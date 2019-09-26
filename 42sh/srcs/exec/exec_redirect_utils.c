/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 20:00:40 by bjovanov          #+#    #+#             */
/*   Updated: 2019/07/02 22:45:27 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		is_dash(char *fd)
{
	if (ft_strlen(fd) == 1 && fd[0] == '-')
		return (1);
	return (0);
}

int		is_valid_fd(char *fd)
{
	int i;

	i = 0;
	if (is_dash(fd))
		return (1);
	while (ft_isdigit(fd[i]))
		i++;
	return (fd[i] == '\0');
}

int		is_right_redirect(enum e_tokens name)
{
	if (name == DGREAT_TOKEN || name == GREATAND_TOKEN || name == GREAT_TOKEN ||
		name == ANDGREAT_TOKEN)
		return (1);
	return (0);
}

int		check_fd(char *fd)
{
	if (fd == NULL)
		return (1);
	if (fd[0] == '&')
		return (-2);
	return (ft_atoi(fd));
}
