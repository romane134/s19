/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:21:12 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/31 16:38:30 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/ft_ls.h"


static t_test			*ft_list(char *str)
{
	t_test *new;

	if (!(new = (t_test*)malloc(sizeof(t_test))))
		return (NULL);
	ft_strdup(str);
	new->doki.name = str;
	new->next = NULL;
	return (new);
}

static void		push_back(t_test **list, t_test *new)
{
	t_test *current;

	if (!(*list))
		*list = new;
	else
	{
		current = *list;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

t_test			*ft_list_file(char **argv, int start)
{
	t_test			*list;
	struct stat		s;

	list = NULL;
	while (argv[start] != '\0')
	{
		if ((stat(argv[start], &s) != -1))
			push_back(&list, ft_list(argv[start]));
		else
			printf ("ls: %s: %s\n", argv[start] ,strerror(errno));
		start++;
	}
	return (list);
}
