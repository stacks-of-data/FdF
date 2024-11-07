/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 23:51:27 by amsaleh           #+#    #+#             */
/*   Updated: 2024/10/30 12:31:34 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	update_center_point(t_fdf *fdf)
{
	fdf->center_point->x = fdf->plot_origin->x
		+ ((fdf->width / (float)fdf->grid_size)
			* fdf->camera->zoom_factor * (fdf->rows / 2));
	fdf->center_point->y = fdf->plot_origin->y
		+ ((fdf->height / (float)fdf->grid_size)
			* fdf->camera->zoom_factor * (fdf->cols / 2));
	fdf->center_point->z = fdf->plot_origin->z;
}

static float	degree_to_rad(float angle)
{
	return (angle * PI / 180);
}

static void	rotate_point(t_point3d *point3d, int angle, int axis)
{
	float		rad;
	t_point3d	oldpoint;

	rad = degree_to_rad(angle);
	oldpoint = *point3d;
	if (axis == x_rotation)
	{
		point3d->y = cos(rad) * oldpoint.y - sin(rad) * oldpoint.z;
		point3d->z = sin(rad) * oldpoint.y + cos(rad) * oldpoint.z;
	}
	if (axis == y_rotation)
	{
		point3d->x = cos(rad) * oldpoint.x + sin(rad) * oldpoint.z;
		point3d->z = -sin(rad) * oldpoint.x + cos(rad) * oldpoint.z;
	}
	if (axis == z_rotation)
	{
		point3d->x = cos(rad) * oldpoint.x - sin(rad) * oldpoint.y;
		point3d->y = sin(rad) * oldpoint.x + cos(rad) * oldpoint.y;
	}
}

void	projection(t_fdf *fdf, t_point3d data_3d, t_point2d *data_2d)
{
	data_3d.x -= fdf->center_point->x;
	data_3d.y -= fdf->center_point->y;
	data_3d.z -= fdf->center_point->z;
	rotate_point(&data_3d, fdf->camera->alpha, z_rotation);
	rotate_point(&data_3d, fdf->camera->beta, y_rotation);
	rotate_point(&data_3d, fdf->camera->gamma, x_rotation);
	data_3d.x += fdf->center_point->x;
	data_3d.y += fdf->center_point->y;
	data_3d.z += fdf->center_point->z;
	data_2d->x = data_3d.x;
	data_2d->y = data_3d.y;
}
