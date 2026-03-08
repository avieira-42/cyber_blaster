#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include "../libs/minilibx-linux/mlx.h"

void    load_sprite(void *mlx_ptr, t_img *sprite, const char *filepath)
{
    int w;
    int h;

    sprite->img = mlx_xpm_file_to_image(mlx_ptr, (char *)filepath, &w, &h);
    if (!sprite->img)
    {
        sprite->addr = NULL;
        return ;
    }
    sprite->width = (float)w;
    sprite->height = (float)h;
    sprite->addr = mlx_get_data_addr(sprite->img,
            &sprite->bpp, &sprite->l_len, &sprite->endian);
}

void    load_sprite_group(void *mlx_ptr,
            t_sprite *dest_array,
            const char *base_path,
            int count,
            int start_index)
{
    int     i;
    char    fullpath[256];

    i = 0;
    while (i < count)
    {
        snprintf(fullpath, sizeof(fullpath),
            "%s%d.xpm", base_path, start_index + i);
        load_sprite(mlx_ptr, &dest_array[i].image, fullpath);
        i++;
    }
}
