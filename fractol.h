/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fractol.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 10:49:18 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/08 17:01:07 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <pthread.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
# include "minilibx/mlx.h"
# include "key_codes.h"
# include "mouse_codes.h"

/*
** Window size macros
*/

# define FRACTAL_SIZE_X		1400
# define WINDOW_SIZE_Y		1000
# define TOOLBAR_SIZE_X		400

/*
** Thread information macros
*/

# define THREAD_PIXEL_JUMP	4
# define THREAD_QUANTITY	(THREAD_PIXEL_JUMP * THREAD_PIXEL_JUMP)

/*
** Fractal flags (used for the toolbar)
*/

# define FLAG_MANDELBROT	1
# define FLAG_JULIA			2
# define FLAG_MULTIBROT		4

# define FLAG_NO_MULTIBROT	3
# define FLAG_NO_JULIA		5
# define FLAG_NO_MANDELBROT	6

# define FLAG_ALL_FRACTALS	7

/*
** Number of defined colorsets
*/

# define COLORSET_QUANTITY	3

/*
** Macros to clarify hook handling in the program
*/

# define NOTHING_TO_DRAW	0
# define DRAWING_DONE		1

/*
** Hook defines used by minilibx to know the type of event
*/

# define KEY_PRESS			2
# define MOUSE_PRESS		4
# define MOUSE_RELEASE		5
# define MOUSE_MOVE			6
# define CLOSE_WINDOW		17

/*
** Flags used by hooks to detect mouse dragging or Julia c-edition
*/

# define MODE_C_EDITION		1
# define MODE_MOUSE_DRAG	2

/*
** Defines for the color union, to know which byte represents which aspect
** of the color
*/

# define OPACITY			3
# define RED				2
# define GREEN				1
# define BLUE				0

/*
** Structure for toolbar display.
**
** - fractal_bitset: for which fractals should the string be displayed.
** - string_info: the string to be displayed.
*/

struct	s_command
{
	int			fractal_bitset;
	const char	*string_info;
};

/*
** Union for color settings.
**
** - color_value: the integer representing the color.
** - color_bytes: the individual bytes of the color (opacity, red, green, blue).
*/

union	u_color
{
	int				color_value;
	unsigned char	color_bytes[4];
};

/*
** Enum for defining some colors.
*/

enum	e_colors
{
	COLOR_WHITE = 0x00ffffff,
	COLOR_GRAY = 0x00808080,
	COLOR_BLACK = 0x00000000,
};

/*
** Typedef for the coloring function. The double represents
** the number of iterations.
*/

typedef int						(*t_cset)(double);
typedef int						(*t_colorset)(double);

/*
** Main structure of the program. Always passed as a pointer to functions,
** to avoid global copy and allow content edition through the program.
**
** - mlx_ptr, win_ptr: basic pointers given by mlx_functions.
**
** - image: pointer to window image.
** - frame_display_cleaner: image used to clean the last number of frames.
** - img_pixels, cln_pixels: raw pixel data for the two images.
**
** - fractal_type: current type of the fractal.
** - event_flags: contains a field of the possible current events running
**   (mouse dragging or Julia c-edition mode).
**
** - mouse_slide_xy: the last xy-position of the mouse, used for mouse dragging.
**
** - center_x, center_y: xy-coordinates of the center of the fractal.
**
** - pixel_width: the current size of a pixel.
** - initial_width: the initial size of a pixel (determined by window size).
**
** - c_real(imag)_value: the current value of the complex c for Julia rendering
**   (next_z = z * z + c).
**
** - n_exponent: the current value of the exponent n for Multibrot rendering
**   (next_z = power(z, n) + initial_z
**
** - max_iterations: the current value of the maximal iterations for a point
**   (i.e when is the point considered to be part of the fractal).
**
** - colorset_number: current used colorset.
** - colorset_function: current function pointer of the colorset.
*/

struct	s_fracinfo
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*image;
	void	*frame_display_cleaner;
	int		*img_pixels;
	int		*cln_pixels;
	int		fractal_type;
	int		event_flags;
	int		mouse_slide_x;
	int		mouse_slide_y;
	double	center_x;
	double	center_y;
	double	pixel_width;
	double	initial_width;
	double	c_real_value;
	double	c_imag_value;
	double	n_exponent;
	int		max_iterations;
	int		colorset_number;
	t_cset	colorset_function;
	int		(*function)(double, double, struct s_fracinfo *);
};

/*
** Structure passed to each drawing thread.
**
** - info: pointer to the main program structure.
** - initial_position_xy: xy-position of the first pixel to draw.
*/

struct	s_thread_args
{
	struct s_fracinfo	*info;
	int					initial_position_x;
	int					initial_position_y;
};

/*
** Typedefs for the structs and union declared.
*/

typedef union u_color			t_color;
typedef struct s_command		t_command;
typedef struct s_fracinfo		t_fracinfo;
typedef struct s_thread_args	t_thread_args;
typedef int						(*t_draw_function)(double, double, t_fracinfo*);

/*
** - ft_assert: checks for the condition given, and, if false, throws an
**   error. Where is a string containing the placement of the call.
**
** - ft_putstr: outputs the given string.
**
** - ft_strcmp: compares the two given strings, and returns 0 if the strings
**   are identical.
**
** - ft_bzero: fill a data field with zeros.
*/

void	ft_assert(int condition, const char *where);
void	ft_putstr(const char *string);
int		ft_strcmp(const char *string, const char *reference);
void	ft_bzero(void *data, size_t	size);

/*
** - start_fractol: start the drawing for the given fractal.
** - draw_window: main handler of the drawing.
*/

void	start_fractol(int fractal_number);
void	draw_window(t_fracinfo *info);

/*
** - key_press: function for handling key-pressing events.
** - mouse_press: function for handling mouse-pressing events.
** - mouse_release: function for handling mouse-releasing events.
** - mouse_move: function for handling mouse-moving events.
** - close_window: function for handling window-closing events. Stops the
**   program execution.
*/

int		key_press(int keycode, t_fracinfo *info);
int		mouse_press(int button, int mouse_x, int mouse_y, t_fracinfo *info);
int		mouse_release(int button, int mouse_x, int mouse_y, t_fracinfo *info);
int		mouse_move(int mouse_x, int mouse_y, t_fracinfo *info);
int		close_window(t_fracinfo *info);

/*
** - save_position: saves the last position of the mouse.
** - reset_params: restores the initial parameters of the main structure.
** - randomize_c_value: sets the Julia c-value to a new random complex number.
** - zoom_at: zooms at the given mouse position, in or out.
** - set_julia_c_value: edits the Julia c-value acording to the mouse position.
*/

void	save_position(t_fracinfo *info, int mouse_x,
		int mouse_y) __attribute__((always_inline));
void	reset_params(t_fracinfo *info) __attribute__((always_inline));
void	randomize_c_value(t_fracinfo *info) __attribute__((always_inline));
void	zoom_at(t_fracinfo *info, int mouse_x, int mouse_y,
		double zoom_scale) __attribute__((always_inline));
void	set_julia_c_value(t_fracinfo *info, int mouse_x,
		int mouse_y) __attribute__((always_inline));

/*
** - xxxpoint: the thread draws his given portion of the xxx fractal.
*/

void	*draw_fractal(void *thread_params);
int		mandelpoint(double c_real, double c_imag, t_fracinfo *info);
int		juliapoint(double c_real, double c_imag, t_fracinfo *info);
int		multipoint(double c_real, double c_imag, t_fracinfo *info);

/*
** - c_xxx: function used to compute a color acording to the given iteration
**   value.
*/

int		c_modulus(double iteration_value);
int		c_grayscale(double iteration_value);
int		c_fluid(double iteration_value);

#endif
