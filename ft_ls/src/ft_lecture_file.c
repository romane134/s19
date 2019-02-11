/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lecture_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 16:02:30 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/02/10 17:01:17 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_test				*ft_lecture_file(int flag, t_test **file)
{
	(*file)->list.flag = flag;
	if ((*file)->list.name[0] == '/')
		(*file)->list.path = ft_strjoin("/", (*file)->list.name);
	else
		(*file)->list.path = ft_strjoin("./", (*file)->list.name);
	ft_inspect_file(&(*file)->list);
	if (!(*(file)))
		return (NULL);
	return ((*file));
}

void				ft_print_file(t_test *li)
{
	t_space		i;

	if (li == NULL)
		return ;
	ft_totspace(li, &i);
	if ((li->list.flag & L_FLAG) == L_FLAG)
		st_printf("total %d\n", ft_tot_blks(li));
	if ((li->list.flag & S_FLAG) == S_FLAG)
		st_printf("%d ", li->list.blks);
	if ((li->list.flag & L_FLAG) == L_FLAG)
		print_list_2(li, i);
	else
		st_printf("%s\n", li->list.name);
}
