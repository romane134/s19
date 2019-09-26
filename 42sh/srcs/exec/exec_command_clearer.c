/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_clearer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 19:54:46 by vjovanov          #+#    #+#             */
/*   Updated: 2019/07/02 22:44:57 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Cree une copie de la chaine de caractere qu'il recoit sans prendre en compte
** les index a ban.
** Ex: Chaine en entree: "Bo" => Chaine de sortie: Bo
*/

void	create_new_cmd(char **cmd, int i, int *ban_index)
{
	char	*new_cmd;
	char	*tmp;
	int		j;
	int		k;
	int		l;

	if (!(tmp = ft_strnew(ft_strlen(cmd[i]))))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	j = -1;
	l = -1;
	while (cmd[i][++j])
	{
		k = -1;
		while (ban_index[++k] != -1)
			if (ban_index[k] == j)
				break ;
		if (ban_index[k] == -1)
			tmp[++l] = cmd[i][j];
	}
	if (!(new_cmd = ft_strdup(tmp)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	ft_strdel(&tmp);
	ft_strdel(&(cmd[i]));
	cmd[i] = new_cmd;
}

/*
** Fonction qui s'occupe de stocker tous les index de la chaine de
** caractere a supprimer lorsqu'il recreera une nouvelle chaine nettoye
**
** Ex: "bo" => ban_index = [0, 3]
*/

void	find_index_to_ban(char *cmd, int k, int **ban_index,
	t_history **history)
{
	int j;

	j = -1;
	while (cmd[++j])
		if (cmd[j] == '"' || cmd[j] == '\'')
		{
			if (!(j > 0 && cmd[j - 1] == '\\' && is_escaped(cmd, j)))
			{
				if (get_last_history_opening(*history) == NULL)
				{
					add_history(history, cmd[j] == '"' ? "\"" : "'",
						cmd[j] == '"' ? "\"" : "'");
					(*ban_index)[k++] = j;
				}
				else if (get_last_history_closing(*history)[0] == cmd[j])
				{
					remove_last_history(history);
					(*ban_index)[k++] = j;
				}
			}
		}
		else if (cmd[j] == '\\')
			if (is_escape_backslash(cmd, j)
				&& !ft_strequ(get_last_history_closing(*history), "\'"))
				(*ban_index)[k++] = j;
}

/*
** Prendre un double tableau de chaine de caractere retourne par
** parse_cmd qui se trouve dans exec_command_splitter.c
**
** Il s'occupe de retourner cette chaine de caractere nettoye de tous
** les quotes, dquotes et '\' inutiles
**
** Aucune des fonction ici n'est generique et peut etre utilise en dehors
** du contexte de la fonction clear_cmd
*/

void	clear_cmd(char **cmd)
{
	int			i;
	int			k;
	int			*ban_index;
	t_history	*history;

	i = -1;
	history = NULL;
	while (cmd[++i])
	{
		k = 0;
		if (!(ban_index = (int*)malloc((sizeof(int) * (ft_strlen(cmd[i]) + 1)))))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		ft_intset(ban_index, ft_strlen(cmd[i]) + 1, -1);
		find_index_to_ban(cmd[i], k, &ban_index, &history);
		create_new_cmd(cmd, i, ban_index);
		free(ban_index);
		ban_index = NULL;
	}
}
