/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <jtahirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 21:30:42 by jtahirov          #+#    #+#             */
/*   Updated: 2018/06/05 17:58:13 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_server.h>

cmd_ln_t *g_config = NULL;
cmd_ln_t *g_kws_config = NULL;

void init_ps()
{
	g_ps = ps_init(g_kws_config);
	if (g_ps == NULL)
	{
		fprintf(stderr, "Failed to create recognizer, see log for details\n");
	}
}

void ft_init_conf(void)
{
	if (!g_config)
		g_config = cmd_ln_init(NULL, ps_args(), TRUE,
							   "-hmm", MODELDIR "/en-us-YJM",
							   "-lm", MODELDIR "/5758.lm.bin",
							   "-dict", MODELDIR "/5758.dic",
							   "-logfn", "./ngram.log",
							   "-samprate", "44100",
							   "-nfft", "2048",
							   NULL);
	if (!g_kws_config)
		g_kws_config = cmd_ln_init(NULL, ps_args(), TRUE,
								   "-hmm", MODELDIR "/en-us-YJM",
								   "-dict", MODELDIR "/cmudict-en-us.dict",
								   "-kws", MODELDIR "/keyphrase",
								   "-logfn", "./kws.log",
								   NULL);
}

int callback_http(struct lws *wsi, enum lws_callback_reasons reason,
					void *user, void *in, size_t len)
{
	return 0;
}

int kift_audio_stream_protocol_callback(struct lws *wsi, enum lws_callback_reasons reason,
											   void *user, void *in, size_t len)
{
	static FILE *file;
	const char *hyp;

	switch (reason)
	{
	case LWS_CALLBACK_ESTABLISHED:
		printf("Connection established\n");
		ft_init_conf();
		init_ps();
		ps_start_utt(g_ps);
		printf("started utt\n");
		break;
	case LWS_CALLBACK_RECEIVE:
		recognize(in, len, wsi);
		break;
	case LWS_CALLBACK_CLOSED:
		printf("ending utt\n");
		ps_end_utt(g_ps);
		printf("Connection closed\n");
		break;
	default:
		break;
	}
	return 0;
}

int kift_switch_mode_callback(struct lws *wsi, enum lws_callback_reasons reason,
									 void *user, void *in, size_t len)
{
	char *answer;

	switch (reason)
	{
	case LWS_CALLBACK_ESTABLISHED:
		printf("InterConnection established\n");
		break;
	case LWS_CALLBACK_RECEIVE:
		answer = (char *)in;
		printf("switch mode got | %s |\n", answer);
		if (!strcmp(answer, "ngram"))
		{
			ps_end_utt(g_ps);
			ps_reinit(g_ps, g_config);
			printf("mode switched to ngram\n");
			ps_start_utt(g_ps);
			g_utt_started = false;
		}
		else if (!strcmp(answer, "kws"))
		{
			ps_end_utt(g_ps);
			ps_reinit(g_ps, g_kws_config);
			printf("mode switched to kws\n");
			ps_start_utt(g_ps);
			g_utt_started = false;
		}
		break;
	case LWS_CALLBACK_CLOSED:
		printf("InterConnection is closed\n");
	default:
		break;
	}
	return 0;
}