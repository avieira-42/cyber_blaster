#ifndef INIT_H
#define INIT_H

#include "types.h"

void	screen_init(t_game *game);
void	map_init(t_game *game);
void	player_init(t_game *game);
void	cam_init(t_cam *cam, t_player player);
void	sprites_init(t_game *game);
t_anim	*sprite_sheet_init(void *mlx, char *base_path, int32_t count, char *file_type);

#endif
