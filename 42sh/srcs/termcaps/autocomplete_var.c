/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <smondesi@student.s19.be>         +#+  +:+       +#+        */
/*                                                ++#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:22:56 by smondesi          #+#    #+#             */
/*   Updated: 2019/08/29 17:34:14 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**find in environment
*/

int			add_list_autocompletion_env(t_filename **fname, char *name)
{
	int		i;
	int		nb;
	char	**item;
	int		keylen;

	i = -1;
	nb = 0;
	item = NULL;
	keylen = ft_strlen(name) - 1;
	while (g_shell->env[++i])
	{
		if (!(item = ft_strsplit(g_shell->env[i], '=')))
			exit_shell("malloc error");
		if (ft_strnequ(item[0], name + 1, keylen))
		{
			*fname = ft_add_list(*fname, item[0]);
			nb++;
		}
		delete_array(item);
	}
	return (nb);
}

int			autocompletion_find_closest_var(t_filename **fname, char *name)
{
	int		i;
	int		nb;
	t_hash	*tmp;

	nb = add_list_autocompletion_env(fname, name);
	i = 0;
	while (i <= INTERN_HASH_SIZE)
	{
		tmp = g_shell->intern_hash[i];
		while (tmp != NULL)
		{
			if (ft_strnequ(tmp->key, name + 1, ft_strlen(name) - 1))
			{
				*fname = ft_add_list(*fname, tmp->key);
				nb++;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (nb);
}

char		*autocompletion_closest_var(char *cmd)
{
	int				nb;
	char			*tmp;
	char			*tmpp;
	t_filename		*fname;
	t_filename		*start;

	fname = NULL;
	nb = autocompletion_find_closest_var(&fname, cmd);
	start = fname;
	if (nb == 1)
	{
		tmpp = ft_strdup(fname->file);
		tmp = ft_strjoin("$", tmpp);
		ft_strdel(&tmpp);
		ft_del_list(fname);
		return (tmp);
	}
	else if (nb > 1 && ft_printf("\n"))
		while (fname)
		{
			ft_printf("%s\n", fname->file);
			fname = fname->next;
		}
	ft_del_list(start);
	return (ft_strdup(cmd));
}

char		*autocompletion_dynamique(char *cmd)
{
	char	*str;

	if (!(str = ft_getenv(cmd + 1)))
		if (!(str = find_hash(g_shell->intern_hash, cmd + 1,
						INTERN_HASH_SIZE)))
			return (autocompletion_closest_var(cmd));
	return (ft_strdup(str));
}

char		*autocompletion_var_home(char *cmd)
{
	char	*tmp;
	char	*home;

	home = ft_getenv("HOME");
	if (home == '\0')
		return (cmd);
	tmp = ft_strjoin(home, &cmd[1]);
//	ft_strdel(&home); not malloce
//	ft_strdel(&cmd); idem
	return (tmp);
}
