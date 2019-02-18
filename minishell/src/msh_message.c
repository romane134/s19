/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_message.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 18:44:49 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/02/18 13:48:57 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void			msh_message(char *line, char **argv)
{
	if ((ft_strcmp(line, "echo") >= 0))
		msh_echo(line);
		if ((ft_strcmp(line, "ls") == 0))
		execve("/bin/ls", argv, NULL);
	else
		st_printf ("ERROR\n");
}
