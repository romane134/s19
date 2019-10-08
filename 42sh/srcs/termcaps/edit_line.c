/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstinglh <sstinglh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 13:55:02 by sstinglh          #+#    #+#             */
/*   Updated: 2019/06/23 01:09:51 by sstinglh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**remove_previous_char()
** Cette fonction va enlever le caractere avant le curseur
** On malloc la taille de la 1ere partie (jusque pos - 1)
**	(on malloc plus tard la suite)
** On copie la cmd de base jusqu'a pos - 1
** On avance d'un caractere (celui qu'on remove)
** On join avec le reste de la cmd de base
** On free la commande de base et retourne la nouvelle
*/
int debug_1()
{
	return (open("/Users/rlucas-d/Documents/42sh/debug_1",  O_RDWR | O_CREAT | O_APPEND,
					0755));
}

char	*remove_previous_char(char *str, t_termcaps *termcaps)
{
	char	*new;
	char	*tmp;
	int		i;

	tmp = str;
	i = 0;
	if (termcaps->cmd_len == 0 || termcaps->pos == 0)
		return (str);
	new = ft_strnew(termcaps->cmd_len * sizeof(char*));
	while (i < termcaps->pos - 1)
	{
		new[i++] = *str;
		str++;
	}
	str++;
	new = ft_strjoin_free(&new, &str, 0);
	ft_strdel(&tmp);
	return (new);
}

/*
**remove_next_char()
** Cette fonction va enlever le caractere apres le curseur
** On malloc la taille de la 1ere partie (jusque pos)
**	(on malloc plus tard la suite)
** On copie la cmd de base jusqu'a pos
** On avance d'un caractere (celui qu'on remove)
** On join avec le reste de la cmd de base
** On free la commande de base et retourne la nouvelle
*/

char	*remove_next_char(char *str, t_termcaps *termcaps)
{
	char	*new;
	char	*tmp;
	int		i;

	tmp = str;
	i = 0;
	if (termcaps->cmd_len == 0)
		return (str);
	new = ft_strnew(termcaps->pos * sizeof(char*));
	while (i < termcaps->pos)
	{
		new[i++] = *str;
		str++;
	}
	str++;
	new = ft_strjoin_free(&new, &str, 0);
	ft_strdel(&tmp);
	return (new);
}

/*
** add_char()
** Cette fonction va ajouter une string ou se trouve le curseur
** On malloc la taille de la 1ere partie (jusque pos)
**	(on malloc plus tard ce qu'on ajoute)
** On copie la cmd de base jusqu'a pos
** ensuite on join avec buff(la string a intercaller)
** On join avec le reste de la cmd de base
** On free la commande de base et retourne la nouvelle
*/

void		add_char(char **str, char *buff)
{
	char	*new;

	new = ft_strnew((ft_strlen(*str) + ft_strlen(buff)));
	new = ft_strjoin_free(str, &buff, 0);
	ft_strdel(str);
	*str = ft_strdup(new);
	ft_strdel(&new);
}

void	del_line(t_termcaps *termcaps)
{
	tputs(termcaps->curs_save, 1, (void *)ft_putchar);
	tputs(tgoto(termcaps->gostart, 0, 0), 1, (void *)ft_putchar);
	tputs(termcaps->del_line, 1, (void *)ft_putchar);
}

int		isprintable(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (!ft_isprint(str[i]))
			return (0);
	return (1);
}
