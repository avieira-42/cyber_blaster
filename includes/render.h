#ifndef RENDER_H
#define RENDER_H

# include "types.h"

void	frame_pixel_put(t_img *frame, int32_t x, int32_t y, int32_t color);
void	line_draw_bresenham(t_vecf32 a, t_vecf32 b, t_img *frame, int32_t color);
void	line_draw_bresenham_v(t_vecf32 a, t_vecf32 b, t_img *frame, int32_t color);
void	line_draw_bresenham_h(t_vecf32 a, t_vecf32 b, t_img *frame, int32_t gamecolor);
void	quad_draw(t_vecf32 a, t_img *frame, int color, t_vecf32 len);
void	window_clear(t_img *frame, int32_t color);
void	space_render(t_game *game);
void	column_render(t_img *frame, t_ray ray, t_player player, int32_t x, t_img *img);
void	draw_texture(t_img *frame, t_img *image, t_vecf32 pos, float scale);
void	fov_draw(t_game *game);
void	player_draw(t_game *game, t_vecf32 map_tile);
void	objects_draw(t_game *game, t_veci32 map_size, t_vecf32 map_tile);
void	ray_draw(t_game *game, t_player player, t_ray ray, int32_t x);
void    grid_draw(t_img *frame, t_vecf32 map_max,
		t_vecf32 map_tile, t_veci32 map_size);
void	sprites_render(t_game *game);
void	sprite_sheet_animate(t_img *frame, t_anim *animation, t_vecf32 pos, float scale);
int32_t	get_color(const t_img *image, int32_t x, int32_t y);

#endif
