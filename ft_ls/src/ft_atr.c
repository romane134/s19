/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 11:36:27 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/02/10 16:47:58 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char		ft_atrib(t_file *file)
{
	char		c;
	acl_t		acl;
	acl_entry_t	entry;

	c = ' ';
	if (listxattr(file->path, NULL, 0, XATTR_NOFOLLOW) == -1)
	{
		if (errno == EPERM || errno == EACCES || errno == EFAULT)
			c = ' ';
	}
	else if (listxattr(file->path, NULL, 0, XATTR_NOFOLLOW) > 0)
		c = '@';
	acl = acl_get_link_np(file->path, ACL_TYPE_EXTENDED);
	if (!acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &entry) == -1)
		acl = NULL;
	if (acl)
		c = '+';
	acl_free(acl);
	return (c);
}
