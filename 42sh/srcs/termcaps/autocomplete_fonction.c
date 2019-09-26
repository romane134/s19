/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_fonction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:58:13 by smondesi          #+#    #+#             */
/*   Updated: 2019/06/10 11:58:18 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			ft_strcmpstart(char *str, char *find)
{
	int i;

	i = 0;
	while (str[i] && find[i] && str[i] == find[i])
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

t_filename	*ft_add_list(t_filename *li, char *data)
{
	t_filename *element;
	t_filename *temp;

	if (!(element = malloc(sizeof(*element))))
		return (NULL);
	element->file = ft_strdup(data);
	element->next = NULL;
	if (li == NULL)
		return (element);
	temp = li;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = element;
	return (li);
}

int			ft_list_lenght(t_filename *li)
{
	int i;

	i = 0;
	while (li)
	{
		i++;
		li = li->next;
	}
	return (i);
}

char		*ft_last_ch(char *str)
{
	int end;

	if (!ft_strchr(str, '/'))
		return (str);
	end = ft_strlen(str);
	while (str[end] != '/')
		end--;
	return (&str[end + 1]);
}

void		ft_del_list(t_filename *li)
{
	t_filename *tmp;

	while (li)
	{
		tmp = li->next;
		ft_strdel(&li->file);
		ft_memdel((void **)&li);
		li = tmp;
	}
}
