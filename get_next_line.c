/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonlee <yonlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:51:27 by yonlee            #+#    #+#             */
/*   Updated: 2021/10/26 21:58:46 by yonlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*split_line() // TODO: 문장 자르는 함수 구현
{

}

char	*get_next_line(int fd)
{
	static char	*backup[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];
	ssize_t		read_size;
	char		*last;

	if (read(fd, buf, 0) == -1 || BUFFER_SIZE <= 0)
		return (0);
	if (!backup[fd]) // 해당 fd 버퍼가 초기화되어 있지 않은 경우
		backup[fd] = ft_strndup("", 0);
	if (ft_strchr(backup[fd], '\n'))
		; // TODO: 개행 문자가 버퍼에 들어있을 경우, 개행 문자를 기준으로 문장 나누어서 반환
	read_size = read(fd, buf, BUFFER_SIZE);
	while (read_size > 0)
	{
		buf[read_size] = '\0';
		backup[fd] = ft_strjoin(backup[fd], buf); // backup에 들어있던 문자열에 새로 읽어온 문자열 덧붙이기
		if (ft_strchr(backup[fd], '\n'))
			; // TODO: 개행 문자를 기준으로 문장 나누기
		read_size = read(fd, buf, BUFFER_SIZE);
	}
	// TODO: 현재까지 남아 있는 문자열 잘라서 last에 저장
	free(backup[fd]);
	backup[fd] = 0;
	return (last);
}
