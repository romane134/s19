/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 13:55:33 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/16 13:55:47 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 *  ** @ means the file has extended attributes. Use listxattr() to get a list
 *   ** of the names of all the extended attributes, and getxattr() to get the
 *    ** value of a particular attribute. If listxattr returns a non-zero result,
 *     ** you would display @ to indicate this.
 *      */


/* savoir si @, +, - !!!!!
 *  *
 *   * acl_t acl = NULL;
 *    acl_entry_t dummy;
 *     ssize_t xattr = 0;
 *      char str[10];
 *       char * filename = "/Applications";
 *
 *        acl = acl_get_link_np(filename, ACL_TYPE_EXTENDED);
 *         if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1) {
 *          acl_free(acl);
 *           acl = NULL;
 *            }
 *             xattr = listxattr(filename, NULL, 0, XATTR_NOFOLLOW);
 *              if (xattr < 0)
 *               xattr = 0;
 *
 *                str[1] = '\0';
 *                 if (xattr > 0)
 *                  str[0] = '@';
 *                   else if (acl != NULL)
 *                    str[0] = '+';
 *                     else
 *                      str[0] = ' ';
 *
 *                       printf("%s\n", str);
 *                        */
