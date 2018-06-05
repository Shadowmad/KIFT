#include <ft_server.h>

ps_decoder_t 	*g_ps;
uint8_t 		g_utt_started = false;

void recognize(void *chunk, int len, struct lws *wsi)
{
	const char *hyp;
	uint8_t in_speech;

	ps_process_raw(g_ps, chunk, len / 2, false, false);
	in_speech = ps_get_in_speech(g_ps);
	if (in_speech && !g_utt_started)
	{
		g_utt_started = true;
		printf("Listening...\n");
	}
	if (!in_speech && g_utt_started)
	{
		ps_end_utt(g_ps);
		hyp = ps_get_hyp(g_ps, NULL);
		if (hyp)
		{
			printf("hyp -> %s\n", hyp);
			int m_len = strlen(hyp);
			unsigned char *message = malloc(m_len + LWS_PRE);
			memcpy(message + LWS_PRE, hyp, m_len);
			lws_write(wsi, message + LWS_PRE, m_len, LWS_WRITE_TEXT);
		}
		ps_start_utt(g_ps);
		g_utt_started = false;
		printf("ready...\n");
	}
}

static struct lws_protocols protocols[] = {
	/* first protocol must always be HTTP handler */
	{
		"http-only",   // name
		callback_http, // callback
		0			   // per_session_data_size
	},
	{
		"kift-audio-stream-protocol",		 // protocol name - very important!
		kift_audio_stream_protocol_callback, // callback
		0,
		100000 // we don't use any per session data
	},
	{
		"kift-switch-mode",
		kift_switch_mode_callback,
		0
	},
	{
		NULL, NULL, 0 /* End of list */
	}};

int main(void)
{
	// server url will be http://localhost:9000
	int port = 9000;
	struct lws_context *context;
	struct lws_context_creation_info context_info =
		{
			.port = port, .iface = NULL, .protocols = protocols, .extensions = NULL, .ssl_cert_filepath = NULL, .ssl_private_key_filepath = NULL, .ssl_ca_filepath = NULL, .gid = -1, .uid = -1, .options = 0, NULL, .ka_time = 0, .ka_probes = 0, .ka_interval = 0};
	// create lws context representing this server
	context = lws_create_context(&context_info);
	if (context == NULL)
	{
		fprintf(stderr, "WebSockets init failed\n");
		return -1;
	}
	printf("Starting server...\n");

	// infinite loop, to end this server send SIGTERM. (CTRL+C)
	while (1)
	{
		lws_service(context, 50);
		// lws_service will process all waiting events with their
		// callback functions and then wait 50 ms.
		// (this is a single threaded webserver and this will keep our server
		// from generating load while there are not requests to process)
	}

	lws_context_destroy(context);

	return 0;
}
