/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 17:02:52 by dhuang            #+#    #+#             */
/*   Updated: 2017/01/05 21:47:35 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include "get_next_line.h"

void			ft_putchar(char c);
void			ft_putstr(char const *str);
void			ft_putnbr(int n);
void			ft_putendl(char const *s);
size_t			ft_strlen(char const *s);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
int				ft_strcmp(char const *s1, char const *s2);
int				ft_strncmp(char const *s1, char const *s2, size_t n);
char			*ft_strcpy(char *dst, char const *src);
char			*ft_strncpy(char *dst, char const *src, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memset(void *b, int c, size_t len);
int				ft_atoi(const char *str);
void			ft_strclr(char *s);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strstr(const char *big, const char *little);
char			*ft_strnstr(const char *big, const char *little, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
char			*ft_strdup(const char *s1);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(long long n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

t_list			*ft_lstnew(void const *content, size_t content_size);
t_list			*ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

int				ft_atoibase(const char *str, int b);
char			*ft_itoabase(unsigned long n, unsigned int b);
void			ft_strrev(char *str);
void			ft_putnbrnl(int n);
void			ft_swap(void *a, void *b);
int				ft_islower(int c);
int				ft_isupper(int c);
int				ft_max(int *n, size_t l);
int				ft_min(int *n, size_t l);
int				*ft_maxmap(int *n, size_t l);
int				*ft_minmap(int *n, size_t l);

char			*ft_strjoinreplace(char const *s1, char const *s2);
int				ft_wstrlen(const wchar_t *s);
wchar_t			*ft_wstrnew(size_t size);
wchar_t			*ft_wstrdup(const wchar_t *s1);
wchar_t			*ft_wstrcat(wchar_t *s1, const wchar_t *s2);
wchar_t			*ft_wstrcpy(wchar_t *dst, const wchar_t *src);
void			*ft_wset(int *b, int c, size_t len);
char			*ft_wstouni(wchar_t *wstr);
void			ft_wctouni(wchar_t wide, char *tmp);
wchar_t			*ft_wstrjoin(wchar_t const *s1, wchar_t const *s2);
wchar_t			*ft_wstrjoinreplace(wchar_t const *s1, wchar_t const *s2);
wchar_t			*ft_wstrsub(wchar_t const *s, unsigned int start, size_t len);

void			*ft_mrlc(void *mem, size_t old, size_t new);
char			*ft_srlc(char *str, size_t old, size_t new);

#endif
