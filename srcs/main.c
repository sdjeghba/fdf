/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:13:30 by sdjeghba          #+#    #+#             */
/*   Updated: 2017/11/16 17:12:14 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>
/*
int       main()
{
  void  *mlx_init();
  int   bpp;
  int   sizeline;
  int   endian;
  int   *img;
  char  *data;
  void  *mlx_ptr;
  void  *win_ptr;
  int   pixel_nbr;

  pixel_nbr = 0;
  mlx_ptr = mlx_init();
  img = mlx_new_image(mlx_ptr, 300, 300);
  data = mlx_get_data_addr(img, &bpp, &sizeline, &endian);
  printf("%d, %d, %d\n", bpp, sizeline, endian);
  while (pixel_nbr < 360000)
    {
      data[pixel_nbr] = 50;
      pixel_nbr++;
    }
  win_ptr = mlx_new_window(mlx_ptr, 800, 800, "Fenetre de Astaroth");
  mlx_put_image_to_window(mlx_ptr, win_ptr, img, 250, 250);
  mlx_loop(mlx_ptr);
  return (0);
}*/

int			main(int ac, char **av)
{
	(void)ac;
	if (ac != 2)
		ft_putendl("usage: ./fdf imputfile");
	else
		fdf(av);
	return (0);
}
