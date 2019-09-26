/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <smondesi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:42:10 by smondesi          #+#    #+#             */
/*   Updated: 2019/06/27 14:57:33 by sstinglh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		save_formated_file(struct dirent	*dent, char *buf, char *cmd,
		t_filename **fname)
{
	char		*str;
	struct stat	f_info;
	char		*tmp;

	lstat(buf, &f_info);
	if (ft_strcmpstart(ft_last_ch(cmd), dent->d_name))
	{
		tmp = ft_strjoin(buf, "/");
		str = ft_strjoin(tmp, dent->d_name);
		stat(str, &f_info);
		ft_strdel(&str);
		ft_strdel(&tmp);
		if (f_info.st_mode == 16877)
		{
			tmp = ft_strjoin(dent->d_name, "/");
			*fname = ft_add_list(*fname, tmp);
			ft_strdel(&tmp);
		}
		else
			*fname = ft_add_list(*fname, dent->d_name);
	}
}

int			ft_last_slash(char *cmd)
{
	int end;

	end = ft_strlen(cmd);
	while (cmd[end] != '/')
		end--;
	return (end);
}

char		*path_to_open(char *cmd)
{
	char		*path;
	char		*tmp;

	if (cmd[0] == '/')
		if (cmd[ft_strlen(cmd) - 1] == '/')
			return (ft_strdup(cmd));
		else if (ft_strcmp(ft_strrchr(cmd, '/'), &cmd[0]))
			return (ft_strndup(cmd, ft_last_slash(cmd) + 1));
		else
			return (ft_strdup("/"));
	else
	{
		path = ft_strnew(PATH_MAX + 1);
		getcwd(path, PATH_MAX);
		if (ft_strchr(cmd, '/'))
		{
			tmp = ft_strjoin(path, "/");
			ft_strdel(&path);
			path = ft_strndup(cmd, ft_last_slash(cmd) + 1);
			path = ft_strjoin_free(&tmp, &path, 2);
		}
	}
	return (path);
}

char		*ft_show_or_complete(t_filename *fname, char *cmd, char *path)
{
	int		nb;
	char	*tmp;
	char	*tmpp;

	nb = ft_list_lenght(fname);
	if (nb == 1)
	{
		tmp = NULL;
		if (cmd[0] == '/')
			tmp = ft_strdup(path);
		else if (ft_strchr(cmd, '/'))
			tmp = ft_strndup(cmd, ft_last_slash(cmd) + 1);
		tmpp = fname->file;
		return (ft_strjoin_free(&tmp, &tmpp, 0));
	}
	else if (nb > 1 && ft_printf("\n"))
		while (fname)
		{
			ft_printf("%s\n", fname->file);
			fname = fname->next;
		}
	return (ft_strdup(cmd));
}

char		*autocomplete_path(char *cmd)
{
	DIR				*dir;
	struct dirent	*dent;
	t_filename		*fname;
	char			*path;

	fname = NULL;
	path = path_to_open(cmd);
	if (!(dir = opendir(path)))
	{
		ft_strdel(&path);
		return (ft_strdup(cmd));
	}
	while ((dent = readdir(dir)) != NULL)
		save_formated_file(dent, path, cmd, &fname);
	cmd = ft_show_or_complete(fname, cmd, path);
	ft_strdel(&path);
	ft_del_list(fname);
	closedir(dir);
	return (cmd);
}
