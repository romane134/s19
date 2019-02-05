/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 17:56:40 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/22 18:06:06 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_words(char const *s, char c)
{
	int		i;
	int		mots;

	mots = 0;
	i = 0;
	if (s != NULL)
	{
		while (s[i])
		{
			while (s[i] == c)
				i++;
			if (s[i] != c && s[i] != '\0')
				mots++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		return (mots);
	}
	return (0);
}
