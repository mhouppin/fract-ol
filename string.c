/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   string.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 14:01:42 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 15:12:52 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

size_t	ft_strlen(const char *string)
{
	size_t	i;

	i = 0;
	while (string[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr(const char *string)
{
	write(1, string, ft_strlen(string));
}

int		ft_strcmp(const char *string, const char *reference)
{
	size_t	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] != reference[i])
			return ((unsigned char)string[i] - (unsigned char)reference[i]);
		i++;
	}
	return ((unsigned char)string[i] - (unsigned char)reference[i]);
}

void	ft_bzero(void *data, size_t size)
{
	while (size > 0 && ((uint64_t)data % 8) != 0)
	{
		*((char *)data) = 0;
		data++;
		size--;
	}
	while (size > 7)
	{
		*((int64_t *)data) = 0;
		data += 8;
		size -= 8;
	}
	while (size > 0)
	{
		*((char *)data) = 0;
		data++;
		size--;
	}
}
