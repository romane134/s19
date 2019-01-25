/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 09:46:55 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/22 18:06:32 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		*count_lettre(char const *s, int *stock, char c)
{
	int		i;
	int		lettre;
	int		j;

	i = 0;
	j = 0;
	lettre = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			lettre++;
		}
		stock[j] = lettre + 1;
		j++;
		lettre = 0;
	}
	return (stock);
}

static	void	tableau(const char *s, char **tab, char c)
{
	int		a;
	int		i;
	int		j;

	a = 0;
	i = 0;
	while (s[a])
	{
		j = 0;
		while (s[a] == c)
		{
			a++;
		}
		if (s[a] == '\0')
			break ;
		while (s[a] != c && s[a] != '\0')
		{
			tab[i][j] = s[a];
			j++;
			a++;
		}
		tab[i][j] = '\0';
		i++;
	}
	tab[i] = 0;
}

static void		free_tab(char **tab, int p)
{
	while (p--)
		free(tab[p]);
	free(tab);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		p;
	int		nb_mots;
	int		stock[ft_count_words(s, c)];
	int		*lettre;

	if (s == NULL)
		return (NULL);
	nb_mots = ft_count_words(s, c);
	lettre = count_lettre(s, stock, c);
	p = 0;
	if ((tab = (char**)malloc(sizeof(char*) * (nb_mots + 1))) == NULL)
		return (NULL);
	while (p < nb_mots)
	{
		if ((tab[p] = (char*)malloc(sizeof(char) * (lettre[p]))) == NULL)
		{
			free_tab(tab, p);
			return (NULL);
		}
		p++;
	}
	tableau(s, tab, c);
	return (tab);
}
