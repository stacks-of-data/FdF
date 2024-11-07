/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:23:22 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/01 17:41:39 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <sys/param.h>

# define PI 3.14159265358979323846
# define BACKGROUND 0x303030

typedef struct s_point2d
{
	float		x;
	float		y;
}				t_point2d;

typedef struct s_point3d
{
	float		x;
	float		y;
	float		z;
}				t_point3d;

typedef struct s_img
{
	void		*img;
	void		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_camera
{
	float		zoom_factor;
	float		alpha;
	float		beta;
	float		gamma;
}				t_camera;

typedef struct s_mouse
{
	int			x;
	int			y;
}				t_mouse;

enum	e_projection
{
	isometric,
	orthographic
};

enum	e_rotation
{
	x_rotation,
	y_rotation,
	z_rotation
};

typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	int			cols;
	int			rows;
	int			width;
	int			height;
	int			grid_size;
	int			show_menu;
	int			projection;
	float		height_factor;
	int			**height_data;
	u_int32_t	**points_color;
	t_camera	*camera;
	t_mouse		*mouse_pos;
	t_point3d	**points_data;
	t_point3d	*plot_origin;
	t_point3d	*center_point;
	t_img		*img;
	t_img		*logo_img;
	t_img		*back_img;
}				t_fdf;

typedef struct s_mapdata
{
	char		*line;
	char		*res;
	char		**line_split;
}				t_mapdata;

typedef struct s_line3d
{
	t_point3d	start;
	t_point3d	end;
}				t_line3d;

typedef struct s_line2d
{
	t_point2d	start;
	t_point2d	end;
}				t_line2d;

void			projection(t_fdf *fdf, t_point3d data_3d,
					t_point2d *data_2d);
void			draw_connections(t_fdf *fdf);
void			mlx_img_pixel_put(t_img *img, int x, int y, unsigned int color);
int				get_arr_size(void **arr);
void			**alloc_arr_2d(ssize_t len, size_t n_elems, size_t elem_size);
char			*ft_safe_strjoin(char *s1, char *s2);
int				read_map(char **argv, t_fdf *fdf);
void			exit_handler(t_fdf *fdf, int error);
void			parse_height_map(t_fdf *fdf, t_mapdata *map_data);
int				exit_hook(t_fdf *mlx);
int				mouse_down_hook(int button, int x, int y, t_fdf *fdf);
int				mouse_up_hook(int button, int x, int y, t_fdf *fdf);
int				key_down_hook(int keycode, t_fdf *fdf);
void			redraw_scene(t_fdf *fdf);
t_img			*create_image(t_fdf *fdf, int width, int height,
					unsigned int color);
t_img			*open_image(t_fdf *fdf, char *path);
void			fill_image(t_img *img, unsigned int color);
void			update_center_point(t_fdf *fdf);
void			print_details(t_fdf *fdf);
void			isometric_controls(int keycode, t_fdf *fdf);
void			orthographic_controls(int keycode, t_fdf *fdf);
void			switch_projection(t_fdf *fdf);
void			reset_scene(t_fdf *fdf);
void			redraw_scene(t_fdf *fdf);
void			setup_points(t_fdf *fdf);
int				free_mapdata(t_mapdata *mapdata);
void			parse_handle_edge_case(int rows_count, t_fdf *fdf,
					t_mapdata *mapdata);

#endif