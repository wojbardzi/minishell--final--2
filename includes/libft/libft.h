/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:39:15 by pzurawic          #+#    #+#             */
/*   Updated: 2025/08/12 22:12:45 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *s);

char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strtok(char *str, char delim);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);
char	*ft_strtrim(char const *s1, char const *set);

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_printf(const char *format, ...);
int		ft_print_char(char c);
int		ft_print_str(char *str);
int		ft_print_nbr(int n);
int		ft_print_unsigned(unsigned int n);
int		ft_print_hex_long(unsigned long long n, int uppercase);
int		ft_print_ptr(void *ptr);
int		ft_print_str(char *str);
void	ft_bzero(void *s, size_t n);

#endif
