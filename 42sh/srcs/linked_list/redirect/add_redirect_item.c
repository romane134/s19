/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirect_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:56:31 by bcedric           #+#    #+#             */
/*   Updated: 2019/07/02 22:33:46 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			add_redirect_item(t_redirect **redirect, char *path,
				enum e_tokens name, int std)
{
	t_redirect *new;
	t_redirect *tmp;

	if (!(new = malloc(sizeof(*new))))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	if (!(new->path = ft_strdup(path)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	new->name = name;
	new->std = std;
	if (*redirect == NULL)
	{
		new->next = NULL;
		*redirect = new;
		return ;
	}
	tmp = *redirect;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
}
