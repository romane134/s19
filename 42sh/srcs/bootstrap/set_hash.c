/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 20:08:11 by vjovanov          #+#    #+#             */
/*   Updated: 2019/07/02 22:34:06 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		fill_arrayle(DIR *current_dir, char *path)
{
	struct dirent	*dir_element;
	struct stat		infos;
	char			*full_path;
	char			*temp;

	if ((dir_element = readdir(current_dir)) != NULL)
	{
		if (!(full_path = ft_strjoin(path, dir_element->d_name)))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		if (lstat(full_path, &infos) == -1)
			return (free_array(full_path, 1));
		if ((infos.st_mode & S_IFMT) != S_IFREG ||
			(infos.st_mode & S_IFMT) == S_IFLNK)
			return (free_array(full_path, 1));
		if ((infos.st_mode & S_IXUSR))
		{
			if (!(temp = ft_strdup(dir_element->d_name)))
				free_array_exit(full_path);
			add_data_hash(temp, full_path, HASHTABLE_SIZE, g_hash_table);
		}
		else
			ft_strdel(&full_path);
		return (1);
	}
	return (0);
}

void	fill_hash_arrayle(char **path)
{
	int		i;
	char	*pathjoin;
	DIR		*current_dir;

	i = -1;
	while (path[++i])
	{
		if (!(pathjoin = ft_strjoin(path[i], "/")))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		if ((current_dir = opendir(pathjoin)))
		{
			while (current_dir)
			{
				if (!(fill_arrayle(current_dir, pathjoin)))
					break ;
			}
			closedir(current_dir);
		}
		ft_strdel(&pathjoin);
	}
}

/*
** si le parametre construct est a 1, alors la hash table est cree,
**	POUR LE CAS D'UNE INITIALISATION
**	si le parametre construct est a 0, alors la hash table n'est pas cree,
** elle est uniquement rempli
**
**	fonctionne uniquement pour la g_hash_table
*/

void	set_hash(int construct)
{
	char	**path;
	char	**split;
	int		i;

	i = 0;
	if (construct == 1)
		g_hash_table = make_hash(HASHTABLE_SIZE);
	while (g_shell->env[i])
	{
		if (!(split = ft_strsplit(g_shell->env[i], '=')))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		if (ft_strequ(split[0], "PATH"))
			break ;
		delete_array(split);
		i++;
	}
	if (g_shell->env[i] && split[1])
	{
		path = ft_strsplit(split[1], ':');
		delete_array(split);
		fill_hash_arrayle(path);
		delete_array(path);
	}
}
