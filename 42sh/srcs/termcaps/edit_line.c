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

char	*remove_previous_char(char *str, t_termcaps *termcaps)
{
	char	*new;
	char	*tmp;
	int		i;

	tmp = str;
	i = 0;
	if (termcaps->cmd_len == 0 || termcaps->pos == 0)
		return (str);
	new = ft_strnew(termcaps->cmd_len);
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
	new = ft_strnew(termcaps->pos);
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

void		add_char_end(char **str, char *buff)
{
	char	*new;

	new = ft_strjoin(*str, buff);
	ft_strdel(str);
	*str = ft_strdup(new);
	ft_strdel(&new);
}

void		add_char(char **str, char *buff, t_termcaps *termcaps)
{
	int		i;
	int		j;
	char	*temp;
	char	*new;
	char	*tmp2;

	i = 0;
	j = -1;
	tmp2 = *str;
	temp = ft_strnew((ft_strlen(*str) + ft_strlen(buff)));
	while (i < termcaps->pos)
	{
		temp[i++] = **str;
		(*str)++;
	}
	while (buff[++j])
		temp[i++] = buff[j];
	new = ft_strjoin(temp, *str);
	ft_strdel(&temp);
	ft_strdel(&tmp2);
	*str = ft_strdup(new);
	ft_strdel(&new);
}

void	del_line(t_termcaps *termcaps)
{
	tputs(termcaps->curs_save, 1, (void *)ft_putchar);
	tputs(tgoto(termcaps->gostart, 0, 0), 1, (void *)ft_putchar);
	tputs(termcaps->del_line, 1, (void *)ft_putchar);
}

/*
** commande qui verifie que chaque caractere du buffer est imprimable
*/

int		isprintable(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (!ft_isprint(str[i]))
			return (0);
	return (1);
}
