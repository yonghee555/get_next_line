/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonlee <yonlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:51:27 by yonlee            #+#    #+#             */
/*   Updated: 2021/10/25 20:44:34 by yonlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*store[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];
	ssize_t		read_size;

	if (read(fd, buf, 0) == -1 || BUFFER_SIZE <= 0)
		return (0);
	if (ft_strchr(store[fd], '\n'))
		; // TODO: 개행 문자를 기준으로 문장 나누기
	read_size = read(fd, buf, BUFFER_SIZE);
	while (read_size > 0)
	{
		if (ft_strchr(store[fd], '\n'))
		; // TODO: 개행 문자를 기준으로 문장 나누기
		read_size = read(fd, buf, BUFFER_SIZE);
	}
}
