/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstinglh <sstinglh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:36:01 by sstinglh          #+#    #+#             */
/*   Updated: 2019/08/01 23:55:34 by sstinglh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** open_history_file()
** Creation du path pour l'history
** On ouvre le fichier en lecture/ecriture, on le cree si il le faut et on force
** 														l'ecriture a la fin
** On calcule la longueur du fichier
** On met la derniere ligne dans last_cmd
** on free line et history_path
*/

int		open_history_file(t_termcaps *termcaps)
{
	char	*history_path;
	char	*line;
	int		fd;

	line = NULL;
	history_path = ft_strjoin(getenv("HOME"), "/.42sh_history");
	if ((fd = open(history_path, O_RDWR | O_CREAT | O_APPEND,
					0777)) == -1)
		return (-1);
	ft_strdel(&history_path);
	termcaps->history_len = 0;
	termcaps->last_cmd = ft_strnew(0);
	while (get_next_line(fd, &line, 0))
	{
		ft_strdel(&termcaps->last_cmd);
		termcaps->history_len++;
		termcaps->last_cmd = ft_strdup(line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
	return (1);
}

/*
** read_last_line()
** On open pour repartir au debut du fichier
** On recup le path et on y ajout le nom du fichier
** On ouvre le fichier en lecture/ecriture, on le cree si il le faut et on
** 												force l'ecriture a la fin
** On reset le GNL (3eme argument a 1)
** On va chercher la ligne a l'index i
*/

char	*read_last_line(int pos)
{
	char	*line;
	int		i;
	int		fd;
	char	*history_path;

	i = 0;
	line = NULL;
	history_path = ft_strjoin(getenv("HOME"), "/.42sh_history");
	if ((fd = open(history_path, O_RDWR | O_CREAT | O_APPEND,
					0777)) == -1)
	{
		ft_strdel(&history_path);
		return (NULL);
	}
	ft_strdel(&history_path);
	get_next_line(fd, &line, 1);
	while ((i <= pos))
	{
		i++;
		ft_strdel(&line);
		get_next_line(fd, &line, 0);
	}
	close(fd);
	return (line);
}

/*
** add_in_history()
** On regarde si la commande est pareil que la precedente si oui on ne l'ajoute
**< pas
** Sinon on ecrit a la fin du fichier
** On ajoute +1 au nombre de lignes dans history
** On ajoute 1 a la position (car on a ajoute un champ)
** On supprime la last_cmd
** On met la nouvelle
** On free cmd2 qui comporte la commande avec le \n
*/

void	add_in_history(t_termcaps *termcaps, char *cmd)
{
	char	*cmd2;
	char	*history_path;
	int		fd;

	if (cmd[0] == '\0' || (ft_strcmp(termcaps->last_cmd, cmd) == 0))
		return ;
	history_path = ft_strjoin(getenv("HOME"), "/.42sh_history");
	if ((fd = open(history_path, O_RDWR | O_CREAT | O_APPEND,
					0777)) == -1)
	{
		ft_strdel(&history_path);
		return ;
	}
	ft_strdel(&history_path);
	cmd2 = ft_strjoin(cmd, "\n");
	write(fd, cmd2, ft_strlen(cmd2));
	termcaps->history_len++;
	termcaps->history_pos++;
	ft_strdel(&termcaps->last_cmd);
	termcaps->last_cmd = ft_strdup(cmd);
	ft_strdel(&cmd2);
	close(fd);
}

/*
** termcaps_histo()
** On recup ajoute ou soustrait 1 a history_pos
** On va chercher la ligne avec read_last_line
** On affiche a nouveau
** Si on est sur le 1er histo, on affiche une cmd vide
** On recalcule les pos et les cmd_len
*/

void	termcaps_histo(t_termcaps *termcaps, char **cmd, int i)
{
	termcaps->edit_mode = FALSE;
	if (termcaps->history_pos < termcaps->history_len && i == 65)
	{
		termcaps->history_pos++;
		ft_strdel(cmd);
		*cmd = read_last_line(termcaps->history_len - termcaps->history_pos);
		show_new(*cmd, termcaps, 0);
	}
	else if (termcaps->history_pos > 1 && i == 66)
	{
		termcaps->history_pos--;
		ft_strdel(cmd);
		*cmd = read_last_line(termcaps->history_len - termcaps->history_pos);
		show_new(*cmd, termcaps, 0);
	}
	else if (termcaps->history_pos == 1 && i == 66)
	{
		termcaps->history_pos--;
		ft_strdel(cmd);
		*cmd = ft_strdup("");
		show_new(*cmd, termcaps, 0);
	}
	termcaps->cmd_len = ft_strlen(*cmd);
	termcaps->pos = ft_strlen(*cmd);
}
