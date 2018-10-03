/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 08:56:46 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/03 11:17:13 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strdup(const char *s)
{
	char	*copy;

	if (!(copy = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	ft_strcpy(copy, s);
	return (copy);
}

int		main()
{
	char a[90] = "aaaaa";

	printf("%s\n", ft_strdup(a));
	printf("%s\n", strdup(a));
	return (0);
}
