/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_andif.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 18:22:18 by vjovanov          #+#    #+#             */
/*   Updated: 2019/07/06 18:51:25 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Gestion du token &&
*/

int		exec_andif(t_token *ast, char ***env)
{
	int ret;

	ret = 0;
	if ((ret = exec(ast->left, env)) == 0)
	{
		ret = exec(ast->right, env);
		return (ret);
	}
	return (ret);
}
