/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 06:23:38 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/05 07:49:28 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int        ft_a(void)
{
	char    a[50] = "a";
	char    b[50] = "e";
	printf("****ft_memcmp->>>>%d\n", ft_memcmp(a, b, 5));
	printf("****memcmp--->>>>%d\n", memcmp(a, b, 5));
	return (0);
}
int        ft_b(void)
{
	char c[] = "asdfgh";
	int a;

	a = 'h';
	printf("ft_strchr------>%s\n", ft_strchr(c, a));
	printf("strchr------>%s\n", strchr(c, a));
	return (0);
}


int        ft_c(void)
{
	char c[] = "coucou ";
	char d[] = "ca va?";
	printf("ft_strjoin --->%s\n",ft_strjoin(c, d));
	return (0);
}

int        ft_d(void)
{
	char c[] = "ashdfgahiiaii";

	printf("ft_strchr------>%s\n", ft_strrchr(c, 'a'));
	printf("strchr--------->%s\n", strrchr(c, 'a'));
	return (0);
}
int		ft_e(void)
{
	char c[] = "coucou ";
	char d[] = "ca va?";
	printf("ft_strncpy ---> %s\n", ft_strncpy(c, d, 4));
	printf("strncpy--- > %s\n", strncpy(c, d, 4));
	return (0);
}

int		ft_f(void)
{ 
	char c[] = "coucou ";
	char d[] = "ca va?";
	printf("ft_strcpy ---> %s\n", ft_strcpy(c, d));
	printf("strcpy--- > %s\n", strcpy(c, d));
	return (0);
}

int		ft_g(void)
{
	const char *s;

	s = "ahahah";
	printf("ft_strlen --> %zu\n", ft_strlen(s));
	printf ("strlen --> %lu\n", strlen(s));
	return (0);
}

int		ft_h(void)
{
	char c[] = "iiioiqwp";
	char d[] = "iiifv";

	printf("ft_strstr ---> %s\n", ft_strstr(c, d));
	printf("strstr--- > %s\n", strstr(c, d));
	return (0);
}

int		ft_i(void)
{
	char c[] = "coucou  gddhgjv h";

	printf("ft_strdup ---> %s\n", ft_strdup(c));
	printf("strup--- > %s\n", strdup(c));
	return (0);
}

int	ft_j(void)
{
	char c[] = "coucou ";
	char d[] = "sasdasdasd";
	printf("ft_strcmp ---> %d\n", ft_strcmp(c, d));
	printf("strcmp--- > %d\n", strcmp(c, d));
	return (0);
}

int	ft_k(void)
{
	char a[55] = "salut";
	char b[55] = "sssttop";
	char c[55] = "salut";
	char d[55] = "sssttop";
	printf("ft_strcat------>%s\n", ft_strcat(a, b));
	printf("strcat--------->%s\n", strcat(c, d));
	return (0);
}

int	ft_l(void)
{
    void *c = "coucou ";
    
   	printf("ft_bezero ---> %d\n", ft_bzero('c', 4));
    printf("bzero--- > %d\n", bzero('c', 4));
	return (0);

}
int		main(void)
{
	int a;

	a = '1';
	ft_a();
	ft_b();
	ft_c();
	ft_d();
	ft_e();
	ft_f();
	ft_g();
	ft_h();
	ft_i();
	ft_j();
	ft_k();
	ft_l();
}
