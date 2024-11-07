/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:23:54 by amsaleh           #+#    #+#             */
/*   Updated: 2024/10/30 12:40:51 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	setup_points(t_fdf *fdf)
{
	t_point3d	point_3d;
	t_point3d	start_point_3d;
	int			i;
	int			j;

	i = 0;
	start_point_3d = *fdf->plot_origin;
	while (i < fdf->cols)
	{
		j = 0;
		start_point_3d.y += (fdf->height / (float)fdf->grid_size)
			* fdf->camera->zoom_factor;
		point_3d = start_point_3d;
		while (j < fdf->rows)
		{
			point_3d.x += (fdf->width / (float)fdf->grid_size)
				* fdf->camera->zoom_factor;
			point_3d.z = (float)fdf->height_data[i][j] * fdf->height_factor
				* fdf->camera->zoom_factor;
			fdf->points_data[i][j] = point_3d;
			j++;
		}
		i++;
	}
}

static void	init_fdf_helper(t_fdf *fdf)
{
	fdf->plot_origin = ft_calloc(1, sizeof(t_point3d));
	if (!fdf->plot_origin)
		exit_handler(fdf, 1);
	fdf->points_data = (t_point3d **)alloc_arr_2d(fdf->cols,
			fdf->rows, sizeof(t_point3d));
	if (!fdf->points_data)
		exit_handler(fdf, 1);
	fdf->img = create_image(fdf, fdf->width, fdf->height, 0x7B0000);
	if (!fdf->img)
		exit_handler(fdf, 1);
	fdf->camera = ft_calloc(1, sizeof(t_camera));
	if (!fdf->camera)
		exit_handler(fdf, 1);
	fdf->center_point = ft_calloc(1, sizeof(t_point3d));
	if (!fdf->center_point)
		exit_handler(fdf, 1);
	fdf->mouse_pos = ft_calloc(1, sizeof(t_mouse));
	if (!fdf->mouse_pos)
		exit_handler(fdf, 1);
}

static t_fdf	*init_fdf(char **argv)
{
	t_fdf	*fdf;

	fdf = ft_calloc(1, sizeof(t_fdf));
	if (!fdf)
		exit_handler(fdf, 1);
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		exit_handler(fdf, 1);
	fdf->width = 800;
	fdf->height = 600;
	fdf->win = mlx_new_window(fdf->mlx, fdf->width, fdf->height, "FDF");
	if (!fdf->win)
		exit_handler(fdf, 1);
	if (!read_map(argv, fdf))
		exit_handler(fdf, 1);
	init_fdf_helper(fdf);
	fill_image(fdf->img, BACKGROUND);
	return (fdf);
}

static void	init_fdf_props(t_fdf *fdf)
{
	fdf->grid_size = fdf->cols + fdf->rows;
	fdf->plot_origin->x = fdf->width / 4;
	fdf->plot_origin->y = fdf->width / 4;
	fdf->camera->zoom_factor = 1;
	fdf->camera->alpha = 45;
	fdf->camera->gamma = 35;
	fdf->show_menu = 1;
	fdf->height_factor = 3;
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2)
		return (0);
	fdf = init_fdf(argv);
	init_fdf_props(fdf);
	update_center_point(fdf);
	setup_points(fdf);
	draw_connections(fdf);
	fdf->logo_img = open_image(fdf, "logo.xpm");
	if (!fdf->logo_img)
		exit_handler(fdf, 1);
	fdf->back_img = create_image(fdf, 200, fdf->height - 100, 0x7B0000);
	if (!fdf->back_img)
		exit_handler(fdf, 1);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->logo_img->img, 0, 0);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->back_img->img, 0, 100);
	print_details(fdf);
	mlx_hook(fdf->win, 17, 0, exit_hook, fdf);
	mlx_hook(fdf->win, 2, 1L << 0, key_down_hook, fdf);
	mlx_hook(fdf->win, 4, 1L << 2, mouse_down_hook, fdf);
	mlx_hook(fdf->win, 5, 1L << 3, mouse_up_hook, fdf);
	mlx_loop(fdf->mlx);
}
