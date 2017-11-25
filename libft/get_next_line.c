/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <sdjeghba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:58:40 by sdjeghba          #+#    #+#             */
/*   Updated: 2017/09/13 19:12:15 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/get_next_line.h"
#include "./includes/libft.h"

int					ft_processing_data(char **file, char **line)
{
	char			*tmp;

	tmp = ft_strchr(*file, '\n');
	if (tmp)
	{
		*line = ft_strsub(*file, 0, tmp - *file);
		ft_strncpy(*file, tmp + 1, ft_strlen(tmp));
		tmp = NULL;
		return (1);
	}
	return (0);
}

int					ft_read_file(int fd, char **file, char **line)
{
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	int				ret;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		tmp = NULL;
		if (*file)
		{
			tmp = ft_strdup(*file);
			ft_memdel((void**)file);
			*file = ft_strjoin(tmp, buf);
			ft_memdel((void**)&tmp);
		}
		else
			*file = ft_strdup(buf);
		if (ft_processing_data(file, line))
			return (1);
	}
	return (0);
}

int					get_next_line(int fd, char **line)
{
	static char		*file[256];
	int				ret_value;

	if (!line || fd < 0 || fd > 256)
		return (-1);
	if (file[fd] != NULL && ft_processing_data(&file[fd], line) == 1)
		return (1);
	ret_value = ft_read_file(fd, &file[fd], line);
	if (ret_value != 0)
		return (ret_value);
	if (file[fd] == NULL || file[fd][0] == '\0')
		return (0);
	*line = file[fd];
	file[fd] = NULL;
	return (1);
}
