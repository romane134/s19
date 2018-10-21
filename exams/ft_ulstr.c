/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 08:51:04 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/17 11:37:35 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		main(int argc, char **argv)
{
	int a;

	a = 0;
	if (argc == 2)
	{
		while (argv[1][a])
		{
			if (*argv[a] >= 'A' && *argv[a] <= 'Z')
				*argv[a] = *argv[a + 32];
			if (*argv[a] >= 'a' && *argv[a] <= 'z')
				*argv[a] = *argv[a - 32];
			write (1, &argv[1][a], 1);
			a++;
		}

	}
	write (1, "\n", 1);
	return (0);
}
