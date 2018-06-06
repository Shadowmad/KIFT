/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   httpServer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <jtahirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:26:38 by jtahirov          #+#    #+#             */
/*   Updated: 2018/06/06 14:27:07 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_server.h>

static void ft_connect_header(char **result)
{
	;
}

static char *ft_get_file(char *filename)
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
	ft_connect_header(&result);
	return (result);
}

static char	*ft_parse_buffer(char buffer[], enum e_type *type)
{
	char 			*result;
	char 			*header;

	printf("%s\n", buffer);
	result = NULL;
	if (!buffer)
		return NULL;
	if (strnstr(buffer, "/index.html", 15))
	{
		result = ft_get_file("../templates/index.html");
		*type = html;
	}
	if (strnstr(buffer, "/alarm.html", 15))
	{
		result = ft_get_file("../templates/alarm.html");
		*type = html;
	}
	if (strstr(buffer, "GET /static/css/styles.css"))
	{
		result = ft_get_file("../static/css/styles.css");
		*type = css;
	}
	if (strstr(buffer, "/static/js/audio.js"))
	{
		result = ft_get_file("../static/js/audio.js");
		*type = js;
	}
	if (strstr(buffer, "/static/js/alarm.js"))
	{
		result = ft_get_file("../static/js/alarm.js");
		*type = js;
	}
	if (strstr(buffer, "/static/js/command_parser.js"))
	{
		result = ft_get_file("../static/js/command_parser.js");
		*type = js;
	}

	return (result);
}

static void 	ft_answer(int client_fd, char *result, int len, enum e_type type)
{
	char 	*headers;
	char 	*answer;

	printf("this is what i got from type: %d\n", type);
	switch (type)
	{
		case html:
			headers = strdup(
				"HTTP/1.0 200 OK\r\nServer: CPi\r\nContent-type: text/html\r\n\r\n");
		break ;
		case css:
			headers = strdup(
				"HTTP/1.0 200 OK\r\nServer: CPi\r\nContent-type: text/css\r\n\r\n");
		break ;
		case js:
			headers = strdup(
				"HTTP/1.0 200 OK\r\nServer: CPi\r\nContent-type: text/javascript\r\n\r\n");
		break ;
		default:
		break ;
	}
	printf("\n\nThis is my header:\n\t%s\n\n", headers);
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
	enum e_type type;

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
		if (!(result = ft_parse_buffer(buffer, &type)))
		{
			printf("result = NULL can't find the page O_O \n");
			continue ;
		}
		ft_answer(client_fd, result, strlen(result), type);
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
