/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_left_redirect_extends.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:49:20 by bjovanov          #+#    #+#             */
/*   Updated: 2019/07/06 19:49:21 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	exec_child_dless_token(int fd[2], char *value)
{
	close(fd[0]);
	write(fd[1], value, ft_strlen(value));
	close(fd[1]);
	exit(EXIT_SUCCESS);
}
