/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 00:24:40 by amsaleh           #+#    #+#             */
/*   Updated: 2024/10/28 15:52:00 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	get_arr_size(void **arr)
{
	int				i;
	unsigned char	**arr_ref;

	i = 0;
	arr_ref = (unsigned char **)arr;
	while (arr_ref[i])
		i++;
	return (i);
}

char	*ft_safe_strjoin(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (!res)
		return (0);
	free(s1);
	free(s2);
	return (res);
}

static void	destroy_images(t_fdf *fdf)
{
	if (fdf->img)
		if (fdf->img->img)
			mlx_destroy_image(fdf->mlx, fdf->img->img);
	if (fdf->logo_img)
		if (fdf->logo_img->img)
			mlx_destroy_image(fdf->mlx, fdf->logo_img->img);
	if (fdf->back_img)
		if (fdf->back_img->img)
			mlx_destroy_image(fdf->mlx, fdf->back_img->img);
	free(fdf->img);
	free(fdf->logo_img);
	free(fdf->back_img);
}

static void	exit_handler_helper(t_fdf *fdf)
{
	mlx_loop_end(fdf->mlx);
	destroy_images(fdf);
	if (fdf->height_data)
		free_array((void **)fdf->height_data);
	if (fdf->points_data)
		free_array((void **)fdf->points_data);
	if (fdf->points_color)
		free_array((void **)fdf->points_color);
	free(fdf->camera);
	free(fdf->plot_origin);
	free(fdf->center_point);
	free(fdf->mouse_pos);
	if (fdf->mlx)
	{
		if (fdf->win)
			mlx_destroy_window(fdf->mlx, fdf->win);
		mlx_destroy_display(fdf->mlx);
	}
	free(fdf->mlx);
	free(fdf);
}

void	exit_handler(t_fdf *fdf, int error)
{
	if (error)
	{
		ft_printf("Exiting due to an error!\n");
		ft_printf("Error: %s\n", strerror(errno));
	}
	if (fdf)
		exit_handler_helper(fdf);
	if (error)
		exit(errno);
	exit(0);
}
