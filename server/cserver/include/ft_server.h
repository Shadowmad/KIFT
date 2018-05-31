/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <jtahirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:28:39 by jtahirov          #+#    #+#             */
/*   Updated: 2018/05/31 10:40:42 by jtahirov         ###   ########.fr       */
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

typedef struct addrinfo t_addr;
typedef struct sockaddr_storage t_client;

char 		*ft_strnew(size_t size);
void 		initialize_hints(t_addr *hints);
char 		*ft_strjoin(char *str1, char *str2);
char 		*ft_strmjoin(int num, ...);

#endif