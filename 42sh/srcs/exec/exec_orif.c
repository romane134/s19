/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_orif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 18:22:23 by vjovanov          #+#    #+#             */
/*   Updated: 2019/07/06 19:00:24 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Gestion du token ||
*/

int		exec_orif(t_token *ast, char ***env)
{
	int ret;

	ret = 0;
	if ((ret = exec(ast->left, env)) == 1)
	{
		ret = exec(ast->right, env);
		return (ret);
	}
	return (ret);
}
