/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 19:33:03 by sdjeghba          #+#    #+#             */
/*   Updated: 2017/11/22 18:11:11 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int			iso_view(t_img *img, t_data *data)
{
	(void)data;
	void	*mlx;
	void	*win;
	int		*im;
	int		bpp;
	int		size_l;
	int		endian;
	char	*i;
	img->p.x = 0;
	img->p.y = 0;
	int nx;
	int	ny;

	nx = 0;
	ny = 0;
	mlx = mlx_init();
	im = mlx_new_image(mlx, img->iwidth, img->iheight);
	i = mlx_get_data_addr(im, &bpp, &size_l, &endian);
	while (data->tab[img->p.y])
	{
		while (img->p.x < data->tab_width)
		{
			nx = (img->p.x * img->spw_btw_pts) - (img->p.y * img->spw_btw_pts);
			ny = ((img->p.y * img->sph_btw_pts) + (img->p.y * img->sph_btw_pts)) / 2;
			set_pixel(nx, ny, img);
			img->p.x++;
		}
		img->p.y++;
	}
	win = mlx_new_window(mlx, data->win_width, data->win_height, "4");
	mlx_put_image_to_window(mlx, win, im, 0, 0);
	sleep(5);
	//mlx_loop(mlx);

	/*while (data->tab[img->p.y])
	{
		while (img->p.x < data->tab_width)
		{
			set_pixel((img->p.x * img->spw_btw_pts), img->p.y * img->sph_btw_pts, img);
		}
	}*/
	return (0);
}
