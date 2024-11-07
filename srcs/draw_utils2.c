/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:58:47 by amsaleh           #+#    #+#             */
/*   Updated: 2024/10/30 12:38:36 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	mlx_img_pixel_put(t_img *img, int x, int y, u_int32_t color)
{
	u_int32_t	*dst;

	if (x < img->width && y < img->height && x >= 0 && y >= 0)
	{
		dst = img->addr + (y * img->line_length + x
				* (img->bits_per_pixel / 8));
		*dst = color;
	}
}

void	fill_image(t_img *img, u_int32_t color)
{
	int			x;
	int			y;
	u_int32_t	*dst;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			dst = img->addr + (y * img->line_length + x
					* (img->bits_per_pixel / 8));
			*dst = color;
			x++;
		}
		y++;
	}
}

void	redraw_scene(t_fdf *fdf)
{
	update_center_point(fdf);
	setup_points(fdf);
	fill_image(fdf->img, BACKGROUND);
	draw_connections(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
	if (fdf->show_menu)
	{
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->logo_img->img, 0, 0);
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->back_img->img, 0, 100);
		print_details(fdf);
	}
}
