/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 16:18:55 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/02/10 16:07:06 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"
# include <dirent.h>
# include <stdio.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <uuid/uuid.h>

/*
** (readdir)
**
** struct dirent {
**    ino_t          d_ino;        numéro d'inœud
**    off_t          d_off;        décalage jusqu'à la dirent suivante
**    unsigned short d_reclen;     longueur de cet enregistrement
**    unsigned char  d_type;       type du fichier
**    char           d_name[256];  nom du fichier
** };
*/

/*
** ft_inspect_file.c
*/

# define A_FLAG 1
# define RR_FLAG 2
# define L_FLAG  4
# define T_FLAG 8
# define G_FLAG 16
# define ONE_FLAG 32
# define R_FLAG 64
# define TT_FLAG 128
# define U_FLAG 256
# define UU_FLAG 512
# define N_FLAG 1024
# define S_FLAG 2048
# define F_FLAG 4096

typedef struct s_file	t_file;
struct				s_file
{
	int				tot;
	int				size;
	char			*date;
	int				link;
	char			*mode;
	int				device;
	char			*group;
	char			*user;
	char			*name;
	int				flag;
	int				blks;
	ssize_t			time;
	char			*path;
	int				major;
	int				minor;
	struct group	*gr;
	struct passwd	*pwd;
};

typedef struct s_space	t_space;
struct				s_space
{
	int				link;
	size_t			group;
	int				size;
	size_t			user;
	int				major;
	int				minor;
};

typedef struct s_test	t_test;
struct				s_test
{
	t_file			list;
	t_test			*next;
};

/*
** ft_ls
*/
int					ft_link(int flag, t_test *list);
void				ft_recur(int flag, t_test *file);
t_test				*ft_doc(t_test *file, int flag);
t_test				*ft_file(t_test *list, int link);
void				ft_list_document(t_test *file, int flag, int i, int link);
void				ft_suite(int *var, t_test *file, t_test *list);
/*
** ft_flag
*/

int					ft_flag(char **argv, int *flag);
void				set_flag(char *argv, int *flag);

/*
** ft_good_print
*/

int					ft_tot_blks(t_test *li);
int					ft_lg(int nb);
void				ft_space(int i);
void				print_list_2(t_test *li, t_space nb);
void				print_list(t_test *li);
void				ft_totspace(t_test *li, t_space *i);

/*
** ft_stat_right.c
*/

t_file				ft_inspect_file(t_file *file);
char				*stat_time(struct stat s, t_file *file);

/*
** ft_sort.c
*/

void				ft_sort(int flag, t_test *file);
void				sort_list(t_test *file);
t_test				*list_rev(t_test *file);
void				sort_list_time(t_test *file);
t_test				*ft_sort_list(int flag, t_test *list);

/*
** ft_lecture_file.c
*/
t_test				*ft_lecture_file(int flag, t_test **file);

/*
** ft_list_file.c
*/

t_test				*ft_list_file(char **argv, int start, int *i);
void				ft_print_file(t_test *li);
t_test				*ft_list(char *str);
void				push_back(t_test **list, t_test *new);
char				**ft_sort_argv(char **argv, int i);

/*
** ft_list.c
*/
t_test				*add_lst(t_test *li, t_file data);
t_test				*push_back_list(t_test *li, t_file data);
t_test				*add_sort(t_test *li, t_file data);
void				ft_free_list(t_test *child);

/*
** ft_lecture.c
*/

t_test				*lecture_2(int flag, struct dirent *dp,
		char *doc, t_test *file);
t_test				*lecture(int flag, char *doc);

/*
** ft_atr.c
*/
char				ft_atrib(t_file *file);
#endif
