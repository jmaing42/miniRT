/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_file_name (file name is useless too)          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42header-remover <whatever@example.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by file history     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/bmp.h"

#include <stdbool.h>
#include <stdlib.h>

static uint32_t	u32_to_le(uint32_t u32)
{
	const uint32_t		test = 42;
	const char *const	source = (const char *)&u32;
	uint32_t			result;
	char *const			dest = (char *)&result;

	if (*((char *)&test))
		return (u32);
	dest[0] = source[3];
	dest[1] = source[2];
	dest[2] = source[1];
	dest[3] = source[0];
	return (result);
}

static uint16_t	u16_to_le(uint16_t u16)
{
	const uint16_t		test = 42;
	const char *const	source = (const char *)&u16;
	uint16_t			result;
	char *const			dest = (char *)&result;

	if (*((char *)&test))
		return (u16);
	dest[0] = source[1];
	dest[1] = source[0];
	return (result);
}

static void	fill_header(t_minirt_bmp *self, char *result)
{
	const size_t	row_padding = (4 - (self->width * 3) % 4) % 4;
	const size_t	row_size = self->width * 3 + row_padding;
	const size_t	whole_size = row_size * self->height;

	result[0] = 'B';
	result[1] = 'M';
	*((uint32_t *)(result + 2)) = u32_to_le(54 + (uint32_t)whole_size);
	*((uint32_t *)(result + 6)) = u32_to_le(0);
	*((uint32_t *)(result + 10)) = u32_to_le(54);
	*((uint32_t *)(result + 14)) = u32_to_le(40);
	*((uint32_t *)(result + 18)) = u32_to_le((uint32_t)self->width);
	*((uint32_t *)(result + 22)) = u32_to_le((uint32_t)self->height);
	*((uint16_t *)(result + 26)) = u16_to_le(1);
	*((uint16_t *)(result + 28)) = u16_to_le(24);
	*((uint32_t *)(result + 30)) = u32_to_le(0);
	*((uint32_t *)(result + 34)) = u32_to_le((uint32_t)whole_size);
	*((uint32_t *)(result + 38)) = u32_to_le(0);
	*((uint32_t *)(result + 42)) = u32_to_le(0);
	*((uint32_t *)(result + 46)) = u32_to_le(256);
	*((uint32_t *)(result + 50)) = u32_to_le(0);
}

static void	fill_body(t_minirt_bmp *self, char *result)
{
	const size_t	row_padding = (4 - (self->width * 3) % 4) % 4;
	size_t			offset;
	size_t			y;
	size_t			x;
	size_t			i;

	offset = 0;
	y = self->height;
	while (y--)
	{
		x = (size_t)-1;
		while (++x < self->width)
		{
			result[offset++] = self->extra[self->width * y + x].b * 255;
			result[offset++] = self->extra[self->width * y + x].g * 255;
			result[offset++] = self->extra[self->width * y + x].r * 255;
		}
		i = (size_t)-1;
		while (++i < row_padding)
			result[offset++] = 0;
	}
}

t_err	t_image_serialize(t_minirt_bmp *self, char **out, size_t *out_length)
{
	const size_t	row_padding = (4 - (self->width * 3) % 4) % 4;
	const size_t	row_size = self->width * 3 + row_padding;
	const size_t	whole_size = row_size * self->height;
	const size_t	length = 54 + whole_size;
	char *const		result = malloc(length);

	if (!result)
		return (true);
	fill_header(self, result);
	fill_body(self, result + 54);
	*out_length = length;
	*out = result;
	return (false);
}
