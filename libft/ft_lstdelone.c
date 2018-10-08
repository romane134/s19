/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 10:37:03 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/08 11:54:29 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Prend en paramètre l’adresse d’un pointeur sur un maillon et
** libère la mémoire du contenu de ce maillon avec la fonction
** del passée en paramètre puis libère la mémoire du maillon
** en lui même avec free(3). La mémoire du champ next ne
** doit en aucun cas être libérée. Pour terminer, le pointeur sur
** le maillon maintenant libéré doit être mis à NULL (de manière
** similaire à la fonction ft_memdel de la partie obligatoire).
*/
#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}
