/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:41:26 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/01 17:12:39 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	exit_hook(t_fdf *mlx)
{
	exit_handler(mlx, 0);
	return (0);
}

int	mouse_down_hook(int button, int x, int y, t_fdf *fdf)
{
	if (button == 1)
	{
		fdf->mouse_pos->x = x;
		fdf->mouse_pos->y = y;
	}
	if (button == 4)
	{
		fdf->camera->zoom_factor *= 2;
		redraw_scene(fdf);
	}
	if (button == 5)
	{
		fdf->camera->zoom_factor /= 2;
		redraw_scene(fdf);
	}
	return (0);
}

int	mouse_up_hook(int button, int x, int y, t_fdf *fdf)
{
	if (button == 1)
	{
		fdf->plot_origin->x += (float)(x - fdf->mouse_pos->x);
		fdf->plot_origin->y += (float)(y - fdf->mouse_pos->y);
		redraw_scene(fdf);
	}
	return (0);
}

int	key_down_hook(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
		exit_handler(fdf, 0);
	if (fdf->projection == isometric)
		isometric_controls(keycode, fdf);
	if (fdf->projection == orthographic)
		orthographic_controls(keycode, fdf);
	if (keycode == XK_p)
		switch_projection(fdf);
	if (keycode == XK_s)
		fdf->show_menu = !fdf->show_menu;
	if (keycode == XK_z)
		reset_scene(fdf);
	if (keycode == XK_c)
		fdf->height_factor -= 0.25;
	if (keycode == XK_v)
		fdf->height_factor += 0.25;
	if (keycode == XK_s || keycode == XK_p || keycode == XK_z
		|| keycode == XK_c || keycode == XK_v)
		redraw_scene(fdf);
	return (0);
}
