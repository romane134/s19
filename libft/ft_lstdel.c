/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 11:43:01 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/16 20:33:19 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*nextone;

	if (!alst || !del)
		return ;
	while (*alst)
	{
		nextone = (*alst)->next;
		del((*alst)->content, (*alst)->content_size);
		free((*alst));
		((*alst) = nextone);
	}
	(*alst) = NULL;
}
