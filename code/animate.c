#include "types.h"
#include "render.h"

void	sprite_sheet_animate(t_img *frame, t_anim *animation, t_vecf32 pos, float scale)
{
	if (++(animation->counter) == animation->sprites_per_frame)
	{
		animation->counter = 0;
		if ((animation->i)++ == animation->count - 1)
			animation->i = 0;
	}
	draw_texture(frame, &animation->sheet[animation->i], pos, scale);
}
