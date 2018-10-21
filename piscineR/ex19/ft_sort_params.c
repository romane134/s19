/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 13:35:01 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/01 13:50:47 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c);

void	ft_putstr(char *str)
{
	int a;

	a = 0;
	while (str[a] != '\0')
	{
		ft_putchar(str[a]);
		a++;
	}
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if ((s1[i] == '\0' && s2[i] != '\0') || (s2[i] == '\0' && s1[i] != '\0'))
		return (s1[i] - s2[i]);
	return (0);
}

void	ft_print_params(int argc, char **argv)
{
	int a;

	a = 1;
	while (a < argc)
	{
		ft_putstr(argv[a]);
		ft_putchar('\n');
		a++;
	}
}

int		main(int argc, char **argv)
{
	int a;

	a = 0;
	while (a < (argc))
	{
		a++;
		if (a + 1 < argc && ft_strcmp(argv[a + 1], argv[a]) < 0)
		{
			argv[argc + 1] = argv[a];
			argv[a] = argv[a + 1];
			argv[a + 1] = argv[argc + 1];
			a = 0;
		}
	}
	ft_print_params(argc, argv);
	return (0);
}
