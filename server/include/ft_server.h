/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <jtahirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:28:39 by jtahirov          #+#    #+#             */
/*   Updated: 2018/06/05 16:08:46 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SERVER_H
# define FT_SERVER_H

# include <sys/uio.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <fcntl.h>
# include <string.h>
# include <netdb.h>
# include <stdarg.h>
# include <libwebsockets.h>
# include <pocketsphinx.h>
# include "libwebsockets.h"
# include <stdio.h>
# include <stdlib.h>
# include <sphinx_config.h>
# include <stdbool.h>
# include <time.h>

/*
** HTTP SERVER
*/

# define LWS_MAX_SOCKET_IO_BUF 100000

typedef struct addrinfo t_addr;
typedef struct sockaddr_storage t_client;

char 		*ft_strnew(size_t size);
void 		initialize_hints(t_addr *hints);
char 		*ft_strjoin(char *str1, char *str2);
char 		*ft_strmjoin(int num, ...);

/*
** AUDIO SERVER
*/

extern cmd_ln_t 		*g_config;
extern cmd_ln_t 		*g_kws_config;
extern ps_decoder_t 	*g_ps;
extern uint8_t 			g_utt_started;

void recognize(void *chunk, int len, struct lws *wsi);
void ft_init_conf(void);
void init_ps();

int kift_audio_stream_protocol_callback(struct lws *wsi, enum lws_callback_reasons reason,
											   void *user, void *in, size_t len);
int kift_switch_mode_callback(struct lws *wsi, enum lws_callback_reasons reason,
									void *user, void *in, size_t len);
int callback_http(struct lws *wsi, enum lws_callback_reasons reason,
						void *user, void *in, size_t len);
#endif