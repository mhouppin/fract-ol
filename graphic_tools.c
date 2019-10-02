/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   graphic_tools.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 14:36:09 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 17:00:06 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

void	save_position(t_fracinfo *info, int mouse_x, int mouse_y)
{
	info->mouse_slide_x = mouse_x;
	info->mouse_slide_y = mouse_y;
	info->event_flags |= MODE_MOUSE_DRAG;
}

void	reset_params(t_fracinfo *info)
{
	info->event_flags = 0;
	info->mouse_slide_x = 0;
	info->mouse_slide_y = 0;
	info->center_x = 0.0;
	info->center_y = 0.0;
	info->pixel_width = info->initial_width;
	info->c_real_value = 0.0;
	info->c_imag_value = 0.0;
	info->max_iterations = 100;
	info->colorset_number = 0;
	info->n_exponent = 3.0;
}

void	randomize_c_value(t_fracinfo *info)
{
	srand(time(NULL));
	info->c_real_value = (double)((rand() % 10001) - 5000) * 0.0003;
	info->c_imag_value = (double)((rand() % 10001) - 5000) * 0.0003;
}

void	zoom_at(t_fracinfo *info, int mouse_x, int mouse_y, double zoom_scale)
{
	info->center_x += (mouse_x - (FRACTAL_SIZE_X + 1) / 2) * info->pixel_width;
	info->center_y += ((WINDOW_SIZE_Y + 1) / 2 - mouse_y) * info->pixel_width;
	info->pixel_width *= zoom_scale;
	info->center_x -= (mouse_x - (FRACTAL_SIZE_X + 1) / 2) * info->pixel_width;
	info->center_y -= ((WINDOW_SIZE_Y + 1) / 2 - mouse_y) * info->pixel_width;
}

void	set_julia_c_value(t_fracinfo *info, int mouse_x, int mouse_y)
{
	info->c_real_value = info->center_x +
		((double)(mouse_x - (FRACTAL_SIZE_X + 1) / 2) * info->pixel_width);
	info->c_imag_value = info->center_y +
		((double)((WINDOW_SIZE_Y + 1) / 2 - mouse_y) * info->pixel_width);
}
