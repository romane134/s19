/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 09:13:22 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/12/11 09:13:24 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/ft_ls.h"

int   ft_flags(char **argv, DIR *rep)
{
  struct dirent *lecture;

  if ((argv[2] = "-a"))
  while ((lecture = readdir(rep)))
    nt_printf("%s\n", lecture->d_name);
  return (0);
}

int   main(int argc, char **argv)
{
  struct dirent *lecture;
  DIR *rep;

  rep = opendir(argv[1]);
  if (argv[2])
    ft_flags(argv, rep);
  else if (argc == 2)
    while ((lecture = readdir(rep)))
      {
        if ((ft_strcmp(lecture->d_name, ".")) && (ft_strcmp(lecture->d_name, "..")))
          {
              nt_printf("%s\n", lecture->d_name);
              analyse_file(lecture->d_name);
          }
      }
  return (0);
}
