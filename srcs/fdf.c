/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:44:55 by sdjeghba          #+#    #+#             */
/*   Updated: 2017/11/30 16:28:56 by sdjeghba         ###   ########.fr       */
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
	img->bres.dx = abs(img->p.x2 - img->p.x1);
	img->bres.dy = abs(img->p.y2 - img->p.y1);
	img->bres.sx = img->p.x1 < img->p.x2 ? 1 : -1;
	img->bres.sy = img->p.y1 < img->p.y2 ? 1 : -1;
	img->bres.err = (img->bres.dx > img->bres.dy ?\
			img->bres.dx : -img->bres.dy) / 2;
	while (42)
	{
		if ((img->p.x1 > 1) && (img->p.x1 < data->win_w) && (img->p.y1 > 1)\
				&& (img->p.y1 < data->win_h))
			set_pixel(img->p.x1, img->p.y1, img);
		if (img->p.x1 == img->p.x2 && img->p.y1 == img->p.y2)
			break ;
		img->bres.e = img->bres.err;
		if (img->bres.e > -img->bres.dx)
		{
			img->bres.err -= img->bres.dy;
			img->p.x1 += img->bres.sx;
		}
		if (img->bres.e < img->bres.dy)
		{
			img->bres.err += img->bres.dx;
			img->p.y1 += img->bres.sy;
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

void		free_map(t_list **list)
{
	t_list	*tmp;
	t_list	*tnext;

	tmp = *list;
	while (tmp->next)
	{
		tnext = tmp->next;
		ft_memdel((void**)&tmp->content);
		free(tmp);
		tmp = tmp->next;
	}
}

void		free_tabint(int	**tab)
{
	int		i;

	i = 0;
	while (tab[i])
		ft_memdel((void**)&tab[i++]);
	free(tab);
}

int			fdf(char **av)
{
	t_data	data;
	t_list	*map;
	t_img	img;

	map = NULL;
	data.win_w = 1490;
	data.win_h = 900;
	get_map(av, &map, &data);
	data.mlx = mlx_init();
	create_img(&data, &img);
//	free_map(&map);
	data.win = mlx_new_window(data.mlx, data.win_w, data.win_h, "42");
	mlx_key_hook(data.win, key_hook, &data);
	mlx_put_image_to_window(data.mlx, data.win, img.img, 0, 0);
//	free_tabint(data.tab);
	mlx_loop(data.mlx);
	return (0);
}
