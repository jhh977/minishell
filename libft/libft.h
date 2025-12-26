/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:32:56 by jhijazi           #+#    #+#             */
/*   Updated: 2025/12/26 15:06:10 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdarg.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include "get_next_line.h"

int				ft_atoi(const char *nptr);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
char			*ft_itoa(int n);
void			*ft_memchr(const void *ptr, int value, size_t size);
int				ft_memcmp(const void *dest, const void *src, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *a, int toFind);
char			*ft_strdup(const char *src);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin(const char *str1, const char *str2);
unsigned int	ft_strlcat(char *dest, const char *src, size_t size);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
int				ft_strlen(const char *c);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *a, int toFind);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			ft_tolower(char c);
char			ft_toupper(char c);
int				ft_printf(const char *format, ...);
int				ft_putint(int i);
int				ft_putunsigned(unsigned int n);
int				ft_putchar(int c);
int				ft_putstr(char *s);
int				ft_puthex(int type, unsigned long a);
int				ft_putadd(void *ptr);
void			*ft_realloc(void *ptr, size_t new_size);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dest, const char *src);
int				ft_putstr_error(char *s);
int				ft_putchar_error(int c);

#endif
