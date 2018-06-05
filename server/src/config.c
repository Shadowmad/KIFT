/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <jtahirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 21:30:42 by jtahirov          #+#    #+#             */
/*   Updated: 2018/06/04 21:47:16 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_server.h>

cmd_ln_t *g_config = NULL;
cmd_ln_t *g_kws_config = NULL;

void ft_init_conf(void)
{
	if (!g_config)
		g_config = cmd_ln_init(NULL, ps_args(), TRUE,
							   "-hmm", MODELDIR "/en-us-YJM",
							   "-lm", MODELDIR "/en-us.lm.bin",
							   "-dict", MODELDIR "/cmudict-en-us.dict",
							   "-logfn", "./ngram.log",
							   "-samprate", "44100",
							   "-nfft", "2048",
							   NULL);
	if (!g_kws_config)
		g_kws_config = cmd_ln_init(NULL, ps_args(), TRUE,
								   "-hmm", MODELDIR "/en-us-YJM",
								   "-dict", MODELDIR "/cmudict-en-us.dict",
								   //    "-lm", MODELDIR "/1421.lm.bin",
								   "-kws", MODELDIR "/keyphrase",
								   //    "-samprate", "44100",
								   //    "-nfft", "2048",
								   "-logfn", "./kws2.log",
								   NULL);
}
