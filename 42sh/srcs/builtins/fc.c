/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstinglh <sstinglh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 21:35:46 by sstinglh          #+#    #+#             */
/*   Updated: 2019/08/23 15:46:46 by sstinglh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** fc_option_s()
**
** Recup un eventuelle "old=now" ensuite recup la ligne en first si il y en
** a sinon prendre la derniere et l'executer.
** Remplace old par new si ils sont present et execute.
** ! start_process() free result lors de son execution !
*/

int		fc_option_s(char **cmd, int i)
{
	int		x;
	char	*result;
	char	*tmp;
	char	**old_new;

	x = 0;
	old_new = NULL;
	if (cmd[i] && (ft_isalpha(cmd[i][x])))
	{
		if (ft_strchr(cmd[i], '='))
			old_new = ft_strsplit(&cmd[i++][x++], '=');
		else
			return (fc_error(1, cmd[i]));
	}
	result = read_last_line(get_first_last(cmd, i, &x, &x) - 1);
	if (old_new)
	{
		tmp = result;
		result = ft_streplace_first(result, old_new[0], old_new[1]);
		free_darray(old_new, 0);
		ft_strdel(&tmp);
	}
	ft_printf("%s\n", result);
	start_process(result);
	return (0);
}

/*
** fc_option_e()
**
** Le but est d'ouvrir une editeur de texte pour modifier les anciennes
** commandes et reexecuter celles ci si on a "-e".
**
** On essaie de choper l'editeur en fonction des variables d'environnement
**
** fc_option_l() va ecrire dans le fichier temporaire que lire l'editeur.
** On lance l'editeur avec le chemin du fichier temporaire.
** get_new_cmd() va recup la/les commande(s) modifiees dans le fichier et les
** separer par un ";"
** Ensuite on relance un process pour chaque commande.
*/

int		fc_option_e(int i, int g_bit, char **cmd)
{
	int		f;
	char	*new_cmd__editor;
	char	**to_start;

	if ((f = open("/tmp/.42sh_tmp_fc", O_RDWR | O_CREAT | O_TRUNC, 0755)) == -1)
		return (fc_error(2, NULL));
	if ((new_cmd__editor = get_editor(cmd, &i, g_bit)) == NULL)
		return (-1);
	fc_option_l(cmd, g_bit, i, f);
	close(f);
	start_process(ft_strjoin(new_cmd__editor, " /tmp/.42sh_tmp_fc"));
	ft_strdel(&new_cmd__editor);
	if (g_bit & FC_OPTION_E)
	{
		if ((new_cmd__editor = get_new_cmd()) == NULL)
			return (-1);
		to_start = ft_strsplit(new_cmd__editor, ';');
		ft_strdel(&new_cmd__editor);
	//Remove les 2 commandes precedentes ? (fc et editeur)
		i = 0;
		while (to_start && to_start[i] != '\0')
			start_process(to_start[i++]);
		free(to_start);
	}
	return (0);
}

/*
** builtin_fc()
**
** Lance les fonctions en fonction des parametres. Si on a 2 options
** incompatible on return une error
*/

int		builtin_fc(char **cmd)
{
	int		g_bit;
	int		i;

	g_bit = 0;
	if ((i = check_fc_option(cmd, &g_bit)) < 0)
		return (-1);
	if ((g_bit & FC_OPTION_L && g_bit & FC_OPTION_E) ||
		(g_bit & FC_OPTION_L && g_bit & FC_OPTION_S) ||
		(g_bit & FC_OPTION_E && g_bit & FC_OPTION_S))
		return (fc_error(0, NULL));
	if (g_bit & FC_OPTION_L)
		return (fc_option_l(cmd, g_bit, i, 0));
	if (g_bit & FC_OPTION_S)
		return (fc_option_s(cmd, i));
	return (fc_option_e(i, g_bit, cmd));
}
