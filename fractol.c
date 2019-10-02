/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fractol.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 13:31:39 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 12:42:57 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_toolbox(t_fracinfo *info, int fractal_type)
{
	static const t_command	commands[10] = {{7, "[+] -> increment it_max"},
		{7, "[-] -> decrement it_max"}, {7, "[wheel] -> zoom in or out"},
		{2, "[R-click] -> modify c value"}, {7, "[L-click] -> drag and slide"},
		{7, "[C] -> change color setup"}, {7, "[R] -> reset fractal"},
		{2, "[Q] -> randomize c value"}, {7, "[Esc] -> quit program"},
		{4, "[>] (or [<]) -> change Multibrot exp."}};
	register int			command_i;
	register int			position_y;

	command_i = 0;
	position_y = 10;
	while (command_i < 10)
	{
		if (fractal_type & commands[command_i].fractal_bitset)
		{
			mlx_string_put(info->mlx_ptr, info->win_ptr,
				FRACTAL_SIZE_X + 10, position_y, COLOR_WHITE,
				(char *)commands[command_i].string_info);
			position_y += 40;
		}
		command_i++;
	}
}

static void	load_hooks_and_create_images(t_fracinfo *info)
{
	int		not_used;

	mlx_do_key_autorepeatoff(info->mlx_ptr);
	mlx_hook(info->win_ptr, KEY_PRESS, 0, &key_press, info);
	mlx_hook(info->win_ptr, MOUSE_PRESS, 0, &mouse_press, info);
	mlx_hook(info->win_ptr, MOUSE_RELEASE, 0, &mouse_release, info);
	mlx_hook(info->win_ptr, MOUSE_MOVE, 0, &mouse_move, info);
	mlx_hook(info->win_ptr, CLOSE_WINDOW, 0, &close_window, info);
	info->image = mlx_new_image(info->mlx_ptr, FRACTAL_SIZE_X, WINDOW_SIZE_Y);
	ft_assert(info->image != NULL, "mlx_new_image(), line 51");
	info->img_pixels = (int *)mlx_get_data_addr(info->image, &not_used,
		&not_used, &not_used);
	info->frame_display_cleaner = mlx_new_image(info->mlx_ptr, 90, 40);
	ft_assert(info->frame_display_cleaner != NULL, "mlx_new_image(), line 56");
	info->cln_pixels = (int *)mlx_get_data_addr(info->frame_display_cleaner,
		&not_used, &not_used, &not_used);
	ft_bzero(info->cln_pixels, 90 * 40 * sizeof(int));
	mlx_string_put(info->mlx_ptr, info->win_ptr, FRACTAL_SIZE_X + 100,
		WINDOW_SIZE_Y - 50, COLOR_WHITE, "milliseconds");
}

void		start_fractol(int fractal_type)
{
	t_fracinfo	info;

	ft_assert((info.mlx_ptr = mlx_init()) != NULL, "mlx_init(), line 69");
	info.win_ptr = mlx_new_window(info.mlx_ptr, FRACTAL_SIZE_X + TOOLBAR_SIZE_X,
		WINDOW_SIZE_Y, "Fractol v1.3");
	ft_assert(info.win_ptr != NULL, "mlx_new_window(), line 70");
	draw_toolbox(&info, fractal_type);
	load_hooks_and_create_images(&info);
	info.fractal_type = fractal_type;
	info.event_flags = (fractal_type == FLAG_JULIA) ? MODE_C_EDITION : 0;
	info.mouse_slide_x = 0;
	info.mouse_slide_y = 0;
	info.center_x = 0.0;
	info.center_y = 0.0;
	info.pixel_width = 6.0 / FRACTAL_SIZE_X;
	info.initial_width = info.pixel_width;
	info.c_real_value = 0.0;
	info.c_imag_value = 0.0;
	info.n_exponent = 3.0;
	info.max_iterations = 100;
	info.colorset_number = 0;
	draw_window(&info);
	mlx_loop(info.mlx_ptr);
}
