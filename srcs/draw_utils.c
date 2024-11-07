/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 23:53:57 by amsaleh           #+#    #+#             */
/*   Updated: 2024/10/29 20:20:56 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	draw_line_helper(t_fdf *fdf, t_line3d line_3d,
	t_line2d line_2d, u_int32_t color)
{
	if (color)
		mlx_img_pixel_put(fdf->img, line_2d.start.x, line_2d.start.y, color);
	else if ((line_3d.start.z > fdf->plot_origin->z && line_3d.start.z <= 100)
		|| (line_3d.end.z > fdf->plot_origin->z && line_3d.end.z <= 100))
		mlx_img_pixel_put(fdf->img, line_2d.start.x, line_2d.start.y, 0xFFFF00);
	else if (line_3d.start.z > 100 || line_3d.end.z > 100)
		mlx_img_pixel_put(fdf->img, line_2d.start.x, line_2d.start.y, 0xFF0000);
	else if (!line_3d.start.z && !line_3d.end.z)
		mlx_img_pixel_put(fdf->img, line_2d.start.x, line_2d.start.y, 0xFFA500);
	else if (line_3d.start.z > -100 || line_3d.end.z > -100)
		mlx_img_pixel_put(fdf->img, line_2d.start.x, line_2d.start.y, 0x702963);
	else
		mlx_img_pixel_put(fdf->img, line_2d.start.x, line_2d.start.y, 0x301934);
}

static void	draw_line(t_fdf *fdf, t_line3d line_3d, u_int32_t color)
{
	t_point2d	diff;
	t_point2d	inc;
	t_line2d	line_2d;
	int			steps;
	int			i;

	projection(fdf, line_3d.start, &line_2d.start);
	projection(fdf, line_3d.end, &line_2d.end);
	diff.x = line_2d.end.x - line_2d.start.x;
	diff.y = line_2d.end.y - line_2d.start.y;
	if (ft_abs(diff.x) > ft_abs(diff.y))
		steps = ft_abs(diff.x);
	else
		steps = ft_abs(diff.y);
	inc.x = diff.x / (float)steps;
	inc.y = diff.y / (float)steps;
	i = -1;
	while (++i <= steps)
	{
		draw_line_helper(fdf, line_3d, line_2d, color);
		line_2d.start.x += inc.x;
		line_2d.start.y += inc.y;
	}
}

static void	draw_connections_rows(t_fdf *fdf)
{
	int			i;
	int			j;
	t_line3d	line_3d;

	i = 0;
	while (i < fdf->cols)
	{
		j = 0;
		while (j < fdf->rows - 1)
		{
			line_3d.start = fdf->points_data[i][j];
			line_3d.end = fdf->points_data[i][j + 1];
			draw_line(fdf, line_3d, fdf->points_color[i][j]);
			j++;
		}
		i++;
	}
}

static void	draw_connections_cols(t_fdf *fdf)
{
	int			i;
	int			j;
	t_line3d	line_3d;

	i = 0;
	while (i < fdf->rows)
	{
		j = 0;
		while (j < fdf->cols - 1)
		{
			line_3d.start = fdf->points_data[j][i];
			line_3d.end = fdf->points_data[j + 1][i];
			draw_line(fdf, line_3d, fdf->points_color[j][i]);
			j++;
		}
		i++;
	}
}

void	draw_connections(t_fdf *fdf)
{
	draw_connections_rows(fdf);
	draw_connections_cols(fdf);
}
