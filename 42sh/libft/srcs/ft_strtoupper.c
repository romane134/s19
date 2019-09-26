/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 10:40:14 by bjovanov          #+#    #+#             */
/*   Updated: 2019/01/11 10:40:15 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** NAME:
** 	ft_strtoupper
**
** DESCRIPTION:
**	ft_strtoupper() met en majuscule la chaine de caractere s
**
** SYNOPSIS:
**	char *ft_strtoupper(char *s)
**
** PARAMS:
**	s - chaine de caractere a mettre en majuscule
**
** RETURN VALUE:
**	(char*) renvoie un pointeur sur s
*/

char	*ft_strtoupper(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (ft_islower(s[i]))
			s[i] = ft_toupper(s[i]);
		i++;
	}
	return (s);
}
