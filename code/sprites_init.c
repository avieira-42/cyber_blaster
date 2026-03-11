#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include "../libs/minilibx-linux/mlx.h"
#include "../libs/libft/include/libft.h"

static
void	stt_path_cat(char *path, t_anim *anim, int32_t sprite_number)
{
	size_t		i;
	size_t		j;
	const char	*number = ft_itoa(sprite_number + 1);

	i = 0;
	j = 0;
	while (anim->base_path[i])
	{
		path[j] = anim->base_path[i];
		i++;
		j++;
	}
	i = 0;
	while(number[i])
	{
		path[j] = number[i];
		i++;
		j++;
	}
	i = 0;
	while (anim->file_type[i])
	{
		path[j] = anim->file_type[i];
		i++;
		j++;
	}
	path[j] = '\0';
}

static
void    stt_load_sprite(void *mlx_ptr, t_img *sprite, char *filepath)
{
    sprite->img = mlx_xpm_file_to_image(mlx_ptr, filepath,
			&sprite->width, &sprite->height);
    if (!sprite->img)
    {
        sprite->addr = NULL;
        return ;
    }
    sprite->addr = mlx_get_data_addr(sprite->img,
            &sprite->bpp, &sprite->l_len, &sprite->endian);
}

static
void    stt_load_animation(void *mlx_ptr, t_anim *animation)
{
    int32_t     i;
    char		path[200];

	animation->sheet = malloc(sizeof(t_img) * animation->count);
    i = 0;
    while (i < animation->count)
    {
		stt_path_cat(path, animation, i);
		stt_load_sprite(mlx_ptr, &(animation->sheet[i]), path);
        i++;
    }
}

t_anim	*sprite_sheet_init(void *mlx, char *base_path, int32_t count, char *file_type)
{
	t_anim	*anim;

	anim = malloc(sizeof(t_anim));
	anim->base_path = ft_strdup(base_path);
	anim->count = count;
	anim->file_type = ft_strdup(file_type);
	anim->i = 0;
	anim->end = false;
	stt_load_animation(mlx, anim);
	return (anim);
}
