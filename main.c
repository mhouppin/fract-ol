/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 11:16:32 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 14:01:29 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

/*
** The usage of the program, when no command-line arguments (ore more than one)
** are given. The strings "\e[1m" and "\e[0m" are VT-100 escape sequences,
** which enable and disable bold mode on terminal, respectively.
*/

static void	display_usage(void)
{
	ft_putstr("\nusage: ./fractol --fractal_name - draws a fractal");
	ft_putstr(" (version 1.3)\n");
	ft_putstr("Available fractals:\e[1m\n");
	ft_putstr("\t--mandelbrot (or -m);\n");
	ft_putstr("\t--julia (or -j);\n");
	ft_putstr("\t--multibrot (or -mx)\n");
	ft_putstr("\n\e[0m");
	exit(EXIT_SUCCESS);
}

/*
** If the given command-line argument is not known by the program, an error is
** thrown ("\e[31;1m" puts the text in big red letters), informing the user
** that he must change his parameter.
*/

static void	unknown_command_line_parameter(char *user_input)
{
	ft_putstr("\e[31;1mError\e[0m: unknown parameter \e[1m\"");
	ft_putstr(user_input);
	ft_putstr("\"\e[0m\n");
	exit(EXIT_FAILURE);
}

/*
** The dispatcher of the program. (Brackets are not necessary, bit they help
** the code being more readable.) If the command-line argument is recognized
** by the function, start_fractol is called with the corresponding flag for the
** fractal to draw. Otherwise, an error is thrown (see upper).
*/

static void	launch(char *user_input)
{
	if (!ft_strcmp(user_input, "--mandelbrot") || !ft_strcmp(user_input, "-m"))
	{
		start_fractol(FLAG_MANDELBROT);
	}
	else if (!ft_strcmp(user_input, "--julia") || !ft_strcmp(user_input, "-j"))
	{
		start_fractol(FLAG_JULIA);
	}
	else if (!ft_strcmp(user_input, "--multibrot") ||
			!ft_strcmp(user_input, "-mx"))
	{
		start_fractol(FLAG_MULTIBROT);
	}
	else
	{
		unknown_command_line_parameter(user_input);
	}
}

/*
** Just a small main. Checks for the number of arguments, and call the usage
** or the launcher.
*/

int			main(int argc, char **argv)
{
	if (argc != 2)
		display_usage();
	launch(argv[1]);
	return (0);
}
