/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:22:21 by amsaleh           #+#    #+#             */
/*   Updated: 2024/10/30 12:41:08 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	isometric_controls(int keycode, t_fdf *fdf)
{
	if (keycode == XK_1)
		fdf->camera->gamma += 10;
	if (keycode == XK_2)
		fdf->camera->beta += 10;
	if (keycode == XK_3)
		fdf->camera->alpha += 10;
	if (keycode == XK_4)
		fdf->camera->gamma -= 10;
	if (keycode == XK_5)
		fdf->camera->beta -= 10;
	if (keycode == XK_6)
		fdf->camera->alpha -= 10;
	if (keycode == XK_1 || keycode == XK_2 || keycode == XK_3 || keycode == XK_4
		|| keycode == XK_5 || keycode == XK_6)
		redraw_scene(fdf);
}

void	orthographic_controls(int keycode, t_fdf *fdf)
{
	if (keycode == XK_t)
	{
		fdf->camera->alpha = 0;
		fdf->camera->gamma = 0;
	}
	if (keycode == XK_f)
	{
		fdf->camera->alpha = 0;
		fdf->camera->gamma = 90;
	}
	if (keycode == XK_r)
	{
		fdf->camera->alpha = -90;
		fdf->camera->gamma = 90;
	}
	if (keycode == XK_l)
	{
		fdf->camera->alpha = 90;
		fdf->camera->gamma = 90;
	}
	if (keycode == XK_t || keycode == XK_f || keycode == XK_r
		|| keycode == XK_l)
		redraw_scene(fdf);
}

void	switch_projection(t_fdf *fdf)
{
	if (fdf->projection == isometric)
	{
		fdf->camera->alpha = 0;
		fdf->camera->beta = 0;
		fdf->camera->gamma = 0;
		fdf->projection = orthographic;
	}
	else
	{
		fdf->camera->alpha = 45;
		fdf->camera->gamma = 35;
		fdf->projection = isometric;
	}
}

void	reset_scene(t_fdf *fdf)
{
	fdf->plot_origin->x = fdf->width / 4;
	fdf->plot_origin->y = fdf->width / 4;
	if (fdf->projection == isometric)
	{
		fdf->camera->alpha = 45;
		fdf->camera->beta = 0;
		fdf->camera->gamma = 35;
	}
	else
	{
		fdf->camera->alpha = 0;
		fdf->camera->beta = 0;
		fdf->camera->gamma = 0;
	}
	fdf->camera->zoom_factor = 1;
	fdf->height_factor = 3;
}
