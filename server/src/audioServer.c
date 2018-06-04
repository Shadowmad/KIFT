#include <stdio.h>
#include <stdlib.h>
#include <libwebsockets.h>
#include <pocketsphinx.h>
#include <sphinx_config.h>
#include <stdbool.h>
#include <time.h>
#include <ft_server.h>

#define LWS_MAX_SOCKET_IO_BUF 100000

ps_decoder_t 	*g_ps;
bool 			g_kws = true;

static void recognize(void *chunk, int len)
{
	const char 			*hyp;
	uint8_t				in_speech;
	static uint8_t		utt_started = false;

	ps_process_raw(g_ps, chunk, len / 2, false, false);
	in_speech = ps_get_in_speech(g_ps);
	if (in_speech && !utt_started) {
		utt_started = true;
		if (!g_kws)
		{
			ps_reinit(g_ps, g_kws_config);
			g_kws = true;
		}
		else 
			printf("looking for minion\n");
	}
	if (!in_speech && utt_started) {
		ps_end_utt(g_ps);
		hyp = ps_get_hyp(g_ps, NULL);
		if (hyp) {
			printf("hyp -> %s\n", hyp);
			if (strstr(hyp, "minion"))
			{
				ps_reinit(g_ps, g_config);
				g_kws = false;
				printf("changed config\n");
			}
			fflush(stdout);
		}
		if (ps_start_utt(g_ps) < 0)
			printf("Failed to start utterance\n");
		utt_started = false;
		printf("ready...\n");
	}
}

static void init_ps()
{
	g_ps = ps_init(g_kws_config);
	if (g_ps == NULL)
	{
		fprintf(stderr, "Failed to create recognizer, see log for details\n");
	}
}

static int callback_http(struct lws *wsi,
						 enum lws_callback_reasons reason, void *user, void *in, size_t len)
{
	return 0;
}

static int kift_audio_stream_protocol_callback(struct lws *wsi,
											   enum lws_callback_reasons reason, void *user, void *in, size_t len)
{
	static FILE *file;
	const char *hyp;
	switch (reason)
	{
	case LWS_CALLBACK_ESTABLISHED:
		// file = fopen("test.raw", "wb");
		printf("Connection established\n");
		ft_init_conf();
		init_ps();
		ps_start_utt(g_ps);
		printf("started utt\n");
		// printf("Opened file\n");
		break;
	case LWS_CALLBACK_RECEIVE:
		// printf("Received audio chunk of size: %lu\n", len);
		recognize(in, len);
		// printf("finished recognize\n");
		// fwrite(in, 1, len, file);
		break;
	case LWS_CALLBACK_CLOSED:
		// fclose(file);
		// printf("Closed file\n");
		printf("ending utt\n");
		ps_end_utt(g_ps);
		hyp = ps_get_hyp(g_ps, NULL);
		printf("hyp => %s\n", hyp);
		printf("Connection closed\n");
		break;
	default:
		break;
	}

	return 0;
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
