/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   colors.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 13:02:51 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 15:40:05 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

int		c_modulus(double iteration_value)
{
	t_color result;

	if (iteration_value < 0.0)
		return (0);
	result.color_bytes[OPACITY] = 0;
	result.color_bytes[RED] = (int)(iteration_value * 16.0) % 256;
	result.color_bytes[GREEN] = (int)(iteration_value * 8.0) % 256;
	result.color_bytes[BLUE] = (int)(iteration_value * 4.0) % 256;
	return (result.color_value);
}

int		c_grayscale(double iteration_value)
{
	t_color	result;

	if (iteration_value < 0.0)
		return (COLOR_BLACK);
	result.color_bytes[OPACITY] = 0;
	result.color_bytes[RED] =
		(unsigned char)(cos(iteration_value / 10.0) * -127 + 128);
	result.color_bytes[GREEN] = result.color_bytes[RED];
	result.color_bytes[BLUE] = result.color_bytes[RED];
	return (result.color_value);
}

int		c_fluid(double iteration_value)
{
	t_color	result;

	if (iteration_value < 0.0)
		return (COLOR_GRAY + 1);
	result.color_bytes[OPACITY] = 0;
	result.color_bytes[RED] =
		(unsigned char)(sin(iteration_value / 10.0) * 127 + 128);
	result.color_bytes[GREEN] = result.color_bytes[RED];
	result.color_bytes[BLUE] =
		(unsigned char)(cos(iteration_value / 64.0) * -63 + 192);
	return (result.color_value);
}
