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

#ifndef BMP_INTERNAL_H
# define BMP_INTERNAL_H

# include "minirt/bmp.h"

typedef void	(*t_minirt_bmp_new_fill)(
					void *context,
					size_t x,
					size_t y,
					t_minirt_bmp_pixel *out);

t_minirt_bmp	*minirt_bmp_new(
					size_t width,
					size_t height,
					t_minirt_bmp_new_fill fill,
					void *context);

#endif
