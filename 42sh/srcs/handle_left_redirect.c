/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_left_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 14:38:59 by bjovanov          #+#    #+#             */
/*   Updated: 2019/08/01 17:36:06 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Free 2 chaines de caracteres
*/

static void		free_2_string(char **del1, char **del2)
{
	ft_strdel(del1);
	ft_strdel(del2);
}

/*
** Exemple de commande : cat << OUT
** La fonction reçoit "OUT" comme premier parametre et va appeler
** termcaps_main()
** pour creer une nouvelle ligne tant que la valeur de cette ligne n'est pas
** "OUT".
** Des que "OUT" est la valeur de la ligne, la fonction arrête de boucler
** et remplace le "OUT" du token par les differentes valeurs indiquees
**
** Exemple : cat << OUT
** newline: Test
** newline: Test2
** newline: OUT
**
** On a desormais cat << Test\nTest2 qu'on va pouvoir utiliser plus facilement
** lors de l'execution dans la fonction exec_redirect() du fichier
** exec_redirect.c
*/

static void		init_heredoc(t_token *out, t_termcaps *termcaps)
{
	char *line;
	char *tmp;
	char *result;

	if (out == NULL)
		return ;
	result = ft_strnew(0);
	while (1)
	{
		line = termcaps_main(termcaps, 0);
		if (g_shell->stop == 1)
		{
			free_2_string(&line, &result);
			break ;
		}
		if (ft_strequ(line, out->value))
			break ;
		expansions_handle(&line, g_shell->env);
		if (!(tmp = ft_str3join(result, line, "\n")))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		free_2_string(&line, &result);
		result = tmp;
	}
	free_2_string(&line, &(out->value));
	out->value = result;
}

/*
** Fonction appelee dans main.c
** Permet de gerer les heredoc (<<) avant l'execution de l'arbre
** Boucle sur les differents tokens crees par le lexeur et lorsqu'il s'agit
** d'un heredoc (<<), initialise le processus via init_heredoc()
*/

void			handle_left_redirect(t_token *list, t_termcaps *termcaps)
{
	t_token *tmp;

	tmp = list;
	while (tmp->next)
	{
		if (tmp->name == DLESS_TOKEN)
			init_heredoc(tmp->next, termcaps);
		tmp = tmp->next;
	}
}
