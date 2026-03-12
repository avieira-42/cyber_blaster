#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../libs/minilibx-linux/mlx.h"
#include "libft_math.h"
#include "types.h"
#include "update.h"
#include "init.h"

void	screen_init(t_game *game)
{
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, SCREEN_X, SCREEN_Y, "doom_blade");
	game->t0 = time_get();
	time_delta_get(game);
	game->vd = 1 / u_rsqrt(game->map.width * game->map.width
			+ game->map.height * game->map.height);
	game->frame.img = mlx_new_image(game->mlx_ptr, SCREEN_X, SCREEN_Y);
	game->frame.addr = mlx_get_data_addr(
			game->frame.img, &game->frame.bpp, &game->frame.l_len,
				&game->frame.endian);
	if (game->frame.addr == NULL)
		return ;
}

void	player_init(t_game *game)
{
	game->player.dir = (t_vecf32){0.71, 0.71};
	game->player.ori = (t_vecf32){0, 0};
	game->player.dir_mod = 0;
	game->player.speed = 3;
	game->player.speed_mod = 1;
	game->player.mouse_mov = (t_vecf32){0, 0};
	game->player.reload = false;
	game->player.shoot = false;
	game->player.shoot_sound = false;
}

void	cam_init(t_cam *cam, t_player player)
{
	cam->dist = 1;
	cam->dist_mod = 0;
	cam->half_len = 10;
	cam->dir = (t_vecf32){-0.71, 0.71};
	cam->pos = vec_sum(player.pos,
				vec_scalar_mult(player.dir, cam->dist));
}

void	sprites_init(t_game *game)
{
	// HUD INIT
	// hands
	game->shoot = sprite_sheet_init(game->mlx_ptr,
			"assets/sprites/xpm/hud/hands/hands_shooting", 5, ".xpm");
	game->shoot->sprites_per_frame = 2;
	game->shoot->dt = &game->dt;
	game->walk = sprite_sheet_init(game->mlx_ptr,
			"assets/sprites/xpm/hud/hands/hands_walking", 8, ".xpm");
	game->walk->sprites_per_frame = 3;
	game->walk->dt = &game->dt;
	game->reload = sprite_sheet_init(game->mlx_ptr,
			"assets/sprites/xpm/hud/hands/hands_reloading", 17, ".xpm");
	game->reload->sprites_per_frame = 6;
	game->reload->dt = &game->dt;
	// cards
	game->ammo = sprite_sheet_init(game->mlx_ptr,
			"assets/sprites/xpm/hud/hud_ammo/ammo", 9, ".xpm");
	game->ammo->dt = &game->dt;
	game->health = sprite_sheet_init(game->mlx_ptr,
			"assets/sprites/xpm/hud/hud_health/health", 10, ".xpm");
	game->health->dt = &game->dt;
	game->pill = sprite_sheet_init(game->mlx_ptr,
			"assets/sprites/xpm/hud/hud_pill/pill", 2, ".xpm");
	game->pill->dt = &game->dt;
	// BACKGROUND
	game->city = sprite_sheet_init(game->mlx_ptr,
			"assets/sprites/xpm/tiles/city", 4, ".xpm");
	game->city->dt = &game->dt;
}

void	audio_init(t_game *game)
{
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_AllocateChannels(10);
	game->gun_shot = Mix_LoadWAV("assets/audio/gun_shot.wav");
	game->gun_reload = Mix_LoadWAV("assets/audio/gun_reload.wav");
	game->step = Mix_LoadWAV("assets/audio/step.wav");
	game->step_fast = Mix_LoadWAV("assets/audio/step_fast.wav");
	game->current_step = game->step;
}

void	gun_init(t_game *game)
{
	game->gun.ammo = 8;
	game->gun.max_ammo = 8;
	game->gun.first_i = -1;
}
