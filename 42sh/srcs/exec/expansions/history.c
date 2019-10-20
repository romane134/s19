/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:52:30 by vjovanov          #+#    #+#             */
/*   Updated: 2019/08/29 17:45:33 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
 ** get_history_len()
 **
 ** fonction qui calcule le nombre de ligne de fichier historique en faisant un
 **< GNL
 ** et en incrementant un compteur. Avant il faut ouvrir le fichier et reset la
 ** variable statique avec 	"get_next_line(fd, &line, 1);"
 */

int		get_history_len(void)
{
	char	*history_path;
	char	*line;
	int		fd;
	int		history_len;

	line = NULL;
	history_path = ft_strjoin(getenv("HOME"), "/.42sh_history");
	if ((fd = open(history_path, O_RDWR | O_CREAT | O_APPEND,
					0777)) == -1)
		return (-1);
	ft_strdel(&history_path);
	history_len = 0;
	get_next_line(fd, &line, 1);
	while (get_next_line(fd, &line, 0))
	{
		history_len++;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
	return (history_len);
}

/*
 ** numeric_histo()
 **
 ** On recup la taille actuelel de l'historique (pas de la struct termcaps
 **< ici...)
 ** On atoi pour avoir le numero de la ligne a aller chercher, on verifie que
 **< c'est
 ** dans les conditions. Si c'est negatif on converti en positif pour avoir le
 **< bon
 ** On read_last_line sur le numero de la ligne qu'on veut
 ** ensuite on remplace dans cmd avec ft_streplace_first. Il faut recreer le mot
 ** a enlever avec le "!" d'ou le join
 */
 // FINIR !!!!!!!
 int		numeric_histo_util(char **cmd, int i, int num, int history_len)
 {
 	if ((*cmd + i)[0] == '-')
 	{
 		dprintf(2, "\n -: event not found");
 		ft_strdel(cmd);
 		*cmd = ft_strdup("");
 		return (-1);
 	}
 	if ((num > 0 && num > history_len) || (num < 0 && -num > history_len))
 	{
 		dprintf(2, "\n %d: event not found", num);
 		ft_strdel(cmd);
 		*cmd = ft_strdup("");
 		return (-1);
 	}
 	return (0);
 }

void	numeric_histo(char **cmd, int i)
{
	int		history_len;
	int		num;
	char	*remplacement;
	char	*tmp;
	char	*to_replace;

	history_len = get_history_len();
	num = ft_atoi(&(*cmd)[i]);
	if (numeric_histo_util(cmd, i, num, history_len) == -1)
		return ;
	num = (num < 0) ? history_len + num : num;
	if ((remplacement = read_last_line(num)) == NULL)
		return ;
	tmp = "!";
	to_replace = ft_itoa(ft_atoi(&(*cmd)[i]));
	to_replace = ft_strjoin_free(&tmp, &to_replace, 1);
	tmp = *cmd;
	*cmd = ft_streplace_first(*cmd, to_replace, remplacement);
	ft_strdel(&tmp);
	ft_strdel(&to_replace);
	ft_strdel(&remplacement);
}

/*
 ** last_histo()
 **
 ** Meme principe que numeric_histo() mais on sait quelle ligne aller chercher,
 ** la derniere. On fait -1 car on commence a 0 et get_history_len nous renvoie
 ** la taille
 */

void	last_histo(char **cmd)
{
	int		num;
	char	*remplacement;
	char	*tmp;

	num = get_history_len() - 1;
	if ((remplacement = read_last_line(num)) == NULL)
		return ;
	tmp = *cmd;
	*cmd = ft_streplace_first(*cmd, "!!", remplacement);
	ft_strdel(&tmp);
	ft_strdel(&remplacement);
}

/*
 ** word_histo()       !! le len en param sert uniquement a etre a la norme !!
 **
 ** Si on a un mot qui suit le "!" on va calculer la lengueur de ce mot pour le
 ** remalloc comme "mot a chercher / mot a remplacer" et faire une recherche dans
 **<
 ** l'historique dessus. Si il recoit null, c'est qu'il n'existe pas, on met un
 ** message d'erreur et on return NULL en commande pour interrompre cell-ci
 ** Si on reçoit un resultat, on va le remplacer dans la commande avec
 ** ft_streplace_first. Il faut recreer le mot a enlever avec le "!" d'ou le join
 */

void	word_histo(char **cmd, int i, int len)
{
	char	*to_replace;
	char	*remplacement;
	char	*tmp;

	len = 0;
	while ((*cmd)[i + len] && ft_isspace((*cmd)[i + len]) == 0)
		len++;
	to_replace = ft_strndup(&(*cmd)[i], len);
	if ((remplacement = result_reasearch_without_termcaps(to_replace)) == NULL)
	{
		ft_printf("\n42sh: !%s: event not found", to_replace);
		ft_strdel(&to_replace);
		ft_strdel(cmd);
		return ;
	}
	tmp = "!";
	to_replace = ft_strjoin_free(&tmp, &to_replace, 1);
	if (remplacement != NULL)
	{
		tmp = *cmd;
		*cmd = ft_streplace_first(*cmd, to_replace, remplacement);
		ft_strdel(&tmp);
	}
	ft_strdel(&remplacement);
	ft_strdel(&to_replace);
}

/*
 ** expansion_history()
 **
 ** Va regarder si il y a un "!" et regarder si c'est suivi par un chiffre,
 ** une lettre ou un ! et lancer la fonction qui gere le cas
 **
 ** VIKTOR:
 ** Donc premiere amelioration, il faut verifier que le ! n'est pas escape
 **
 ** Ensuite, meme chose que pour les dollars, il faut conserver un historique
 ** des quotes.
 ** Car si je fais "!!", ca fonctionne car le double quote n'echappe pas les !
 ** Par contre, si je fais '!!', il ne faut pas remplacer les !! car les quotes
 ** echappent les !!
 **
 ** Donc j'ai la premiere grosse condition qui me permet de savoir quels quotes
 ** ont ete ouvert, et si ils ont ete fermes avant de rentrer dans la condition
 ** où on tombe sur un !, dans ce cas on s'en fout completement.
 **
 ** Donc, j'ai mon historique de quote, et lorsque je tombe sur !, je verifie que
 ** le quote ouvrant actuel n'est pas un quote simple. Sinon dans ce cas, je ne
 ** rentre pas dans la condition
 */

 /*
  ** Petit point sur cette condition.
  ** Un quote echappe un dquote tandis qu'un dquote echappe un quote.
  ** D'ou l'interet de cette condition car si il y a deja un quote/dquote qui est active
  ** alors c'est impossible de pouvoir activer un nouveau quote tant qu'on a pas ferme le dernier
  ** Exemple: "'ls'", ici malgre que c'est le quote qui a la possibilite d'echapper le plus, le fait qu'il soit entre dquote fait qu'il n'a aucun pouvoir, il ne fait rien
  ** C'est donc pour ca ici qu'on verifie simplement que l'historique est vide
  ** car du fait qu'on ne verifie que les quotes et dquote, on ne peut que avoir
  ** un seul quote active a la fois, donc un seul element a la fois dans l'historique
  */

int		expansion_history(char **cmd)
{
	t_history	*history;
	int		i;

	i = -1;
	history = NULL;
	while (*cmd && (*cmd)[++i])
	{
		if (((*cmd)[i] == '"' || (*cmd)[i] == '\'') && !is_escaped(*cmd, i)) // Verifie si on tombe sur un quote ou dquote et si oui, verifie si il est pas echappe
		{
			if (ft_strnequ(get_last_history_closing(history), &((*cmd)[i]), 1)) // On recupere le dernier quote ouvrant et on demande a recuperer la valeur qui permet de le close et ensuite on le compare avec notre quote actuel pour savoir si notre quote actuel peut fermer le quote ouvert.
			{
				remove_last_history(&history); // Si le quote actuel peut effectivement fermer le quote ouvrant active, dans ce cas, on enleve le quote ouvrant de l'historique et on continue
				continue ;
			}
			if (get_last_history_closing(history) == NULL) // Sinon, on verifie que l'historique est vide avant d'aller rajouter un quote a l'historique.
				add_history(&history, (*cmd)[i] == '"' ? "\"" : "'",
						(*cmd)[i] == '"' ? "\"" : "'");
		}
		if ((*cmd)[i] == '!' && !is_escaped(*cmd, i)
				&& !ft_strequ(get_last_history_opening(history), "'")) // On verifie que le ! n'est pas escape et que le dernier quote qui a ete ouvert n'est pas un quote simple car si oui, cela veut dire qu'il echappe les ! et qu'il ne faut donc pas convertir les !! en valeur
		{
			if (ft_isdigit((*cmd)[i + 1]) || (*cmd)[i + 1] == '-')
				numeric_histo(cmd, i + 1);
			else if (ft_isalpha((*cmd)[i + 1]))
				word_histo(cmd, i + 1, 0);
			else if ((*cmd)[i + 1] == '!')
				last_histo(cmd);
			else
				continue ;
			i = 0;
		}
	}
	if (!*cmd)
		return (0);
	else
		return (1);
}
