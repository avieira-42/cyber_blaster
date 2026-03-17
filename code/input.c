#include <X11/keysym.h>
#include "types.h"
#include "clean.h"

int     key_pressed(int keysym, void *arg)
{
	t_game  *game;

	game = (t_game *)arg;
	if (keysym == XK_w)
		game->player.ori.y += 1;
	if (keysym == XK_a)
		game->player.ori.x += -1;
	if (keysym == XK_s)
		game->player.ori.y += -1;
	if (keysym == XK_d)
		game->player.ori.x += 1;
	if (keysym == XK_l)
		game->player.dir_mod += -1;
	if (keysym == XK_j)
		game->player.dir_mod += 1;
	if (keysym == XK_k)
		game->cam.dist_mod += -1;
	if (keysym == XK_i)
		game->cam.dist_mod += 1;
	if (keysym == XK_Shift_L)
	{
		game->player.speed_mod += 1;
		game->current_step = game->step_fast;
		game->walk->sprites_per_frame--;
	}
	if (keysym == XK_p)
	{
		if (game->pause == false)
			game->pause = true;
		else
			game->pause = false;
	}
	if (keysym == XK_r && game->gun.ammo < 8
			&& game->player.shoot == false)
	{
		if (game->player.reload == false)
			game->player.reload = true;
	}
	if (keysym == XK_Escape)
		free_displays();
	return (1);
}

int     key_released(int keysym, void *arg)
{
	t_game  *game;

	game = (t_game *)arg;
	if (keysym == XK_w)
		game->player.ori.y += -1;
	if (keysym == XK_a)
		game->player.ori.x += 1;
	if (keysym == XK_s)
		game->player.ori.y += 1;
	if (keysym == XK_d)
		game->player.ori.x += -1;
	if (keysym == XK_l)
		game->player.dir_mod += 1;
	if (keysym == XK_j)
		game->player.dir_mod += -1;
	if (keysym == XK_k)
		game->cam.dist_mod += 1;
	if (keysym == XK_i)
		game->cam.dist_mod += -1;
	if (keysym == XK_Shift_L)
	{
		game->player.speed_mod += -1;
		game->current_step = game->step;
		game->walk->sprites_per_frame++;
	}
	return (1);
}

int	mouse_pressed(int keysym, int x, int y, void *arg)
{
	t_game  *game;

	(void)x;
	(void)y;
	game = (t_game *)arg;
	if (keysym == 1 && game->player.shoot == false
			&& game->gun.ammo > 0)
	{
		game->gun.ammo--;
		game->player.shoot = true;
		game->player.shoot_sound = true;
		game->player.reload = false;
	}
	else if (keysym == 1 && game->gun.ammo == 0)
		Mix_PlayChannel(3, game->no_ammo, 0);
	return (1);
}

int	mouse_released(int keysym, int x, int y, void *arg)
{
	t_game  *game;

	game = (t_game *)arg;
	(void)x;
	(void)y;
	(void)game;
	(void)keysym;
	/*if (keysym == 1)
		game->player.shoot = true;*/
	return (1);
}

int	mouse_move(int x, int y, void *arg)
{
	t_game	*game;

	game = (t_game *) arg;
	game->player.mouse_mov.x = (x - SCREEN_X / 2) / 100;
	game->player.mouse_mov.y += (y - SCREEN_Y / 2) * -1;
	if (game->player.mouse_mov.y <= -1000.)
		game->player.mouse_mov.y = -1000.;
	if (game->player.mouse_mov.y <= -1200.)
		game->player.mouse_mov.y = -1000.;
	if (game->player.mouse_mov.y >= 3500.)
		game->player.mouse_mov.y = 3500.;
	return (1);
}
