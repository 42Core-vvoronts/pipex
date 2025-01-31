/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elibft.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 10:38:42 by vvoronts          #+#    #+#             */
/*   Updated: 2024/12/08 10:38:45 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELIBFT_H
# define ELIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdarg.h>
# include <limits.h>
# define BUFFER_SIZE 1024
# define SUCCESS 0
# define FAIL -1
# define MEMFAIL -2

enum	e_errors
{
	noerror = 0,
	intovfl = 1,
	longovfl = 2,
	llovfl = 3,
	nonnumer = 4,
	empty = 5
};

typedef struct s_file
{
	int				fd;
	ssize_t			b;
	char			buf[BUFFER_SIZE];
	ssize_t			i;
	char			*line;
	size_t			ttl;
	struct s_file	*next;
}	t_file;
char		*get_next_liner(int fd, int *error);
long long	ft_atoier(char *str, int *error);
size_t		ft_parrlen(void *arr);
void		*ft_parrjoin(void *arr1, void *arr2);
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlener(const char *str);
char		*ft_strjoiner(char const *s1, char const *s2);
long long	ft_parrclean(int code, void (*del)(void *), void *arr1, void *arr2);

#endif