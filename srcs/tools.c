/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:44:48 by sdjeghba          #+#    #+#             */
/*   Updated: 2017/11/23 13:26:02 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		set_pixel(int x, int y, t_img *img)
{
	int		i;

	i = (img->iwidth * img->iheight * 4) / 3 + (img->iwidth * 4) / 2;
	i += (x * 4) + (y * img->size_line);
	img->pixel[i++] = 126;
	img->pixel[i++] = 126;
	img->pixel[i++] = 126;
	img->pixel[i] = 0;
}

int			display_error(char *str)
{
	ft_putendl(str);
	exit(0);
	return (0);
}

/*void		do_bresenham(t_img *img, t_data *data)
{
	(void)data;
	if (img->p.x + 1 < data->tab_width)
	{
		img->p.x1 = img->vec.start_x;
		img->p.y1 = img->vec.start_y;
		img->p.x2 = img->vec.stop_x;
		img->p.y2 = img->vec.start_y;
		bresenham(img, data->tab[img->p.y][img->p.x]);
	}
	if (img->p.y + 1 < data->tab_height)
	{
		img->p.x1 = img->vec.start_x;
		img->p.y1 = img->vec.start_y;
		img->p.x2 = img->vec.stop_x;
		img->p.y2 = img->vec.stop_y;
		bresenham(img, data->tab[img->p.y][img->p.x]);
	}
}*/
