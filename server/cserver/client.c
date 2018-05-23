/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <jtahirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:54:48 by jtahirov          #+#    #+#             */
/*   Updated: 2018/05/22 16:11:41 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

static void 	ft_print_response(int sockfd)
{
	char 	buffer[2048];
	int 	n;

	n = read(sockfd, buffer, 2048);
	buffer[n] = '\0';
	ft_printf("response%\n%s\n", buffer);
}

static void 	ft_request_page(int sockfd)
{
	char 	*header;
	int		n;
	
	header = ft_strdup("GET /index.html HTTP/1.0\r\nHost:example.org\r\n\r\n");
	n = write(sockfd, header, strlen(header));
	ft_print_response(sockfd);
}

static void  	ft_initialize_server(t_addr **serverinfo)
{
	t_addr 	hints;
	
	ft_bzero(&hints, sizeof(t_addr));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	getaddrinfo("localhost", "6357", &hints, serverinfo);
}

int 	main(void)
{
	int		sockfd;
	t_addr 	*serverinfo;

	ft_initialize_server(&serverinfo);
	sockfd = socket(
					serverinfo->ai_family, \
					serverinfo->ai_socktype, \
					serverinfo->ai_protocol);

	if (connect(sockfd, serverinfo->ai_addr, serverinfo->ai_addrlen) < 0)
		return (-1);
	ft_request_page(sockfd);
	freeaddrinfo(serverinfo);
	return (1);
}


// int sockfd = socket(servinfo->ai_family,
//                     servinfo->ai_socktype,
//                     servinfo->ai_protocol);
// connect(sockfd, 
//         servinfo->ai_addr,
//         servinfo->ai_addrlen); 
// freeaddrinfo(servinfo);