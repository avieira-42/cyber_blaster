#include <unistd.h>
#include "types.h"

void	frame_pixel_put(t_img *frame, int32_t x, int32_t y, int32_t color)
{ char	*dst;
	if (x < 0 || x >= SCREEN_X || y < 0 || y >= SCREEN_Y)
		return ;
	dst = frame->addr + (y * frame->l_len + x * frame->bpp / 8);
	*(unsigned int *)dst = color;
}

void	window_clear(t_img *frame, int32_t color)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < SCREEN_Y)
	{
		j = 0;
		while (j < SCREEN_X)
		{
			frame_pixel_put(frame, j, i, color);
			j++;
		}
		i++;
	}
}

int32_t	get_color(const t_img *image, int32_t x, int32_t y)
{
	int32_t	*color;

	if (x < 0 || x >= image->width || y < 0 || y > image->height)
		return (0);
	color = (int32_t *) (image->addr + x * (image->bpp / 8) + y * image->l_len);
	return (*color);
}

void	draw_texture(t_img *frame, t_img *image, t_vecf32 pos, float scale)
{
	int32_t	x;
	int32_t	y;
	int32_t	color;	

	x = 0;
	while (x < image->width * scale)
	{
		y = 0;
		while (y < image->height * scale)
		{
			color = get_color(image, x / scale, y / scale);
			if (color != 2228223 && color != 1441791)
				frame_pixel_put(frame, pos.x + x, pos.y + y, color);
			y++;
		}
		x++;
	}
}
