/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 15:21:13 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/20 17:41:25 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
/*t_file			tri_list(t_file *list)
{

}*/

t_file			*ft_list(char **file, int i)
{
	t_file			*list;
	struct stat		s;
	t_file			*start;

	if (!(list = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	start = list;
	while (file[i] != '\0')
	{
		if (stat(file[i], &s) == 0)
		{
			list = ft_elem_list(list, file[i]);
			list = list->next;
		}
		else
			i++;
		printf ("%s\n", list->name);
		i++;
	}
	list->next = NULL;
	return (start);
}

t_file			*ft_elem_list(t_file *list, char *file)
{
	if (!(list = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	list->name = file;
	//list->stat = s;
	//list->next = NULL;
	return (list);
}
