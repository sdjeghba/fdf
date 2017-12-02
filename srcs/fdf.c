/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:44:55 by sdjeghba          #+#    #+#             */
/*   Updated: 2017/12/02 19:08:12 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int			draw_v(t_img *img, t_data *data)
{
	int		line;

	line = img->p.y + 1;
	img->p.x--;
	img->p.x1 = ((img->p.x - img->p.y) * img->spw_btw_pts) + (data->win_w / 2);
	img->p.y1 = ((img->p.x + img->p.y) * img->sph_btw_pts) -\
				(data->tab[img->p.y][img->p.x] * 3) + (data->win_h / 6);
	img->p.x2 = ((img->p.x - line) * img->spw_btw_pts) + (data->win_w / 2);
	img->p.y2 = ((img->p.x + line) * img->sph_btw_pts) -\
				(data->tab[line][img->p.x] * 3) + (data->win_h / 6);
	img->p.x++;
	bresenham(img, data);
	return (0);
}

int			draw_h(t_img *img, t_data *data)
{
	img->p.x1 = ((img->p.x - img->p.y) * img->spw_btw_pts) + (data->win_w / 2);
	img->p.y1 = ((img->p.x + img->p.y) * img->sph_btw_pts) -\
				(data->tab[img->p.y][img->p.x] * 3) + (data->win_h / 6);
	img->p.x++;
	img->p.x2 = ((img->p.x - img->p.y) * img->spw_btw_pts) + (data->win_w / 2);
	img->p.y2 = ((img->p.x + img->p.y) * img->sph_btw_pts) -\
				(data->tab[img->p.y][img->p.x] * 3) + (data->win_h / 6);
	bresenham(img, data);
	return (0);
}

int			bresenham(t_img *img, t_data *data)
{
	img->a.dx = abs(img->p.x2 - img->p.x1);
	img->a.dy = abs(img->p.y2 - img->p.y1);
	img->a.sx = img->p.x1 < img->p.x2 ? 1 : -1;
	img->a.sy = img->p.y1 < img->p.y2 ? 1 : -1;
	img->a.err = (img->a.dx > img->a.dy ? img->a.dx : -img->a.dy) / 2;
	while (42)
	{
		if ((img->p.x1 > 1) && (img->p.x1 < data->win_w) && (img->p.y1 > 1)\
				&& (img->p.y1 < data->win_h))
			set_pixel(img->p.x1, img->p.y1, img);
		if (img->p.x1 == img->p.x2 && img->p.y1 == img->p.y2)
			break ;
		img->a.e = img->a.err;
		if (img->a.e > -img->a.dx)
		{
			img->a.err -= img->a.dy;
			img->p.x1 += img->a.sx;
		}
		if (img->a.e < img->a.dy)
		{
			img->a.err += img->a.dx;
			img->p.y1 += img->a.sy;
		}
	}
	return (0);
}

int			create_img(t_data *data, t_img *img)
{
	img->img = mlx_new_image(data->mlx, data->win_w, data->win_h);
	img->pixel = mlx_get_data_addr(img->img, &img->bpp,\
			&img->size_line, &img->endian);
	img->spw_btw_pts = ((data->win_w - data->tab_w) / data->tab_w) / 4;
	img->spw_btw_pts = (img->spw_btw_pts <= 0 ? 1 : img->spw_btw_pts);
	img->sph_btw_pts = ((data->win_h - data->tab_h) / data->tab_h) / 4;
	img->sph_btw_pts = (img->sph_btw_pts <= 0 ? 1 : img->sph_btw_pts);
	img->p.x = 0;
	img->p.y = 0;
	while (data->tab[img->p.y])
	{
		while ((img->p.x + 1) < data->tab_w)
		{
			draw_h(img, data);
			if (img->p.y + 1 < data->tab_h)
				draw_v(img, data);
		}
		img->p.x++;
		if (img->p.y + 1 < data->tab_h)
			draw_v(img, data);
		img->p.y++;
		img->p.x = 0;
	}
	return (0);
}

/*void		free_map(t_list **list)
{
	t_list	*tmp;

	tmp = NULL;
	while (*list)
	{
		tmp = (*list)->next;
	//	ft_putendl((*list)->content);
		ft_memdel((void**)&(*list)->content);
		(*list)->content_size = 0;
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}*/

/*void		free_tabint(t_data data)
{
	int		i;

	i = 0;
	while (i < data.tab_h)
	{
		ft_putendl("free tab");
		ft_memdel((void**)&data.tab[i++]);
	}
	data.tab = NULL;
	free(data.tab);
}*/

int			fdf(char **av)
{
	t_data	data;
	t_list	*map;
	t_img	img;

	map = NULL;
	data.win_w = 2000;
	data.win_h = 1200;
	get_map(av, &map, &data);
	data.mlx = mlx_init();
	create_img(&data, &img);
	data.win = mlx_new_window(data.mlx, data.win_w, data.win_h, "42");
	mlx_key_hook(data.win, key_hook, &data);
	mlx_put_image_to_window(data.mlx, data.win, img.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
