/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <jtahirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:26:38 by jtahirov          #+#    #+#             */
/*   Updated: 2018/05/22 19:00:13 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

static void initialize_hints(t_addr *hints)
{
	ft_bzero(hints, sizeof(t_addr));
	hints->ai_family = AF_INET;
	hints->ai_socktype = SOCK_STREAM;
	hints->ai_flags = AI_PASSIVE;
}

static char *ft_get_html(char *filename)
{
	char 	*result;
	char 	*tmp;
	int 	fd;
	char 	buffer[1024];
	int 	ret;

	fd = open(filename, O_RDONLY);
	result = (fd < 0) ? "404 Page not found" : ft_strnew(0);
	while ((ret = read(fd, buffer, 1024)) > 0)
	{
		buffer[ret] = '\0';
		tmp = result;
		result = ft_strjoin(result, buffer);
		ft_strdel(&tmp);
		ft_bzero(buffer, 1024);
	}
	return (result);
}

static char	*ft_parse_buffer(char buffer[])
{
	char 	*result;

	ft_printf("%s\n", buffer);
	result = NULL;
	if (ft_strstr(buffer, "/index.html"))
		result = ft_get_html("../templates/index.html");
	if (ft_strstr(buffer, "/static/js/socket.js"))
		result = ft_get_html("../static/js/socket.js");
	if (ft_strstr(buffer, "/static/js/audio.js"))
		result = ft_get_html("../static/js/audio.js");
	return (result);
}

static void 	ft_answer(int client_fd, char *result, int len)
{
	char 	*headers;
	char 	*answer;

	headers = ft_strdup(
		"HTTP/1.0 200 OK\r\nServer: CPi\r\nContent-type: text/html\r\n\r\n");
	answer = !result ? ft_strmjoin(2, headers, " ") : \
				ft_strmjoin(3, headers, " ", result);
	write(client_fd, answer, len + ft_strlen(headers) + 1);
	ft_strdel(&answer);
	ft_strdel(&headers);
	close(client_fd);
}

static void ft_parse_clients(int socketfd)
{
	int 		client_fd;
	t_client 	client_addr;
	socklen_t 	addr_size;
	char 		buffer[2048];
	char 		*result;

	addr_size = sizeof(t_client);
	// fcntl(socketfd, F_SETFL, O_NONBLOCK);
	while (1)
	{
		client_fd = accept(
			socketfd,
			(struct sockaddr *)&client_addr,
			&addr_size);
		if (client_fd < 0)
			continue ;
		ft_bzero(buffer, 2048);
		read(client_fd, buffer, 2048);
		result = ft_parse_buffer(buffer);
		ft_answer(client_fd, result, ft_strlen(result));
		printf("\nEnd\n");
	}
}

int main()
{
	t_addr hints;
	t_addr *server;
	t_client client_addr;
	int socketfd;

	initialize_hints(&hints);
	getaddrinfo(NULL, "6357", &hints, &server);
	socketfd = socket(
		server->ai_family,
		server->ai_socktype,
		server->ai_protocol);
	bind(socketfd, server->ai_addr, server->ai_addrlen);
	listen(socketfd, 10);
	ft_parse_clients(socketfd);
}
