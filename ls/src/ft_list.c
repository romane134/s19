/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:33:15 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/21 19:46:47 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_file			*ft_list(char **file, int i)
{
	t_file			*list;
	struct stat		s;
	t_file			*start;

	list = NULL;
	start = NULL;
	while (file[i] != '\0')
	{
		if (stat(file[i], &s) == 0)
		{
			list = ft_elem_list(file[i]);
			if (start == NULL)
				start = list;
			i++;
			//printf ("%s\n", list->name);
			list = list->next;
		}
		else
			i++;
	}
	//printf ("%s\n", start->name);
	//printf ("%s\n", start->next->name);
	return (start);
}

t_file			*ft_elem_list(char *file)
{
	t_file		*list;

	if (!(list = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	list->name = file;
	//list->stat = s;
	list->next = NULL;
	return (list);
}
