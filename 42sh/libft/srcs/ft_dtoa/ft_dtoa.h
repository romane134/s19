/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 15:14:44 by vjovanov          #+#    #+#             */
/*   Updated: 2018/12/07 13:13:26 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DTOA_H
# define FT_DTOA_H

# include "libft.h"

# ifndef CHAR_BIT
#  define CHAR_BIT __CHAR_BIT__
# endif

# define MANT_BIT_64 52
# define EXP_BIT_64 11
# define EXP_BIAS_64 1023

char		*ft_dtoa(double n);
long double ft_exp_d(long double n, int exp);
int			set_size_array_d(double n);
int			set_before_comma_d(double n);

#endif
