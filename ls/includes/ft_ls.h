/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 16:18:55 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/21 19:25:52 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_LS_H
# define FT_LS_H

#include "../libft/libft.h"

# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <limits.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

/* (readdir)
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
 ** ft_inspect_file.ce
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

typedef struct	s_file t_file;
struct			s_file
{
	int			size;
	int			flag;
	int			blks;
	char		*path;
	char		*date;
	int			link;
	char		*mode;
	int			device;
	char		*group;
	char		*user;
	char		*name;
	struct stat	stat;
	t_file		*next;
};

typedef struct	s_test t_test;
struct			s_test
{
	t_file		doki;
	t_test		*next;
};

int				print_info_file(char *doc, t_file file);
t_file			ft_inspect_file(char *doc, t_file *file);

/*
** ft_flag
*/

int				ft_flag(char **argv, int *flag);
void			set_flag(char *argv, int *flag);

/*
** ft_lecture.c
*/
t_test			*lecture(int flag, char *doc);

/*
** ft_list.c
*/

t_file		*ft_list(char **file, int i);
t_file		*ft_elem_list(/*t_file *list,*/ char *file);

#endif
