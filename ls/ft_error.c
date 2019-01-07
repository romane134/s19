/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 15:53:41 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/07 16:03:28 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "../libft/includes/libft.h"
int main ()
{
	FILE *fp;

	fp = fopen("file.txt","r");
	if(fp == NULL )
	{
		nt_printf("Error:  %s\n", strerror(errno));
	}

	return(0);
}

