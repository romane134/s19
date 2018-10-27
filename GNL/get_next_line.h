/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:31:31 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/22 12:32:52 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LIGNE_H
# define GET_NEXT_LIGNE_H
# define BUFF_SIZE 14

#include "libft/libft.h"
#include <sys/types.h>
//#include <sys/uio.h>
int		get_next_line(const int fd, char **line);

#endif