/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:32:56 by jhijazi           #+#    #+#             */
/*   Updated: 2025/09/09 18:39:40 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

char	*get_next_line(int fd);
void	ft_safe_free(char **rem);
char	*ft_strchr(const char *a, int toFind);
int		free_temp(char *rem, char *temp);
char	*read_chunk_and_append(int fd, char *rem, char *temp, ssize_t *bytes);
char	*ft_strdup(const char *src);
size_t	ft_str_len(const char *s);
char	*extract_line(char *rem);
char	*update_rem(char *rem);
char	*append_new_buffer(char *rem, char *temp);

#endif