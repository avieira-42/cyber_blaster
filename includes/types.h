#ifndef TYPES_H
#define TYPES_H

#include "libft_math.h"
#include <stdio.h>
#include <stdbool.h>

#define BLACK 0x000000
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define WHITE 0xFFFFFF
#define SPRITE_X 128
#define SPRITE_Y 128
#define SCREEN_X 1920.0
#define SCREEN_Y 1024.0

typedef enum	e_card
{
	N,
	S,
	E,
	W,
}	t_card;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int32_t	bpp;
	int32_t	l_len;
	int32_t	endian;
	int32_t	width;
	int32_t	height;;
}	t_img;

typedef struct	s_anim
{
	int32_t		i;
	int32_t		sprites_per_frame;
	t_img		*sheet;
	float		counter;
	int32_t		count;
	char		*base_path;
	char		*file_type;
	bool		end;
	float		*dt;

}	t_anim;
 
typedef struct	s_cam
{
	t_vecf32	pos;
	t_vecf32	dir;
	int32_t		half_len;
	int32_t		dist_mod;
	float		dist;
}	t_cam;

typedef struct s_player
{
	t_vecf32	dir;
	t_vecf32	pos;
	t_vecf32	ori;
	t_vecf32	mouse_mov;
	int32_t		dir_mod;
	float		speed;
	float		speed_mod;
	bool		reload;
	bool		shoot;
}	t_player;

typedef struct	s_ray
{
	t_vecf32	dir;
	t_vecf32	p_pos;
	t_veci32	p_map_pos;
	t_veci32	step_ori;
	t_vecf32	step_size;
	t_vecf32	ray_len;
	t_vecf32	hit_pos;
	int32_t		color;
	int32_t		side;
	float		final_len;
	float		perp_wall_dist;
	bool		hit;
}	t_ray;

typedef struct	s_column
{
	t_vecf32	start;
	t_vecf32	end;
	float		height;

}	t_column;

typedef	struct	s_map
{
	float		height;
	float		width;
	float		tile_y;
	float		tile_x;
	float		max_x;
	float		max_y;
	char		*grid[500];
}	t_map;

typedef struct s_game
{
	//	definitive
	t_cam		cam;
	t_player	player;
	t_map		map;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		frame;

	//	maybe tmp
	int32_t		vd;
	long long	t0;
	float		dt;
	int32_t		start;
	int32_t		here;
	// hud
	t_anim	*reload;
	t_anim	*shoot;
	t_anim	*walk;
	t_anim	*ammo;
	t_anim	*health;
	t_anim	*pill;
	t_anim	*city;
	// tiles
	// background
	// enemies
}	t_game;

#endif
