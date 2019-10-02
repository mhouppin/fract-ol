/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mandelbrot.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 14:48:16 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 12:19:34 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

int		mandelpoint(register double c_real, register double c_imag,
		t_fracinfo *info)
{
	register double	z_real;
	register double	z_imag;
	register double	z_tmp;
	register int	iter;

	z_real = c_real;
	z_imag = c_imag;
	iter = 0;
	while (iter < info->max_iterations)
	{
		z_tmp = z_real * z_real - z_imag * z_imag + c_real;
		z_imag = 2.0 * z_real * z_imag + c_imag;
		z_real = z_tmp;
		iter++;
		if (z_real * z_real + z_imag * z_imag > 16.0)
			break ;
	}
	if (iter == info->max_iterations)
		return (0);
	return (info->colorset_function(iter - log(log(hypot(z_real, z_imag)))
		/ M_LN2));
}

int		juliapoint(register double z_real, register double z_imag,
		t_fracinfo *info)
{
	register double	c_real;
	register double	c_imag;
	register double	z_tmp;
	register int	iter;

	c_real = info->c_real_value;
	c_imag = info->c_imag_value;
	iter = 0;
	while (iter < info->max_iterations)
	{
		z_tmp = z_real * z_real - z_imag * z_imag + c_real;
		z_imag = 2.0 * z_real * z_imag + c_imag;
		z_real = z_tmp;
		iter++;
		if (z_real * z_real + z_imag * z_imag > 16.0)
			break ;
	}
	if (iter == info->max_iterations)
		return (0);
	return (info->colorset_function(iter - log(log(hypot(z_real, z_imag)))
		/ M_LN2));
}

int		multipoint(register double c_real, register double c_imag,
		t_fracinfo *info)
{
	register double	z_real;
	register double	z_imag;
	register double	radius;
	register double	theta;
	register int	iter;

	z_real = c_real;
	z_imag = c_imag;
	iter = 0;
	radius = hypot(z_real, z_imag);
	while (iter < info->max_iterations)
	{
		radius = pow(radius, info->n_exponent);
		theta = atan2(z_imag, z_real) * info->n_exponent;
		z_real = cos(theta) * radius + c_real;
		z_imag = sin(theta) * radius + c_imag;
		iter++;
		if ((radius = hypot(z_real, z_imag)) > 4.0)
			break ;
	}
	if (iter == info->max_iterations)
		return (0);
	return (info->colorset_function(iter - log(log(hypot(z_real, z_imag)))
			/ log(info->n_exponent)));
}

void	*draw_fractal(void *thread_params)
{
	double		real;
	double		imag;
	int			pos_x;
	int			pos_y;
	t_fracinfo	*info;

	pos_x = ((t_thread_args *)thread_params)->initial_position_x;
	info = ((t_thread_args *)thread_params)->info;
	while (pos_x < FRACTAL_SIZE_X)
	{
		real = info->center_x + (pos_x - (FRACTAL_SIZE_X + 1) / 2.0)
			* info->pixel_width;
		pos_y = ((t_thread_args *)thread_params)->initial_position_y;
		while (pos_y < WINDOW_SIZE_Y)
		{
			imag = info->center_y + ((WINDOW_SIZE_Y + 1) / 2.0 - pos_y)
				* info->pixel_width;
			info->img_pixels[pos_x + pos_y * FRACTAL_SIZE_X] =
				info->function(real, imag, info);
			pos_y += THREAD_PIXEL_JUMP;
		}
		pos_x += THREAD_PIXEL_JUMP;
	}
	return (NULL);
}
