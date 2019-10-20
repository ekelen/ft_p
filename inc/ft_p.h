/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:30:05 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:30:06 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

# define INPUT_BUF_SIZE 1
# define ALLOC_ERR "ERROR: Error allocating memory."

# include <libft.h>
# include <sys/socket.h>
# include <netdb.h>
# include <unistd.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>

typedef struct		s_data_type
{
	char	*name;
	char	code;
}					t_data_type;

typedef struct		s_file_info
{
	char			*content;
	unsigned int	len;
}					t_file_info;

void				exit_error(char const *message);
bool				ft_puterr_ret(const char *msg);
void				*ft_puterr_null(const char *msg);
int					int_error(char const *message);
char				*nvt_to_unix(char *file_content);
char				*unix_to_nvt(char *file_content);
int					ft_chdir(const char *raw_dirname);
size_t				ft_count_words(char const *s, char c);
size_t				ft_count_strs(char **s);
void				ft_strarr_del(char ***strs);
char				*read_first_line(int fd);
void				store_ascii_file(int sockd, int fd);
void				store_bin_file(int sockd, int fd);

static t_data_type	g_available_types[] =
{
	{ "ascii", 'A' },
	{ "binary", 'I' },
	{ "image", 'I' },
	{ NULL, 0 }
};

/*
** files.c
*/

t_file_info			record_file_util(int sockd);
char				get_type_code(char *name, int i);
bool				file_ok(char *path);

/*
** data_utils.c
*/

int					recv_data_util(int sockd, char code, char *dst_filename);
int					send_data_util(int sockd, char code, char *dst_filename);

/*
** builtins.c
*/

int					exec_builtin_local(char *bin, char **av);

/*
** ascii_data.c
*/

void				send_ascii_data(int sockd, char *content);

#endif
