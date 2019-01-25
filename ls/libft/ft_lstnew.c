/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:16:05 by smondesi          #+#    #+#             */
/*   Updated: 2018/12/07 14:30:03 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;
	void	*ccontent;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL || content_size == 0)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else if (content != NULL)
	{
		ccontent = ft_memalloc(content_size);
		ft_memcpy(ccontent, content, content_size);
		new->content = ccontent;
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}
