/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 16:18:55 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/08 12:10:16 by rlucas-d         ###   ########.fr       */
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

typedef struct	s_file
{
	int           size;
	int           date;
	int           mode;
	int           user;
	int           group;
	int           device;
}			t_file;

int		analyse_file(char *file);
void	ft_inspect_file(struct stat s);
void	ft_inspect_rep(struct stat s);

#endif
