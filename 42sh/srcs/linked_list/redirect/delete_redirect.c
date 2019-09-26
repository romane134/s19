/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:30:12 by bcedric           #+#    #+#             */
/*   Updated: 2019/06/10 18:30:13 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		delete_redirect(t_redirect **redirect, int status)
{
	t_redirect *item;

	item = NULL;
	while (*redirect)
	{
		item = *redirect;
		*redirect = (*redirect)->next;
		ft_strdel(&(item->path));
		free(item);
	}
	redirect = NULL;
	return (status);
}
