/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_liner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 10:39:34 by vvoronts          #+#    #+#             */
/*   Updated: 2024/12/08 10:39:36 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * Removes and frees the file context associated with the given file descriptor.
 * 
 * @param fl Pointer to the head of the linked list of file contexts.
 * @param fd File descriptor to remove from the list.
 * @return Always returns NULL.
 */
char	*pop(t_file **fl, int fd)
{
	t_file	*f;
	t_file	*prv;

	f = *fl;
	prv = f;
	while (f)
	{
		if (f->fd == fd)
			break ;
		prv = f;
		f = f->next;
	}
	if (f == *fl)
	{
		*fl = f->next;
		free(f);
	}
	else
	{
		prv->next = f->next;
		free(f);
	}
	return (NULL);
}

/**
 * Retrieves the file context for the given file descriptor
 * or creates a new one if it doesn't exist.
 * 
 * @param fl Pointer to the head of the linked list of file contexts.
 * @param fd File descriptor to retrieve or create the context for.
 * @return Pointer to the file context.
 */
t_file	*get_context(t_file **fl, int fd)
{
	t_file	*f;
	t_file	*prv;

	f = *fl;
	prv = f;
	while (f)
	{
		if (f->fd == fd)
			return (f);
		prv = f;
		f = f->next;
	}
	f = malloc(sizeof(t_file));
	if (!f)
		return (NULL);
	if (prv)
		prv->next = f;
	f->b = 0;
	f->ttl = 0;
	f->next = NULL;
	if (!*fl)
		*fl = f;
	return (f->fd = fd, f->line = NULL, f->i = 0, f);
}

/**
 * Adds a chunk of data from the buffer to the current line in the file context.
 * 
 * @param f Pointer to the file context.
 * @param fl Pointer to the head of the linked list of file contexts.
 * @return Pointer to the updated line, or NULL on failure.
 */
char	*add_chunk(t_file *f, t_file *fl)
{
	ssize_t			len;
	char			*old;
	int				j;

	len = 0;
	while (len < (f->b - f->i) && f->buf[f->i + len++] != '\n')
		;
	old = f->line;
	f->line = (char *)malloc(sizeof(char) * (f->ttl + len + 1));
	if (!f->line)
		return (free(old), pop(&fl, f->fd));
	j = -1;
	while (old && old[++j])
		f->line[j] = old[j];
	while (len--)
		f->line[f->ttl++] = f->buf[f->i++];
	(free(old), f->line[f->ttl] = '\0');
	return ((char *)1);
}

/**
 * Reads the next line from the file associated with the given file descriptor.
 * 
 * @param fd File descriptor to read from.
 * @param error Pointer to an integer to store error status.
 * @return Pointer to the next line, or NULL on failure or end of file.
 */
char	*get_next_liner(int fd, int *error)
{
	static t_file	*fl;
	t_file			*f;
	char			*old;

	*error = 0;
	f = ((t_file *)get_context(&fl, fd));
	if (!f || fd < 0 || BUFFER_SIZE <= 0)
		return (*error = FAIL, pop(&fl, fd));
	while (1)
	{
		if (f->i == f->b)
		{
			f->b = read(fd, f->buf, BUFFER_SIZE);
			f->i = 0;
		}
		if (f->b == 0)
			return (old = f->line, f->line = NULL, pop(&fl, fd), old);
		else if (f->b < 0)
			return (free(f->line), *error = FAIL, pop(&fl, fd));
		if (!add_chunk(f, fl))
			return (free(f->line), *error = FAIL, pop(&fl, fd));
		if (f->line[f->ttl - 1] == '\n' || f->b < BUFFER_SIZE)
			return (f->ttl = 0, old = f->line, f->line = NULL, old);
	}
}
