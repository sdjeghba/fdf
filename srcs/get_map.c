/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 08:17:09 by sdjeghba          #+#    #+#             */
/*   Updated: 2017/12/02 19:01:57 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int			check_map(char *str)
{
	while (*str)
	{
		if (*str != ' ' || !(ft_isalnum(*str)))
			return (-1);
		str++;
	}
	return (0);
}

int			fill_intab(char **tab, t_data *data, int y)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (tab[i])
	{
		data->tab[y][x] = ft_atoi(tab[i]);
		x++;
		i++;
	}
	return (0);
}

int			loop_tabatoi(t_list *tmp, t_data *data, int y)
{
	char	**array;
	int		count;

	count = 0;
	array = NULL;
	if (!(check_map(tmp->content)))
		return (display_error("map error, allowed only alphanum chars"));
	array = ft_strsplit(tmp->content, ' ');
	count = ft_count_word(tmp->content, ' ');
	if (data->tab_w == 0)
		data->tab_w = count;
	if (data->tab_w != count)
		display_error("map error: check the map format");
	if (!(data->tab[y] = malloc(sizeof(int) * data->tab_w)))
		return (-1);
	fill_intab(array, data, y);
	ft_free_tab(array);
	free(array);
	return (0);
}

int			fill_coor(t_list *map, t_data *data)
{
	t_list	*tmp;
	int		y;
	int		cnt;

	y = 0;
	cnt = 0;
	tmp = map;
	data->tab_w = 0;
	if (!(data->tab = malloc(sizeof(int *) * ft_lstlen(&tmp) + 1)))
		return (-1);
	while (tmp)
	{
		loop_tabatoi(tmp, data, y);
		y++;
		tmp = tmp->next;
	}
	data->tab_h = y;
	data->tab[y] = NULL;
	return (0);
}

int			get_map(char **av, t_list **map, t_data *data)
{
	int		fd;
	int		ret;
	char	*tmp;

	tmp = NULL;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		display_error("error: file can't be openned");
	while ((ret = get_next_line(fd, &tmp)))
	{
		if (ret == -1)
			display_error("error: file can't be openned");
		if (ft_strlen(tmp))
		{
			ft_lstpushback(tmp, (ft_strlen(tmp) + 1), map);
			ft_memdel((void**)&tmp);
		}
		else
			display_error("map error");
	}
	fill_coor(*map, data);
	return (0);
}
