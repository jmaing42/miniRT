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
#include <stdint.h>
#include <stdlib.h>

typedef struct s_context
{
	size_t			offset;
	size_t			width;
	bool			reverse_width;
	size_t			height;
	bool			reverse_height;
	size_t			row_padding;
	size_t			row_size;
	size_t			whole_size;
	const uint8_t	*str;
}	t_context;

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

static void	fill(void *context, size_t x, size_t y, t_minirt_bmp_pixel *out)
{
	t_context *const	l = context;
	size_t				actual_x;
	size_t				actual_y;

	actual_x = x;
	actual_y = y;
	if (l->reverse_width)
		actual_x = l->width - 1 - x;
	if (!l->reverse_height)
		actual_y = l->height - 1 - y;
	out->r = l->str[
		l->offset + l->row_size * (l->height - actual_y - 1) + 3 * actual_x + 2
	];
	out->g = l->str[
		l->offset + l->row_size * (l->height - actual_y - 1) + 3 * actual_x + 1
	];
	out->b = l->str[
		l->offset + l->row_size * (l->height - actual_y - 1) + 3 * actual_x + 0
	];
}

static size_t	abs_ex(int32_t i, bool *out_was_negative)
{
	*out_was_negative = (i < 0);
	if (*out_was_negative)
		return (-i);
	return (i);
}

t_err	minirt_bmp_deserialize(
	const void *buffer,
	size_t length,
	t_minirt_bmp **out
)
{
	t_context			l;
	const char *const	str = buffer;

	*out = NULL;
	if (length <= 54 || str[0] != 'B' || str[1] != 'M' || u16_to_le(
			*((uint16_t *)&str[28])) != 24 || u32_to_le(*(
				(uint32_t *)&str[30])) != 0)
		return (false);
	l.offset = *((uint32_t *)&str[10]);
	l.width = abs_ex((int32_t)u32_to_le(*((uint32_t *)&str[18])),
			&l.reverse_width);
	l.height = abs_ex((int32_t)u32_to_le(*((uint32_t *)&str[22])),
			&l.reverse_height);
	l.row_padding = (4 - (l.width * 3) % 4) % 4;
	l.row_size = l.width * 3 + l.row_padding;
	l.whole_size = l.row_size * l.height - l.row_padding;
	l.str = (uint8_t *)str;
	if (length < l.offset + l.whole_size)
		return (false);
	*out = minirt_bmp_new(l.width, l.height, fill, &l);
	if (!*out)
		return (true);
	return (false);
}
