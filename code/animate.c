#include "types.h"
#include "render.h"

void	sprite_sheet_animate(t_img *frame, t_anim *animation, t_vecf32 pos, float scale)
{
	int32_t	i;

	i = animation->i;
	animation->counter += *animation->dt * 30;
	if (animation->counter >= animation->sprites_per_frame)
	{
		animation->counter = 0;
		animation->i++;
		if (animation->i == animation->count)
		{
			animation->i = 0;
			animation->end = true;
		}
	}
	draw_texture(frame, &animation->sheet[i], pos, scale);
}
