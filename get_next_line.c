/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonlee <yonlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:51:27 by yonlee            #+#    #+#             */
/*   Updated: 2021/10/27 18:55:33 by yonlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*split_line(char **backup) // 문장 자르는 함수 구현
{
	char	*new_line;
	char	*ptr_cut;
	char	*remains;
	size_t	n;

	if (!(**backup) || !(*backup))
		return (0);
	ptr_cut = ft_strchr(*backup, '\n');
	if (!ptr_cut) // 개행 문자가 포함되어 있지 않은 경우
		ptr_cut = ft_strchr(*backup, 0);
	n = ptr_cut - *backup + 1;
	new_line = ft_strndup(*backup, n);
	if (!new_line)
		return (0);
	remains = ft_strndup(ptr_cut + 1, ft_strlen(ptr_cut + 1));
	if (!remains)
	{
		free(new_line);
		return (0);
	}
	free(*backup);
	*backup = remains;
	return (new_line);
}

char	*free_all(char **backup, char **buf)
{
	if (*buf)
	{
		free(*buf);
		buf = 0;
	}
	if (*backup)
	{
		
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*buf;
	ssize_t		read_size;
	char		*last;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf || read(fd, buf, 0) == -1 || BUFFER_SIZE <= 0)
		return (free_all(&backup, &buf));
	if (!backup) // 해당 fd 버퍼가 초기화되어 있지 않은 경우
		backup = ft_strndup("", 0);
	if (ft_strchr(backup, '\n'))
		return (split_line(&backup)); // 개행 문자가 포함되어 있을 경우 문장을 잘라 반환
	read_size = read(fd, buf, BUFFER_SIZE);
	while (read_size > 0)
	{
		buf[read_size] = '\0';
		backup = ft_strjoin(backup, buf); // backup에 들어있던 문자열에 새로 읽어온 문자열 덧붙이기
		if (ft_strchr(backup, '\n'))
			return (split_line(&backup)); // 개행 문자가 포함되어 있을 경우 문장을 잘라 반환
		read_size = read(fd, buf, BUFFER_SIZE);
	}
	last = split_line(&backup); // 현재까지 남아 있는 문자열 잘라서 last에 저장
	free_all(&backup, &buf);
	return (last);
}
