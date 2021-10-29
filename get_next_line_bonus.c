/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonlee <yonlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:51:27 by yonlee            #+#    #+#             */
/*   Updated: 2021/10/29 01:13:56 by yonlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

t_list	*find_fd(t_list **lst, int fd)
{
	t_list	*cur;
	t_list	*prev;
	t_list	*new;

	if (!(*lst))
		return (0);
	cur = *lst;
	while (cur)
	{
		if (cur->fd == fd)
			return (cur);
		prev = cur;
		cur = cur->next;
	}
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->fd = fd;
	new->backup = ft_strndup("", 0);
	new->next = 0;
	if (!(*lst))
		*lst = new;
	else
		prev->next = new;
	return (new);
}

char	*free_all(t_list **head, t_list *lst)
{
	t_list	*cur;
	t_list	*prev;

	if (!(*head) || !lst)
		return (0);
	cur = *head;
	prev = 0;
	while (cur->fd != lst->fd)
	{
		if (!(cur->next))
			return (0);
		prev = cur;
		cur = cur->next;
	}
	if (prev)
		prev->next = cur->next;
	if (cur->backup)
		free(cur->backup);
	if (*head == cur)
		*head = (*head)->next;
	free(cur);
	cur = 0;
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*ptr;
	char			buf[BUFFER_SIZE + 1];
	ssize_t			read_size;
	char			*last;

	if (read(fd, buf, 0) == -1 || BUFFER_SIZE <= 0)
		return (free_all(&head, 0));
	ptr = find_fd(&head, fd);
	if (!ptr)
		return (free_all(&head, 0));
	if (ft_strchr(ptr->backup, '\n'))
		return (split_line(&(ptr->backup))); // 개행 문자가 포함되어 있을 경우 문장을 잘라 반환
	read_size = read(fd, buf, BUFFER_SIZE);
	while (read_size > 0)
	{
		buf[read_size] = '\0';
		ptr->backup = ft_strjoin(ptr->backup, buf); // backup에 들어있던 문자열에 새로 읽어온 문자열 덧붙이기
		if (!(ptr->backup))
			return (free_all(&head, ptr));
		if (ft_strchr(ptr->backup, '\n'))
			return (split_line(&(ptr->backup))); // 개행 문자가 포함되어 있을 경우 문장을 잘라 반환
		read_size = read(fd, buf, BUFFER_SIZE);
	}
	last = split_line(&(ptr->backup)); // 현재까지 남아 있는 문자열 잘라서 last에 저장
	free_all(&head, ptr);
	return (last);
}
