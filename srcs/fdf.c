/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:44:55 by sdjeghba          #+#    #+#             */
/*   Updated: 2017/11/22 17:02:24 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int			key_hook(int keycode, t_data *e)
{
	(void)e;
	if (keycode == ESC)
		exit(0);
	ft_putendl(ft_itoa(keycode));
	return (0);
}

int			fdf(char **av)
{
	t_data	data;
	t_list	*map;
	t_img	img;

	map = NULL;
	data.win_width = 1440;
	data.win_height = 900;
	get_map(av, &map, &data);
	data.mlx = mlx_init();
	create_img(&data, &img);
	data.win = mlx_new_window(data.mlx, data.win_width, data.win_height, "42");
	mlx_key_hook(data.win, key_hook, &data);
	mlx_put_image_to_window(data.mlx, data.win, img.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
