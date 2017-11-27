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

	i = (img->iwidth * img->iheight * 4) / 4 + (img->iwidth * 4) / 2;
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
