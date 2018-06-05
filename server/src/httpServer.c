/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   httpServer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <jtahirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:26:38 by jtahirov          #+#    #+#             */
/*   Updated: 2018/06/05 13:37:20 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_server.h>

static char *ft_get_html(char *filename)
{
	char 	*result;
	char 	*tmp;
	int 	fd;
	char 	buffer[1024];
	int 	ret;

	fd = open(filename, O_RDONLY);
	result = (fd < 0) ? "404 Page not found" : ft_strnew(0);
	while ((ret = read(fd, buffer, 1023)) > 0)
	{
		buffer[ret] = '\0';
		tmp = result;
		result = ft_strjoin(result, buffer);
		free(tmp);
		bzero(buffer, 1024);
	}
	close(fd);
	return (result);
}

static char	*ft_parse_buffer(char buffer[])
{
	char 	*result;

	printf("%s\n", buffer);
	result = NULL;
	if (!buffer)
		return NULL;
	if (strnstr(buffer, "/index.html", 15))
		result = ft_get_html("../templates/index.html");
	if (strstr(buffer, "/static/js/audio.js"))
		result = ft_get_html("../static/js/audio.js");
	if (strstr(buffer, "GET /static/css/styles.css"))
		result = ft_get_html("../static/css/styles.css");
	if (strnstr(buffer, "/alarm.html", 15))
		result = ft_get_html("../templates/alarm.html");
	if (strstr(buffer, "/static/js/alarm.js"))
		result = ft_get_html("../static/js/alarm.js");
	if (strstr(buffer, "/static/js/command_parser.js"))
		result = ft_get_html("../static/js/command_parser.js");
	return (result);
}

static void 	ft_answer(int client_fd, char *result, int len)
{
	char 	*headers;
	char 	*answer;

	headers = strdup(
		"HTTP/1.0 200 OK\r\nServer: CPi\r\nContent-type: text/html\r\n\r\n");
	answer = !result ? ft_strmjoin(2, headers, " ") : \
				ft_strmjoin(3, headers, " ", result);
	write(client_fd, answer, len + strlen(headers) + 1);
	free(answer);
	free(headers);
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
		bzero(buffer, 2048);
		read(client_fd, buffer, 2047);
		if (!buffer[0])
			continue ;
		if (!(result = ft_parse_buffer(buffer)))
		{
			printf("result = NULL can't find the page O_O \n");
			continue ;
		}
		ft_answer(client_fd, result, strlen(result));
		if (result)
			free(result);
		result = NULL;
		printf("\nEnd\n");
	}
}

int main()
{
	t_addr hints;
	t_addr *server;
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
