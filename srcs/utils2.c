/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:22:52 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/04 22:23:09 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	**alloc_arr_2d(ssize_t len, size_t n_elems, size_t elem_size)
{
	void	**res;
	ssize_t	i;

	i = -1;
	res = ft_calloc(len + 1, sizeof(void *));
	if (!res)
		return (0);
	while (++i < len)
	{
		res[i] = ft_calloc(n_elems, elem_size);
		if (!res[i])
		{
			while (--i > -1)
				free(res[i]);
			free(res);
			return (0);
		}
	}
	return (res);
}

t_img	*create_image(t_fdf *fdf, int width, int height, unsigned int color)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		return (0);
	img->img = mlx_new_image(fdf->mlx, width, height);
	if (!img->img)
		return (0);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
		return (0);
	img->width = width;
	img->height = height;
	fill_image(img, color);
	return (img);
}

t_img	*open_image(t_fdf *fdf, char *path)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		return (0);
	img->img = mlx_xpm_file_to_image(fdf->mlx, path, &img->width, &img->height);
	if (!img->img)
		return (0);
	return (img);
}

void	parse_handle_edge_case(int rows_count, t_fdf *fdf, t_mapdata *mapdata)
{
	if (rows_count != fdf->rows)
	{
		ft_printf("Reading map data failed!\n");
		free_mapdata(mapdata);
		exit_handler(fdf, 1);
	}
}

void	print_details(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx, fdf->win, 10, 120, 0xFFFFFF,
		"Left mouse button to move");
	mlx_string_put(fdf->mlx, fdf->win, 10, 140, 0xFFFFFF,
		"Scroll to zoom in/out");
	mlx_string_put(fdf->mlx, fdf->win, 10, 160, 0xFFFFFF,
		"S to hide/show this menu");
	mlx_string_put(fdf->mlx, fdf->win, 10, 180, 0xFFFFFF,
		"P to switch projection mode");
	mlx_string_put(fdf->mlx, fdf->win, 10, 200, 0xFFFFFF,
		"In Isometric Projection:");
	mlx_string_put(fdf->mlx, fdf->win, 10, 220, 0xFFFFFF,
		"1,2,3 rotate clockwise");
	mlx_string_put(fdf->mlx, fdf->win, 10, 240, 0xFFFFFF,
		"4,5,6 rotate counter-clockwise");
	mlx_string_put(fdf->mlx, fdf->win, 10, 260, 0xFFFFFF,
		"In Orthographic Projection:");
	mlx_string_put(fdf->mlx, fdf->win, 10, 280, 0xFFFFFF,
		"T,F,R,L to change view side");
	mlx_string_put(fdf->mlx, fdf->win, 10, 300, 0xFFFFFF,
		"Z to reset view");
	mlx_string_put(fdf->mlx, fdf->win, 10, 320, 0xFFFFFF,
		"C,V to change height factor");
}
