/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 23:58:04 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/04 22:24:19 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	ft_ishex(char c)
{
	if ((c > 0x2F && c < 0x3A) || (c > 0x40 && c < 0x47)
		|| (c > 0x60 && c < 0x67))
		return (1);
	return (0);
}

static int	hex_char_to_decimal(char c)
{
	if (c > 0x2F && c < 0x3A)
		return (c - 0x30);
	if (c > 0x40 && c < 0x47)
		return (c - 0x37);
	if (c > 0x60 && c < 0x67)
		return (c - 0x57);
	return (0);
}

static u_int32_t	hex_to_int(char *str)
{
	int			i;
	int			j;
	int			arr[8];
	u_int32_t	res;

	i = 0;
	j = -1;
	res = 0;
	if (str[0] == '0' && str[1] == 'x')
		str += 2;
	while (ft_ishex(str[i]))
	{
		arr[i] = hex_char_to_decimal(str[i]);
		i++;
	}
	while (++j < i)
		res = res * 16 + arr[j];
	return (res);
}

int	parse_height_map_helper(t_mapdata *map_data, int k, u_int32_t *data)
{
	if (map_data->res[k] == '-')
		k++;
	while (ft_isdigit(map_data->res[k]))
		k++;
	if (map_data->res[k] == ',')
	{
		k++;
		*data = hex_to_int(map_data->res + k);
		if (map_data->res[k] == '0' && map_data->res[k + 1] == 'x')
			k += 2;
		while (ft_ishex(map_data->res[k]))
			k++;
	}
	return (k);
}

void	parse_height_map(t_fdf *fdf, t_mapdata *map_data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (map_data->res[k])
	{
		if (ft_isdigit(map_data->res[k]) || map_data->res[k] == '-')
		{
			fdf->height_data[i][j] = ft_atoi(map_data->res + k);
			k = parse_height_map_helper(map_data, k, &fdf->points_color[i][j]);
			j++;
		}
		if (map_data->res[k] == '\n')
		{
			parse_handle_edge_case(j, fdf, map_data);
			i++;
			j = 0;
		}
		if (map_data->res[k])
			k++;
	}
}
