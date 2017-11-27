/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 08:17:33 by sdjeghba          #+#    #+#             */
/*   Updated: 2017/11/23 13:26:01 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int			get_img_size(t_data *data, t_img *img)
{
	if (data->tab_width > data->tab_height)
	{
		img->iwidth = data->win_width ;
		img->iheight = data->win_height ;
	}
	else
	{
		img->iwidth = 900 ;
		img->iheight = 900;
	}
	return (0);
}

int			draw_v(t_img *img, t_data *data)
{
	int		line = img->p.y + 1;

	img->p.x--;
	img->p.x1 = (img->p.x - img->p.y) * (img->spw_btw_pts / 2);
	img->p.y1 = ((img->p.x + img->p.y) * (img->sph_btw_pts / 2)) - ((data->tab[img->p.y][img->p.x] * (img->sph_btw_pts * 1 / 10)) / 2);
	img->p.x2 = (img->p.x - line) * (img->spw_btw_pts / 2);
	img->p.y2 = ((img->p.x + line) * (img->sph_btw_pts / 2)) - ((data->tab[line][img->p.x] * (img->sph_btw_pts * 1 / 10)) / 2);
	img->p.x++;
	bresenham(img);
	return (0);
}

int			draw_h(t_img *img, t_data *data)
{
	img->p.x1 = (img->p.x - img->p.y) * (img->spw_btw_pts / 2);
	img->p.y1 = ((img->p.x + img->p.y) * (img->sph_btw_pts / 2)) - ((data->tab[img->p.y][img->p.x] * (img->sph_btw_pts * 1 / 10)) / 2);
	img->p.x++;
	img->p.x2 = (img->p.x - img->p.y) * (img->spw_btw_pts / 2);
	img->p.y2 = ((img->p.x + img->p.y) * (img->sph_btw_pts / 2)) - ((data->tab[img->p.y][img->p.x] * (img->sph_btw_pts * 1 / 10)) / 2);
	bresenham(img);
	return (0);
}

int			put_points_img(t_img *img, t_data *data)
{
	img->p.x = 0;
	img->p.y = 0;
	while (data->tab[img->p.y])
	{
		while ((img->p.x + 1) < data->tab_width)
		{
			draw_h(img, data);
			if (img->p.y + 1 < data->tab_height)
				draw_v(img, data);
		}
		img->p.x++;
		if (img->p.y + 1 < data->tab_height)
			draw_v(img, data);
		img->p.y++;
		img->p.x = 0;
	}
	return (0);
}

int			bresenham(t_img *img)
{
	img->bres->dx = abs(img->p.x2 - img->p.x1);
	img->bres->dy = abs(img->p.y2 - img->p.y1);
	img->bres->sx = img->p.x1 < img->p.x2 ? 1 : -1;
	img->bres->sy = img->p.y1 < img->p.y2 ? 1 : -1;
	img->bres->err = (img->bres->dx > img->bres->dy ? img->bres->dx : -img->bres->dy) / 2;
	while (42)
	{
		set_pixel(img->p.x1, img->p.y1, img);
		if (img->p.x1 == img->p.x2 && img->p.y1 == img->p.y2)
			break;
		img->bres->e = img->bres->err;
		if (img->bres->e > -img->bres->dx)
		{
			img->bres->err -= img->bres->dy;
			img->p.x1 += img->bres->sx;
		}
		if (img->bres->e < img->bres->dy)
		{
			img->bres->err += img->bres->dx;
			img->p.y1 += img->bres->sy;
		}
	}
	return (0);
}

int			create_img(t_data *data, t_img *img)
{
	get_img_size(data, img);
	img->img = mlx_new_image(data->mlx, img->iwidth, img->iheight);
	img->pixel = mlx_get_data_addr(img->img, &img->bpp, &img->size_line, &img->endian);
	img->spw_btw_pts = ((img->iwidth - data->tab_width) / data->tab_width) / 2;
	img->sph_btw_pts = ((img->iheight - data->tab_height) / data->tab_height) / 2;
	put_points_img(img, data);
	return (0);
}

/*
	printf("img w: %d, img h: %d\n", img->iwidth, img->iheight);
	printf("tab w: %d, tab h: %d\n", data->tab_width, data->tab_height);
	printf("spw: %d, sphh: %d\n", img->spw_btw_pts, img->sph_btw_pts);
	printf("bpp: %d, size_line: %d, endian:%d\n", img->bpp, img->size_line, img->endian);
*/
