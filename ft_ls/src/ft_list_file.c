/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 17:09:36 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/02/10 17:09:38 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char			**ft_sort_argv(char **argv, int i)
{
	char	*tmp;

	while (argv[i + 1] != '\0')
	{
		if ((ft_strcmp(argv[i], argv[i + 1]) > 0))
		{
			tmp = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = tmp;
		}
		else
			i++;
	}
	return (argv);
}

t_test			*ft_list(char *str)
{
	t_test *new;

	if (!(new = (t_test*)malloc(sizeof(t_test))))
		return (NULL);
	new->list.name = str;
	new->next = NULL;
	return (new);
}

void			push_back(t_test **list, t_test *new)
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

t_test			*ft_list_file(char **argv, int start, int *i)
{
	t_test			*list;
	struct stat		s;

	list = NULL;
	while (argv[start] != '\0')
	{
		if ((lstat(argv[start], &s) != -1))
		{
			if ((!(s.st_mode & S_IRUSR)))
				st_printf_error("ls: %s: Permission denied\n", argv[start]);
			else
				push_back(&list, ft_list(argv[start]));
			i[2]++;
		}
		else
			st_printf_error("ls: %s: %s\n", argv[start], strerror(errno));
		start++;
	}
	return (list);
}
