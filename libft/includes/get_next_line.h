/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeghba <sdjeghba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:59:04 by sdjeghba          #+#    #+#             */
/*   Updated: 2017/09/13 19:11:44 by sdjeghba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 4096

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>

int			get_next_line(int fd, char **line);

#endif
