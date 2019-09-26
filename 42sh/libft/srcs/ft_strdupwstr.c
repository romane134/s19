/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupwstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 08:12:49 by bjovanov          #+#    #+#             */
/*   Updated: 2019/02/22 08:12:50 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_new_size(char *str, char *ban)
{
	int		i;
	int		new_size;
	size_t	banlength;

	i = 0;
	new_size = 0;
	banlength = ft_strlen(ban);
	while (str[i])
	{
		if (ft_strlen(&(str[i])) < banlength)
		{
			new_size += ft_strlen(&(str[i]));
			break ;
		}
		if (ft_strnequ(&(str[i]), ban, banlength))
		{
			i += banlength;
			continue ;
		}
		new_size++;
		i++;
	}
	return (new_size);
}

char	*ft_strdupwstr(char *str, char *ban)
{
	size_t	new_size;
	size_t	i;
	size_t	j;
	char	*new_str;

	if (str == NULL || ban == NULL)
		return (NULL);
	if (ban[0] == '\0')
		return (ft_strdup(str));
	new_size = get_new_size(str, ban);
	if (!(new_str = ft_strnew(new_size)))
		return (NULL);
	i = 0;
	j = -1;
	while (str[i])
	{
		if (ft_strnequ(&(str[i]), ban, ft_strlen(ban)))
		{
			i += ft_strlen(ban);
			continue ;
		}
		new_str[++j] = str[i];
		i++;
	}
	return (new_str);
}
