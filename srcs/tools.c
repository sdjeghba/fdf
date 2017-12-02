/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:44:48 by sdjeghba          #+#    #+#             */
/*   Updated: 2017/12/02 19:03:17 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int			key_hook(int keycode, t_data *e)
{
	(void)e;
	if (keycode == ESC)
		exit(0);
	return (0);
}

void		set_pixel(int x, int y, t_img *img)
{
	int		i;

	i = (x * 4) + (y * img->size_line);
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
