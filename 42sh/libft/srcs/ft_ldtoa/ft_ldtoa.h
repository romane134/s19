/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 12:55:55 by vjovanov          #+#    #+#             */
/*   Updated: 2018/12/07 14:04:54 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LDTOA_H
# define FT_LDTOA_H

# include "libft.h"

# ifndef CHAR_BIT
#  define CHAR_BIT __CHAR_BIT__
# endif

# define MANT_BIT_64_LD 64
# define EXP_BIT_64_LD 15
# define EXP_BIAS_64_LD 16383
# define EXTENDED_PRECISION_SIZEOF 10

char		*ft_ldtoa(long double n);
long double ft_exp_ld(long double n, int exp);
int			set_size_array_ld(long double n);
int			set_before_comma_ld(long double n);

#endif
