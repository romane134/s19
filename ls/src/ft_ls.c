/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 13:38:41 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/20 17:42:41 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*t_file		ft_witch_type(t_file *list, int flag)
{
	t_file *start;
	while (list->next != NULL)
	{

	}
}*/


int			main(int argc, char **argv)
{
	int			flag;
	int			i;
//	struct stat	s;
	t_file		*list;

	(void)argc;
	flag = 0;
	i = ft_flag(argv, &flag);
	if (i >= argc)
	{
		lecture(flag, ".");
		return (0);
	}
	else
	{
		list = ft_list(argv, i);
			return (0);
		//ft_witch_type(list, flag);
	}

	return (0);
}
