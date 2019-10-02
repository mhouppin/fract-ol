/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 13:13:45 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 12:15:49 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

/*
** get_fractal() returns the pointer to the draw function
** for the fractal type specified.
*/

static t_draw_function	get_fractal(int fractal_type)
{
	if (fractal_type == FLAG_MANDELBROT)
		return (&mandelpoint);
	if (fractal_type == FLAG_JULIA)
		return (&juliapoint);
	return (&multipoint);
}

/*
** get_colorset() sets the function pointer for the coloring in
** the structure info.
*/

static void				get_colorset(t_fracinfo *info)
{
	static const t_colorset	color_functions[COLORSET_QUANTITY] = {&c_modulus,
		&c_grayscale, &c_fluid};

	info->colorset_function = color_functions[info->colorset_number];
}

/*
** get_draw_time() displays the number of milliseconds used for
** the fractal drawing.
*/

static void				get_draw_time(clock_t timer, t_fracinfo *info)
{
	int			milliseconds;
	static char	buffer[7];
	int			i;

	milliseconds = (timer * 1000.0 / CLOCKS_PER_SEC);
	buffer[6] = '\0';
	i = 5;
	while (i >= 0)
	{
		buffer[i] = (milliseconds % 10) + '0';
		if ((milliseconds /= 10) == 0)
			break ;
		i--;
	}
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr,
		info->frame_display_cleaner, FRACTAL_SIZE_X + 10, WINDOW_SIZE_Y - 50);
	mlx_string_put(info->mlx_ptr, info->win_ptr, FRACTAL_SIZE_X + 10,
		WINDOW_SIZE_Y - 50, COLOR_WHITE, buffer + i);
}

/*
** draw_window() is the main_handler of the fractal drawing: it retrieves
** the function pointers for the fractal drawing via get_fractal() and
** get_colorset(), then initializes the threads' structure and launches them.
**
** The drawing method partitions the image like that:
** (example for 8x8 pixels zone)
**
** 12341234
** 56785678
** 9abc9abc
** def0def0
** 12341234
** 56785678
** 9abc9abc
** def0def0
**
** Then, the thread 1 will draw the pixels '1', the thread 2 will draw
** the pixels '2', and so on. This avoids a thread to be much slower than the
** others, possibly because of a 'black zone' on the screen that requires
** much more iterations than the other zones.
** All threads should have the same work charge, because the full loading time
** will always be relative to the slower thread.
*/

void					draw_window(t_fracinfo *info)
{
	clock_t			timer_start;
	pthread_t		threads[THREAD_QUANTITY];
	t_thread_args	thread_args[THREAD_QUANTITY];
	int				thread_i;

	info->function = get_fractal(info->fractal_type);
	get_colorset(info);
	thread_i = 0;
	timer_start = clock();
	while (thread_i < THREAD_QUANTITY)
	{
		thread_args[thread_i].info = info;
		thread_args[thread_i].initial_position_x = thread_i % THREAD_PIXEL_JUMP;
		thread_args[thread_i].initial_position_y = thread_i / THREAD_PIXEL_JUMP;
		pthread_create(&(threads[thread_i]), NULL, &draw_fractal,
			&(thread_args[thread_i]));
		thread_i++;
	}
	thread_i = 0;
	while (thread_i < THREAD_QUANTITY)
		pthread_join(threads[thread_i++], NULL);
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->image, 0, 0);
	get_draw_time(clock() - timer_start, info);
}
