#include <stdio.h>
#include <stdlib.h>
#include <libwebsockets.h>
#include <pocketsphinx.h>
#include <sphinx_config.h>
#include <stdbool.h>
#include <time.h>

#define LWS_MAX_SOCKET_IO_BUF 100000

ps_decoder_t *g_ps;

static void recognize(void *chunk, int len)
{
	const char 	*hyp;
	static int	total_len;


	total_len += len;
	printf("total_len = %d\n", total_len);
    ps_process_raw(g_ps, chunk, len, false, false);
    if (total_len >= (89000))
    {
		total_len = 0;
        ps_end_utt(g_ps);
		printf("getting hyp\n");
        hyp = ps_get_hyp(g_ps, NULL);
        printf("hyp => %s\n", hyp);
        ps_start_utt(g_ps);
    }
}

static void 	init_ps()
{
    cmd_ln_t *config;

    config = cmd_ln_init(NULL, ps_args(), TRUE,
		         "-hmm", MODELDIR "/en-us/en-us",
		         "-lm", MODELDIR "/en-us/en-us.lm.bin",
	    		 "-dict", MODELDIR "/en-us/cmudict-en-us.dict",
				 "-logfn", "/dev/null",
		         NULL);
    if (config == NULL) {
		fprintf(stderr, "Failed to create config object, see log for details\n");
    }
    g_ps = ps_init(config);
    if (g_ps == NULL) {
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
			init_ps();
        	ps_start_utt(g_ps);
			printf("started utt\n");
			// printf("Opened file\n");
			break;
		case LWS_CALLBACK_RECEIVE:
			printf("Received audio chunk of size: %lu\n", len);
			recognize(in, len);			
			printf("finished recognize\n");
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
		"http-only",	// name
		callback_http,	// callback
		0				// per_session_data_size
	},
	{
		"kift-audio-stream-protocol",			// protocol name - very important!
		kift_audio_stream_protocol_callback,	// callback
		0,
		100000										// we don't use any per session data
	},
	{
		NULL, NULL, 0   /* End of list */
	}
};

int main(void) {
	// server url will be http://localhost:9000
	int port = 9000;
	struct lws_context *context;
	struct lws_context_creation_info context_info =
	{
		.port = port, .iface = NULL, .protocols = protocols, .extensions = NULL,
		.ssl_cert_filepath = NULL, .ssl_private_key_filepath = NULL, .ssl_ca_filepath = NULL,
		.gid = -1, .uid = -1, .options = 0, NULL, .ka_time = 0, .ka_probes = 0, .ka_interval = 0
	};
	// create lws context representing this server
	context = lws_create_context(&context_info);

	if (context == NULL) {
		fprintf(stderr, "WebSockets init failed\n");
		return -1;
	}
	
	printf("Starting server...\n");
	
	// infinite loop, to end this server send SIGTERM. (CTRL+C)
	while (1) {
		lws_service(context, 50);
		// lws_service will process all waiting events with their
		// callback functions and then wait 50 ms.
		// (this is a single threaded webserver and this will keep our server
		// from generating load while there are not requests to process)
	}
	
	lws_context_destroy(context);
	
	return 0;
}