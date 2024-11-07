/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 00:24:50 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/04 22:21:55 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	free_mapdata(t_mapdata *mapdata)
{
	if (mapdata->line)
		free(mapdata->line);
	if (mapdata->line_split)
		free_array((void **)mapdata->line_split);
	if (mapdata->res)
		free(mapdata->res);
	free(mapdata);
	return (0);
}

int	get_map_data_helper2(t_mapdata *mapdata, int fd)
{
	char		*line_str;
	u_int32_t	len;

	line_str = ft_strjoin(mapdata->line, "\n");
	free(mapdata->line);
	mapdata->line = 0;
	mapdata->res = ft_safe_strjoin(mapdata->res, line_str);
	if (!mapdata->res)
		return (0);
	free_array((void **)mapdata->line_split);
	mapdata->line_split = 0;
	mapdata->line = get_next_line(fd);
	if (mapdata->line)
	{
		len = ft_strlen(mapdata->line);
		if (mapdata->line[len - 1] == '\n')
			mapdata->line[len - 1] = 0;
	}
	return (1);
}

static int	get_map_data_helper(t_fdf *fdf, t_mapdata *mapdata, int fd)
{
	int	i;

	i = 0;
	while (mapdata->line)
	{
		mapdata->line_split = ft_split(mapdata->line, ' ');
		if (!fdf->rows)
			fdf->rows = get_arr_size((void **)mapdata->line_split);
		if (fdf->rows != get_arr_size((void **)mapdata->line_split))
			return (free_mapdata(mapdata));
		if (!get_map_data_helper2(mapdata, fd))
			return (free_mapdata(mapdata));
		i++;
	}
	return (i);
}

static t_mapdata	*get_map_data(t_fdf *fdf, int fd)
{
	t_mapdata	*mapdata;
	u_int32_t	len;

	mapdata = ft_calloc(1, sizeof(t_mapdata));
	if (!mapdata)
		return (0);
	mapdata->res = ft_strdup("");
	mapdata->line = get_next_line(fd);
	if (!mapdata->line)
	{
		free_mapdata(mapdata);
		return (0);
	}
	len = ft_strlen(mapdata->line);
	if (mapdata->line[len - 1] == '\n')
		mapdata->line[len - 1] = 0;
	fdf->cols = get_map_data_helper(fdf, mapdata, fd);
	if (!fdf->cols)
		return (0);
	return (mapdata);
}

int	read_map(char **argv, t_fdf *fdf)
{
	int			fd;
	t_mapdata	*map_data;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (0);
	map_data = get_map_data(fdf, fd);
	if (!map_data)
	{
		ft_printf("Reading map data failed!\n");
		return (0);
	}
	fdf->height_data = (int **)alloc_arr_2d(fdf->cols, fdf->rows, sizeof(int));
	if (!fdf->height)
		return (free_mapdata(map_data));
	fdf->points_color = (u_int32_t **)alloc_arr_2d(fdf->cols,
			fdf->rows, sizeof(u_int32_t));
	if (!fdf->points_color)
		return (free_mapdata(map_data));
	parse_height_map(fdf, map_data);
	free_mapdata(map_data);
	return (1);
}
