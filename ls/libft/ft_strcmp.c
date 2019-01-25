/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 11:10:38 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/18 13:23:02 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *str1, const char *str2)
{
	int i;

	i = 0;
	while (str1[i] == str2[i] && str1[i] && str2[i])
		i++;
	if (str1[i] != str2[i])
		return ((unsigned char)(str1[i]) - (unsigned char)(str2[i]));
	if (str1[i] == '\0' && str2[i] == '\0')
		return (0);
	return (1);
}
