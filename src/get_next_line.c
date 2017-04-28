/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiad <schiad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 17:26:05 by schiad            #+#    #+#             */
/*   Updated: 2017/04/28 15:27:53 by schiad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					get_next_line(int const fd, char **line)
{
	int				result;
	t_desc			*cur_fd;
	static t_desc	*first_fd = NULL;

	if (fd < 0 || !line || BUFF_GNL < 1)
		return (-1);
	if (!first_fd)
		first_fd = ft_new_fd(0, NULL);
	while (!(cur_fd = ft_search_fd(fd, first_fd)))
		ft_new_fd(fd, first_fd);
	result = ft_cache_fd(line, cur_fd);
	if (cur_fd->nb_char == -1)
		return (-1);
	result = (cur_fd->nb_char > 0 || result) ? 1 : 0;
	return (result);
	return (-1);
}

t_desc				*ft_search_fd(int fd, t_desc *first)
{
	t_desc			*tmp;

	tmp = first;
	if (tmp->fd == fd)
		return (tmp);
	while (tmp->next)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_desc				*ft_new_fd(int fd, t_desc *first)
{
	t_desc			*new;
	t_desc			*tmp;

	new = (t_desc *)malloc(sizeof(t_desc));
	new->nb_char = 0;
	new->line = ft_strnew(BUFF_GNL + 1);
	new->fd = fd;
	new->next = NULL;
	new->tape_head = 0;
	if (!first)
		return (new);
	tmp = first;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (new);
}

int					ft_cache_fd(char **line_return, t_desc *desc)
{
	int				found[1];
	int				iter[2];
	char			*tmp[2];

	tmp[0] = NULL;
	tmp[1] = NULL;
	iter[0] = 0;
	iter[1] = 0;
	found[0] = 0;
	while (!found[0] && desc->nb_char >= 0)
		ft_find_line(found, iter, tmp, desc);
	ft_strdel(&tmp[0]);
	*line_return = tmp[1];
	return (iter[1]);
}

void				ft_find_line(int *found, int *iter, char **tmp,
		t_desc *desc)
{
	found[0] = 0;
	ft_strdel(&tmp[1]);
	iter[0] = iter[0] + 1;
	tmp[1] = ft_strnew(BUFF_GNL * (iter[0] + 1));
	if (tmp[0])
		ft_strcpy(tmp[1], tmp[0]);
	ft_strdel(&tmp[0]);
	if (desc->nb_char <= desc->tape_head)
	{
		if (!(desc->nb_char = read(desc->fd, desc->line, BUFF_GNL)))
			found[0] = 2;
		desc->tape_head = 0;
	}
	while (desc->nb_char > desc->tape_head && !found[0])
	{
		if ((tmp[1][iter[1]] = desc->line[desc->tape_head]) == '\n')
			found[0] = 1;
		tmp[1][iter[1]] = (tmp[1][iter[1]] == '\n') ? '\0' : tmp[1][iter[1]];
		desc->tape_head++;
		iter[1]++;
	}
	tmp[0] = ft_strnew(BUFF_GNL * (iter[0] + 1));
	ft_strcpy(tmp[0], tmp[1]);
}
