/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   assert.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 13:00:29 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 14:07:21 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

void	ft_assert(int condition, const char *where)
{
	if (condition)
		return ;
	ft_putstr("\e[31;1mError\e[0m (");
	ft_putstr(where);
	ft_putstr("): stopping program.\n");
	exit(EXIT_FAILURE);
}
