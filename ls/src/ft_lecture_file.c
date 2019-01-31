/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lecture_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 16:02:30 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/31 17:23:24 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_test				*ft_lecture_file(int flag, char *doc)
{
	t_file		file;
	t_test		*element;

	file.name = doc;
	if ((flag & A_FLAG) == A_FLAG && doc[0] != '.')
		return (0);
	file.flag = flag;
	file.path = ft_strjoin("./", file.name);
	printf ("%s\n", file.path);
	ft_inspect_file(&file);
	element = malloc(sizeof(*element));
	element->doki = file;
	return (element);
}

void		ft_print_file(t_test *li)
{
	t_space i;

	if (li == NULL)
		return ;
	ft_totspace(li, &i);
	if ((li->doki.flag & L_FLAG) == L_FLAG)
		st_printf("total %d\n", ft_tot_blks(li));
		if ((li->doki.flag & S_FLAG) == S_FLAG)
			st_printf("%d ", li->doki.blks);
		if ((li->doki.flag & L_FLAG) == L_FLAG)
			print_list_2(li, i);
		else
			st_printf("%s\n", li->doki.name);
}
