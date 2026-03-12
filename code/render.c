#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "types.h"
#include "render.h"

void	space_render(t_game *game)
{
	t_vecf32 const	map_max = (t_vecf32){game->map.max_x, game->map.max_y};
	t_vecf32 const	map_tile = (t_vecf32){game->map.tile_x, game->map.tile_y};
	t_veci32 const	map_size = (t_veci32){game->map.width, game->map.height};

	(void)map_max;
	(void)map_tile;
	(void)map_size;
	fov_draw(game);
	//objects_draw(game, map_size, map_tile);
	//grid_draw(&game->frame, map_max, map_tile, map_size);

	// to remove after collisions
	/*if (game->player.pos.x <= game->map.max_x
			&& game->player.pos.y <= game->map.max_y)
		player_draw(game, map_tile);*/
	// to remove after collisions
}

static
void	stt_hands_render(t_game *game)
{
	// reload
	if (game->player.reload == true && game->player.shoot == false)
	{
		if (game->gun.first_i == -1)
		{
			game->reload->i = game->gun.ammo * 4;
			game->gun.first_i = game->reload->i;
		}
		sprite_sheet_animate(&game->frame, game->reload,
				(t_vecf32){SCREEN_X / 5.3, SCREEN_Y / 3}, 1.6);
		if (game->reload->i - game->gun.first_i == 4
				|| game->reload->i >= game->reload->count - 1)
		{
			Mix_PlayChannel(2, game->gun_reload, 0);
			game->gun.ammo++;
			game->gun.first_i = -1;
		}
		if (game->gun.ammo == game->gun.max_ammo)
		{
			game->player.reload = false;
			game->gun.first_i = -1;
			game->reload->i = 0;
		}
	}
	else
	{
		// shoot
		game->player.reload = false;
		game->gun.first_i = -1;
		if (game->player.shoot == true)
		{
			game->walk->i = 0;
			if (game->player.shoot_sound == true)
			{
				Mix_PlayChannel(1, game->gun_shot, 0);
				game->player.shoot_sound = false;
			}
			sprite_sheet_animate(&game->frame, game->shoot,
					(t_vecf32){SCREEN_X / 5.3, SCREEN_Y / 3}, 1.6);
			if (game->shoot->end == true)
			{
				game->player.shoot = false;
				game->shoot->end = false;
				game->shoot->i = 0;
			}
		}
		// walk
		if (game->player.shoot == false)
		{
			if (game->player.ori.x != 0 || game->player.ori.y != 0)
				sprite_sheet_animate(&game->frame, game->walk,
						(t_vecf32){SCREEN_X / 5.3, SCREEN_Y / 3}, 1.6);
			else
			{
				game->walk->i = 0;
				draw_texture(&game->frame, &game->walk->sheet[0],
						(t_vecf32){SCREEN_X / 5.3, SCREEN_Y / 3}, 1.6);
			}
		}
	}
}

void	stt_cards_render(t_game *game)
{
	draw_texture(&game->frame,
			&game->ammo->sheet[game->ammo->count - game->gun.ammo - 1],
			(t_vecf32){50, SCREEN_Y / 1.25}, 2);
	draw_texture(&game->frame, &game->health->sheet[0],
			(t_vecf32){215, SCREEN_Y / 1.25}, 2);
	draw_texture(&game->frame, &game->pill->sheet[0],
			(t_vecf32){380, SCREEN_Y / 1.25}, 2);
}

void	stt_hud_render(t_game *game)
{
	stt_hands_render(game);
	stt_cards_render(game);
}

void	sprites_render(t_game *game)
{
	stt_hud_render(game);
}
