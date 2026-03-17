#include <unistd.h>
#include "render.h"
#include "ray_cast.h"

void    grid_draw(t_img *frame, t_vecf32 map_max,
		t_vecf32 map_tile, t_veci32 map_size)
{
	int	i;
	float	pos;

	i = 0;
	pos = 0;
	while (i <= map_size.y)
	{
		line_draw_bresenham((t_vecf32){0, pos},
				(t_vecf32){map_max.x, pos},
				frame, 0x777777);
		pos += map_tile.y;
		i++;
	}
	i = 0;
	pos = 0; while (i <= map_size.x)
	{
		line_draw_bresenham((t_vecf32){pos, 0},
				(t_vecf32){pos, map_max.y},
				frame, 0x777777);
		pos += map_tile.x;
		i++;
	}
}

void	objects_draw(t_game *game, t_veci32 map_size, t_vecf32 map_tile)
{
	int32_t	y;
	int32_t	x;

	y = 0;
	while (y < map_size.y)
	{
		x = 0;
		while(x < map_size.x)
		{
			if (game->map.grid[y][x] == '1')
				quad_draw((t_vecf32){x * map_tile.x,
						y * map_tile.y},
						&game->frame, 0x555555, map_tile);
			x++;
		}
		y++;
	}
}

void	ray_draw(t_game *game, t_player player, t_ray ray, int32_t x)
{
	t_vecf32	p_pos;

	p_pos.x = game->player.pos.x * game->map.tile_x;
	p_pos.y = game->player.pos.y * game->map.tile_y;
	if (ray.hit == true)
	{
		ray.hit_pos.x = (ray.p_pos.x + ray.dir.x * ray.final_len) * game->map.tile_x;
		ray.hit_pos.y = (ray.p_pos.y + ray.dir.y * ray.final_len) * game->map.tile_y;
		ray.color = RED;
	}
	else
	{
		ray.hit_pos.x = (ray.p_pos.x + ray.dir.x * game->cam.dist) * game->map.tile_x;
		ray.hit_pos.y = (ray.p_pos.y + ray.dir.y * game->cam.dist) * game->map.tile_y;
		ray.color = GREEN;
	}
	//line_draw_bresenham(p_pos, ray.hit_pos, &game->frame, ray.color);
	(void)p_pos;
	if (!ray.hit)
		return ;
	if (ray.wall == 1)
		column_render(&game->frame, ray, player, x, &game->ad_1->sheet[game->ad_1->i]);
	else if (ray.wall == 2)
		column_render(&game->frame, ray, player, x, &game->ad_2->sheet[game->ad_2->i]);
	else if (ray.wall == 3)
		column_render(&game->frame, ray, player, x, &game->wall->sheet[0]);
	else if (ray.wall == 4)
		column_render(&game->frame, ray, player, x, &game->wall->sheet[1]);
}

void	fov_draw(t_game *game)
{
	int32_t		x;
	float		camera_x;
	t_ray		ray;
	x = 0;
	while(x < SCREEN_X)
	{
		camera_x = 2 * x / (float)SCREEN_X - 1;
		ray.dir.x = game->player.dir.x + game->cam.dir.x * camera_x;
		ray.dir.y = game->player.dir.y + game->cam.dir.y * camera_x;
		ray_cast(game, &ray);
		ray_draw(game, game->player, ray, x);
		x++;
	}
}

void	player_draw(t_game *game, t_vecf32 map_tile)
{
	t_vecf32	p_pos;

	p_pos.x = (game->player.pos.x - 0.5f) * map_tile.x;
	p_pos.y = (game->player.pos.y - 0.5f) * map_tile.y;
	quad_draw(p_pos, &game->frame, 0xFF00FF, map_tile);
	frame_pixel_put(&game->frame, p_pos.x, p_pos.y, 0xFFFFFF);
}
