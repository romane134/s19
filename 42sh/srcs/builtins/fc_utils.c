/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstinglh <sstinglh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 21:42:03 by sstinglh          #+#    #+#             */
/*   Updated: 2019/08/19 22:11:15 by sstinglh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		fc_error(int i, char *cmd)
{
	if (i == 0)
	{
		ft_printf("fc: usage: fc [-e ename] [-nlr] [first] [last] or ");
		ft_printf("fc -s [pat=rep] [cmd]");
	}
	else if (i == 1)
		ft_printf("42sh: %d: command not found", cmd);
	else if (i == 2)
		ft_printf("fc: Error with temp file");
	return (-1);
}

/*
** get_first_last()
**
** Le but est d'obtenir le first et le last.
** Au debut first est le fd (thanks la norme)
** On dit que last = history_len_tmp - 1 au cas ou on ai pas de last
** Ensuite on recup first et last si ils existent.
** Si on a pas de first on prend soit les 16 derniers soit le dernier en
** fonction de fd.
** Si on a un first negatif on l'inverse avec histo_len
** Pareil pour last
** Les deux dernieres conditions evite qu'on affiche un historique
** qui n'existe pas
*/

int		get_first_last(char **cmd, int i, int *first, int *last)
{
	int history_len_tmp;
	int fd;

	fd = *first;
	history_len_tmp = get_history_len();
	*last = history_len_tmp - 1;
	if (cmd[i] && (ft_isdigit(cmd[i][0]) || cmd[i][0] == '-'))
	{
		*first = ft_atoi(cmd[i]);
		if (cmd[i + 1] && (ft_isdigit(cmd[i][0]) || cmd[i][0] == '-'))
			*last = ft_atoi(cmd[i + 1]);
	}
	else
		*first = (fd == 0) ? *last - 15 : *last;
	if (*first < 0)
		*first = history_len_tmp - (-*first);
	if (*last < 0)
		*last = history_len_tmp - (-*last);
	if (*last > history_len_tmp - 1 || *last <= 0)
		*last = history_len_tmp - 1;
	if (*first > history_len_tmp - 1 || *first <= 0)
		*first = history_len_tmp - 1;
	return (*first);
}

/*
** get_editor()
**
** Si -e est active on recupere l'editeur ou on retourne une erreur
** Sinon, on va recup FCEDIT. Si il n'existe pas un utilise
** DEFAULT_TEXT_EDITOR (ed)
*/

char	*get_editor(char **cmd, int *i, int g_bit)
{
	char *editor;

	if (g_bit & FC_OPTION_E)
	{
		if (!cmd[*i])
		{
			ft_printf("fc: argument expected: -e\n");
			return (NULL);
		}
		editor = ft_strdup(cmd[(*i)++]);
	}
	else
	{
		if (ft_getenv("FCEDIT"))
			editor = ft_strdup(ft_getenv("FCEDIT"));
		else
			editor = ft_strdup(DEFAULT_TEXT_EDITOR);
	}
	return (editor);
}

/*
** get_new_cmd()
**
** Recupere les commandes dans le fichier temporaire d'edition et les
** join avec ";"
*/

char	*get_new_cmd(void)
{
	int		fd;
	char	*line;
	char	*new_cmd;
	char	*tmp;

	new_cmd = NULL;
	if ((fd = open("/tmp/.42sh_tmp_fc", O_RDWR | O_CREAT | O_APPEND,
					0755)) == -1)
		return (NULL);
	get_next_line(fd, &line, 1);
	while (get_next_line(fd, &line, 0))
	{
		ft_printf("%s\n", line);
		if (new_cmd == NULL)
			new_cmd = ft_strdup(line);
		else
		{
			tmp = new_cmd;
			new_cmd = ft_str3join(new_cmd, ";", line);
			ft_strdel(&tmp);
		}
		ft_strdel(&line);
	}
	close(fd);
	return (new_cmd);
}
