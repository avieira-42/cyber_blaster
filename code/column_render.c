/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 04:49:04 by avieira-          #+#    #+#             */
/*   Updated: 2026/03/17 04:54:02 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "render.h"
#include "types.h"
#include "libft_math.h"

t_column	column_init(t_ray ray, t_player player, int32_t x)
{
	t_column	column;

	// calculate perp_wall_dist
	/*if (ray.side == 0)
		ray.perp_wall_dist = (ray.p_map_pos.x - ray.p_pos.x
				+ (1 - ray.step_ori.x) / 2.0f) / ray.dir.x;
	else
		ray.perp_wall_dist = (ray.p_map_pos.y - ray.p_pos.y
				+ (1 - ray.step_ori.y) / 2.0f) / ray.dir.y;*/

	ray.perp_wall_dist = ray.final_len;

	//	calculate height of line to be drawn
	column.height = SCREEN_Y / ray.perp_wall_dist;

	// calculate lowest and highest pixel to fill in current stripe
	column.end.x = x;
	column.start.x = x;
	//column.start.y = -column.height / 2 + player.mouse_mov.y / 2;
	//column.end.y = column.height / 2 + player.mouse_mov.y / 2;
	column.start.y = SCREEN_Y / 2 - column.height / 2 + player.mouse_mov.y / 2;
	column.end.y   = SCREEN_Y / 2 + column.height / 2 + player.mouse_mov.y / 2;
	if (column.start.y < 0)
		column.start.y = 0;
	if (column.end.y >= SCREEN_Y)
		column.end.y = SCREEN_Y - 1;
	column.height = ft_abs(column.end.y - column.start.y);
	return (column);
}

void	column_pixel_put(t_img *frame, t_ray ray, t_column column, const t_img *img)
{
	int32_t		i;
	float		y;
	float		x;
	float		text_pos;
	const float	step = (float)img->height / (float)column.height;

	x = ray.wall_x * (float)img->width;
	printf("first_x: %f\n", x);
	if (ray.side == 0 && ray.dir.x > 0)
		x = img->width - x - 1;
	if (ray.side == 1 && ray.dir.y < 0)
		x = img->width - x -1;
	printf("x: %f\n", x);
	i = 0;
	y = 0;
	text_pos = 0;
	while(i < column.height)
	{
		y = (int32_t)text_pos;
		if (y < 0)
			y = 0;
		if (y >= img->height)
			y = img->height - 1;
		frame_pixel_put(frame, column.start.x, column.start.y + i, get_color(img, x, y));
		text_pos += step;
		i++;
	}
}

void	column_render(t_img *frame, t_ray ray, t_player player, int32_t x, t_img *img)
{
	t_column const	column = column_init(ray, player, x);

	// Draw Column
	/*if (ray.color != 0x777777 && ray.color != 0xFF00FF)
	{
		if (ray.dir.x > 0)
		{
			if (ray.dir.y > 0)
				ray.color = RED;
			else
				ray.color = BLUE;
		}
		else
		{
			if (ray.dir.y > 0)
				ray.color = WHITE;
			else
				ray.color = GREEN;
		}
	}
	line_draw_bresenham(column.start, column.end, frame, ray.color);*/

	column_pixel_put(frame, ray, column, img);
	line_draw_bresenham((t_vecf32){column.end.x, SCREEN_Y}, column.end, frame, 0x444444);
}
