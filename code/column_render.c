#include <stdbool.h>
#include "render.h"
#include "types.h"
#include "libft_math.h"

t_column	column_init(t_ray ray, t_player player, int32_t x)
{
	t_column	column;
	float		offset;

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
	column.old_start_y = 0;

	// calculate lowest and highest pixel to fill in current stripe
	column.end.x = x;
	column.start.x = x;
	//column.start.y = -column.height / 2 + player.mouse_mov.y / 2;
	//column.end.y = column.height / 2 + player.mouse_mov.y / 2;
	offset = player.mouse_mov.y / 2;
	column.start.y = SCREEN_Y / 2 - column.height / 2 + offset;
	column.end.y   = SCREEN_Y / 2 + column.height / 2 + offset;

	// WALL LIMIT RENDER FIX >>>>>
	column.old_start_y = column.start.y;
	if (column.start.y < 0)
		column.start.y = 0;
	else if (column.end.y >= SCREEN_Y)
		column.end.y = SCREEN_Y - 1;
	// <<<<< WALL LIMIT RENDER FIX

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
	if (ray.side == 0 && ray.dir.x > 0)
		x = img->width - x - 1;
	if (ray.side == 1 && ray.dir.y < 0)
		x = img->width - x -1;
	i = 0;
	if (column.old_start_y < 0)
		text_pos = -column.old_start_y * step;
	else
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
