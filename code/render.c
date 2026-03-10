#include "types.h"
#include "render.h"

void	space_render(t_game *game)
{
	t_vecf32 const	map_max = (t_vecf32){game->map.max_x, game->map.max_y};
	t_vecf32 const	map_tile = (t_vecf32){game->map.tile_x, game->map.tile_y};
	t_veci32 const	map_size = (t_veci32){game->map.width, game->map.height};

	fov_draw(game);
	objects_draw(game, map_size, map_tile);
	grid_draw(&game->frame, map_max, map_tile, map_size);

	// to remove after collisions
	if (game->player.pos.x <= game->map.max_x
			&& game->player.pos.y <= game->map.max_y)
		player_draw(game, map_tile);
	// to remove after collisions
}

void	sprites_render(t_game *game)
{
	if (game->player.shoot == true)
	{
		if (game->shoot->i == game->shoot->count - 1)
			game->player.shoot = false;
		sprite_sheet_animate(&game->frame, game->shoot,
				(t_vecf32){SCREEN_X / 3.7, SCREEN_Y / 2}, 1.2);
		if (game->player.shoot == false)
			game->shoot->i = 0;
	}
	if (game->player.shoot == false)
	{
		if (game->player.ori.x != 0 || game->player.ori.y != 0)
			sprite_sheet_animate(&game->frame, game->walk,
					(t_vecf32){SCREEN_X / 3.7, SCREEN_Y / 2}, 1.2);
		else
			draw_texture(&game->frame, &game->walk->sheet[0],
					(t_vecf32){SCREEN_X / 3.7, SCREEN_Y / 2}, 1.2);
	}
}
