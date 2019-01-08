/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 11:40:30 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/11/05 11:43:03 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include "libft/include/libft.h"
# include <unistd.h>
# include <locale.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_printf(const char * restrict format, ...);

#endif
