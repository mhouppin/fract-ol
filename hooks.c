/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hooks.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 14:09:22 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 12:39:18 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

/*
** These are the functions called by the minilibx when an event is received
** (mouse/key input, window closing, ...)
** Except for close_window(), they all work the same way:
** - If the event modifies the window status (iteration changing,
**   center moving, ...), the image is re-drawn;
** - Else, the event isn't interesting for the display, we quit the function
**   without redrawing the image, which saves us a lot of frames.
*/

int		close_window(t_fracinfo *info)
{
	mlx_destroy_image(info->mlx_ptr, info->image);
	mlx_destroy_image(info->mlx_ptr, info->frame_display_cleaner);
	mlx_destroy_window(info->mlx_ptr, info->win_ptr);
	exit(0);
	return (0);
}

int		key_press(int keycode, t_fracinfo *info)
{
	if (keycode == PAD_ADD || keycode == KEY_EQUAL)
		info->max_iterations += 50;
	else if (keycode == PAD_SUB || keycode == KEY_MINUS)
		info->max_iterations -= (info->max_iterations <= 50) ? 0 : 50;
	else if (keycode == KEY_C)
		info->colorset_number = (info->colorset_number + 1) % COLORSET_QUANTITY;
	else if (keycode == KEY_R)
		reset_params(info);
	else if (keycode == KEY_Q && (info->fractal_type & FLAG_JULIA) != 0)
		randomize_c_value(info);
	else if (keycode == KEY_COMMA && (info->fractal_type & FLAG_MULTIBROT) != 0)
		info->n_exponent = (info->n_exponent <= 1) ? 1 : info->n_exponent - 0.5;
	else if (keycode == KEY_DOT && (info->fractal_type & FLAG_MULTIBROT) != 0)
		info->n_exponent += 0.5;
	else if (keycode == KEY_ESC)
		close_window(info);
	else
		return (NOTHING_TO_DRAW);
	draw_window(info);
	return (DRAWING_DONE);
}

int		mouse_press(int button, int mouse_x, int mouse_y, t_fracinfo *info)
{
	if (button == RIGHT_BUTTON && (info->fractal_type & FLAG_JULIA) != 0
			&& (info->event_flags & MODE_MOUSE_DRAG) == 0)
		info->event_flags ^= MODE_C_EDITION;
	else if (button == LEFT_BUTTON && (info->event_flags & MODE_C_EDITION) == 0)
	{
		save_position(info, mouse_x, mouse_y);
		return (NOTHING_TO_DRAW);
	}
	else if (button == WHEEL_BUTTON && info->fractal_type != FLAG_MULTIBROT)
	{
		if (info->fractal_type == FLAG_MANDELBROT)
			set_julia_c_value(info, mouse_x, mouse_y);
		info->fractal_type = (info->fractal_type == FLAG_MANDELBROT) ?
			FLAG_JULIA : FLAG_MANDELBROT;
	}
	else if (button == SCROLL_DOWN && info->event_flags == 0)
		zoom_at(info, mouse_x, mouse_y, 1.1);
	else if (button == SCROLL_UP && info->event_flags == 0)
		zoom_at(info, mouse_x, mouse_y, 0.909);
	else
		return (NOTHING_TO_DRAW);
	draw_window(info);
	return (DRAWING_DONE);
}

int		mouse_release(int button, int mouse_x, int mouse_y, t_fracinfo *info)
{
	if (button == LEFT_BUTTON && (info->event_flags & MODE_MOUSE_DRAG) != 0)
	{
		mouse_x -= info->mouse_slide_x;
		mouse_y -= info->mouse_slide_y;
		info->center_x -= mouse_x * info->pixel_width;
		info->center_y += mouse_y * info->pixel_width;
		info->mouse_slide_x = 0;
		info->mouse_slide_y = 0;
		info->event_flags ^= MODE_MOUSE_DRAG;
	}
	else
		return (NOTHING_TO_DRAW);
	draw_window(info);
	return (DRAWING_DONE);
}

int		mouse_move(int mouse_x, int mouse_y, t_fracinfo *info)
{
	if ((info->event_flags & MODE_C_EDITION) != 0)
		set_julia_c_value(info, mouse_x, mouse_y);
	else if ((info->event_flags & MODE_MOUSE_DRAG) != 0)
	{
		mouse_x -= info->mouse_slide_x;
		mouse_y -= info->mouse_slide_y;
		info->center_x -= mouse_x * info->pixel_width;
		info->center_y += mouse_y * info->pixel_width;
		info->mouse_slide_x += mouse_x;
		info->mouse_slide_y += mouse_y;
	}
	else
		return (NOTHING_TO_DRAW);
	draw_window(info);
	return (DRAWING_DONE);
}
