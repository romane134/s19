/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 11:43:01 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/08 11:57:49 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Prend en paramètre l’adresse d’un pointeur sur un maillon et
** libère la mémoire de ce maillon et celle de tous ses successeurs
** l’un après l’autre avec del et free(3). Pour terminer,
** le pointeur sur le premier maillon maintenant libéré doit être
** mis à NULL (de manière similaire à la fonction ft_memdel de
** la partie obligatoire).
*/
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*nextone;

	while (*alst)
	{
		nextone = (*alst)->next;
		del((*alst)->content, (*alst)->content_size);
		free((*alst);
		((*alst) = nextone)
	}
(*alst) = NULL;
}
