#include <unistd.h>
#include "render.h"
#include "types.h"

// Simple DDA line (your original)
void line_draw(t_vecf32 a, t_vecf32 b, t_img *frame, int color)
{
    size_t      i;
    t_vecf32    line = vec_sub(a, b);
    int         x;
    int         y;
    size_t      max = vec_max_coord(a);

    if (max != 0)
    {
        x = line.x / max;
        y = line.y / max;
        i = 0;
        while (i < max)
        {
            a.x += x;
            a.y += y;
            frame_pixel_put(frame, a.x, a.y, color);
            i++;
        }
    }
}

// Fully correct Bresenham (unified version)
void line_draw_bresenham(t_vecf32 a, t_vecf32 b, t_img *frame, int color)
{
    int x0 = (int)a.x;
    int y0 = (int)a.y;
    int x1 = (int)b.x;
    int y1 = (int)b.y;

    int dx = ft_abs(x1 - x0);
    int dy = ft_abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;

    while (1)
    {
        frame_pixel_put(frame, x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

// Rectangle fill (your original)
void quad_draw(t_vecf32 a, t_img *frame, int color, t_vecf32 len)
{
    int x;
    int y = 0;

    while (y < len.y)
    {
        x = 0;
        while (x < len.x)
        {
            frame_pixel_put(frame, a.x + x, a.y + y, color);
            x++;
        }
        y++;
    }
}
