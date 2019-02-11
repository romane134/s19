/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 13:38:41 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/02/11 10:35:37 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			ft_verif(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		if ((ft_strlen(argv[i]) == 0))
		{
			st_printf_error("ls: fts_open: No such file or directory\n");
			exit(0);
		}
		i++;
	}
}

void			ft_recur(int flag, t_test *file)
{
	t_test	*child;

	child = NULL;
	while (file != NULL)
	{
		if (file->list.mode[0] == 'd' && ft_strcmp(file->list.name, ".") != 0 &&
				ft_strcmp(file->list.name, "..") != 0)
		{
			st_printf("\n%s:\n", file->list.path);
			child = lecture(flag, file->list.path);
			ft_sort(flag, child);
			ft_free_list(child);
		}
		file = file->next;
	}
	ft_free_list(file);
}

int				main(int argc, char **argv)
{
	int			var[5];
	t_test		*file;
	t_test		*list;

	var[4] = argc;
	var[2] = 0;
	var[0] = 0;
	file = NULL;
	ft_verif(argv);
	var[1] = ft_flag(argv, &var[0]);
	if (var[1] == argc)
	{
		file = lecture(var[0], ".");
		ft_sort(var[0], file);
	}
	if ((argc - var[1]) >= 1)
	{
		argv = ft_sort_argv(argv, var[1]);
		list = ft_list_file(argv, var[1], var);
		ft_suite(var, file, list);
	}
	return (0);
}

void			ft_suite(int *var, t_test *file, t_test *list)
{
	t_test		*debut;
	int			i;

	i = 0;
	sort_list(list);
	list = ft_sort_list(var[0], list);
	var[3] = ft_link(var[0], list);
	file = ft_file(list, var[3]);
	debut = file;
	while (file)
	{
		file = ft_lecture_file(var[0], &file);
		file->list.tot = 0;
		file = file->next;
		i++;
	}
	ft_sort(var[0], debut);
	if ((debut != NULL) && (i < (var[2])))
		st_printf("\n");
	ft_list_document(list, var[0], (var[4] - var[1]), var[3]);
}
