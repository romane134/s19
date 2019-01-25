/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lecture_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 16:02:30 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/25 10:05:16 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_file				*ft_lecture_file(int flag, char *doc)
{
	t_file		*file;

	file = malloc(sizeof(*file));
	file->name = doc;
	if ((flag & A_FLAG) == A_FLAG && doc[0] != '.')
		return (0);
	file->flag = flag;
	file->path = ft_strjoin("./", file->name);
	ft_inspect_file(file->path, file);
//	free(file);
	return (file);
}
