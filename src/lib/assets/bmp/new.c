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

#include "bmp_internal.h"

#include <stdlib.h>

t_minirt_bmp	*new(
	size_t width,
	size_t height,
	void (*fill)(void *context, size_t x, size_t y, t_minirt_bmp_pixel *out),
	void *context
)
{
	const size_t		size
		= sizeof(t_minirt_bmp) + sizeof(t_minirt_bmp_pixel) * width * height;
	t_minirt_bmp *const	result = malloc(size);
	size_t				y;
	size_t				x;

	result->width = width;
	result->height = height;
	y = (size_t)-1;
	while (++y < result->height)
	{
		x = (size_t)-1;
		while (++x < result->width)
			fill(context, x, y, &result->extra[y * result->width + x]);
	}
	return (result);
}
