/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 13:38:41 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/21 19:44:18 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*void	print_list(t_test *li)
{
	while (li != NULL)
	{
		printf("%s\n", li->doki.name);
		printf("%d\n", li->doki.size);
	*		printf("%s\n", li->date);
		 *		**		printf("%s\n", li->user);
		 *		**		printf("%s\n", li->mode);
		 *		
		li = li->next;
	}
}*/

void		sort_list(t_test *file)
{
	t_file tp;
	t_test *tmp;

	tmp = file;
	while (file->next != NULL)
	{
		if(ft_strcmp(file->doki.name, file->next->doki.name) > 0)
		{
			tp = file->doki;
			file->doki = file->next->doki;
			file->next->doki = tp;
			file = tmp;
		}
		else
			file = file->next;
	}
	file = tmp;
	printf("\n");
	//print_list(file);
}

void	ft_printlist(t_file *debut)
{
	while (debut != NULL)
	{
		printf("%s\n", debut->name);
		debut = debut->next;
	}
}

int			main(int argc, char **argv)
{
	int			flag;
	int			i;
	//	struct stat	s;
	t_file		*list;
	t_test		*file;

	(void)argc;
	flag = 0;
	i = ft_flag(argv, &flag);
	if (i >= argc)
	{
		file = lecture(flag, ".");
		sort_list(file);
	}
	else
	{
		list = ft_list(argv, i);
		ft_printlist(list);
	//	while (list)
	//	{
			//printf ("coucou\n");
	//		file = lecture(flag, list->name);
			//printf ("%s\n", list->name);
		//	list = list->next;
		//	printf ("%s\n", list->name);

		//}
		//ft_witch_type(list, flag);
	}
	return (0);
}
