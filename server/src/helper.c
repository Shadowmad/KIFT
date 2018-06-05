/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <jtahirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 10:06:28 by jtahirov          #+#    #+#             */
/*   Updated: 2018/06/05 16:09:52 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_server.h>

char 	*ft_strmjoin(int num, ...)
{
	va_list 	ap;
	char 		*res;
	char 		*tmp;
	char 		*arg;

	va_start(ap, num);
	res = ft_strnew(0);
	while(num--)
	{
		arg = va_arg(ap, char *);
		tmp = res;
		res = ft_strjoin(res, arg);
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
	}
	va_end(ap);
	return (res);
}

char 	*ft_strjoin(char *str1, char *str2)
{
	int 	len1;
	int 	len2;
	char 	*fresh;

	if (!str1 && !str2)
		return (NULL);
	else if (!str1)
		return (strdup(str2));
	else if (!str2)
		return (strdup(str1));
	len1 = strlen(str1);
	len2 = strlen(str2);
	fresh = ft_strnew(len1 + len2);
	strcpy(fresh, str1);
	strcpy(fresh + len1, str2);
	return (fresh);
}

char *ft_strnew(size_t size)
{
	return ((char *)calloc(1, size + 1));
}

void initialize_hints(t_addr *hints)
{
	bzero(hints, sizeof(t_addr));
	hints->ai_family = AF_INET;
	hints->ai_socktype = SOCK_STREAM;
	hints->ai_flags = AI_PASSIVE;
}