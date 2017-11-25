/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 08:17:09 by sdjeghba          #+#    #+#             */
/*   Updated: 2017/11/21 19:09:43 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int			ck_format(t_data *data)
{
	int		line_sz;
	int		y;
	int		x;

	line_sz = 0;
	y = 0;
	x = 0;
	while (data->tab[y] != NULL)
	{
		while (data->tab[y][x] != EOL)
			x++;
		if (line_sz == 0)
			line_sz = x;
		if (line_sz != x)
			display_error("map error: check the map format");
		x = 0;
		y++;
	}
	data->tab_width = line_sz;
	data->tab_height = y;
	return (0);
}

int			fill_intab(char **tab, t_data *data, int y)
{
	int		i;
	int		x;

	x = 0;
	i = 0;
	while (tab[i])
	{
		data->tab[y][x] = ft_atoi(tab[i]);
		x++;
		i++;
	}
	data->tab[y][x] = EOL;
	return (0);
}

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

int			fill_coor(t_list *map, t_data *data)
{
	t_list	*tmp;
	int		y;
	char	**array;

	y = 0;
	tmp = map;
	array = NULL;
	if (!(data->tab = malloc(sizeof(int *) * ft_lstlen(&tmp) + 1)))
		return (-1);
	while (tmp)
	{
		if (!(check_map(tmp->content)))
			return (display_error("map error, allowed only alphanum chars"));
		array = ft_strsplit(tmp->content, ' ');
		data->tab[y] = malloc(sizeof(int) * ft_count_word(tmp->content, ' ') + 1);
		fill_intab(array, data, y);
		ft_free_tab(array);
		y++;
		tmp = tmp->next;
	}
	data->tab[y] = NULL;
	ck_format(data);
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
		ft_putendl("error");
	while ((ret = get_next_line(fd, &tmp)))
	{
		if (ft_strlen(tmp))
		{
			ft_lstpushback(tmp, (ft_strlen(tmp) + 1), map);
			ft_strdel(&tmp);
		}
		else
			display_error("map error!");
	}
	fill_coor(*map, data);
	return (0);
}
