/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:44:48 by sdjeghba          #+#    #+#             */
/*   Updated: 2017/12/03 13:12:22 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int			draw_v(t_img *img, t_data *data)
{
	int		line;

	line = img->p.y + 1;
	img->p.x--;
	img->p.x1 = ((img->p.x - img->p.y) * img->zoomx) + (WIN_W / 2);
	img->p.y1 = ((img->p.x + img->p.y) * img->zoomy) -\
				(data->tab[img->p.y][img->p.x] * 3) + (WIN_H / 6);
	img->p.x2 = ((img->p.x - line) * img->zoomx) + (WIN_W / 2);
	img->p.y2 = ((img->p.x + line) * img->zoomy) -\
				(data->tab[line][img->p.x] * 3) + (WIN_H / 6);
	img->p.x++;
	bresenham(img, data);
	return (0);
}

int			draw_h(t_img *img, t_data *data)
{
	img->p.x1 = ((img->p.x - img->p.y) * img->zoomx) + (WIN_W / 2);
	img->p.y1 = ((img->p.x + img->p.y) * img->zoomy) -\
				(data->tab[img->p.y][img->p.x] * 3) + (WIN_H / 6);
	img->p.x++;
	img->p.x2 = ((img->p.x - img->p.y) * img->zoomx) + (WIN_W / 2);
	img->p.y2 = ((img->p.x + img->p.y) * img->zoomy) -\
				(data->tab[img->p.y][img->p.x] * 3) + (WIN_H / 6);
	bresenham(img, data);
	return (0);
}


int			key_hook(int keycode, t_data *e)
{
	keycode == ESC ? exit(0) : 0;
	keycode == 27 && e->zoom < 10 ? e->zoom++ : 0;
	keycode == 24 && e->zoom > 1 ? e->zoom-- : 0;
	e->side += (keycode == 123 ? 30 : 0);
	e->side -= (keycode == 124 ? 30 : 0);
	e->updown += (keycode == 126 ? 30 : 0);
	e->updown -= (keycode == 125 ? 30 : 0);
	if (keycode == 27 || keycode == 24 || keycode == 123 || keycode == 124 ||\
			keycode == 126 || keycode == 125)
		create_img(e);
	return (0);
}

void		set_pixel(int x, int y, t_img *img, t_data *data)
{
	int		i;

	if (x - data->side < 1 || x - data->side >= WIN_W || y - data->updown < 1 || y - data->updown >= WIN_H)
		return ;
	i = ((x - data->side) * 4) + (((y - data->updown) * img->size_line));
	if (i < (WIN_H * WIN_W * 4) && i > 0)
	{
		img->pixel[i++] = 126;
		img->pixel[i++] = 126;
		img->pixel[i++] = 126;
		img->pixel[i] = 0;
	}
}

int			display_error(char *str)
{
	ft_putendl(str);
	exit(0);
	return (0);
}
