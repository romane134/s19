/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_length.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjovanov <bjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 01:41:19 by bjovanov          #+#    #+#             */
/*   Updated: 2018/10/31 01:47:30 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_array_length(void **array1)
{
	int		count;
	char	**t;

	t = (char**)array1;
	count = 0;
	while (t[count])
		count++;
	return (count);
}
