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

#ifndef BMP_TYPES_H
# define BMP_TYPES_H

# include <stddef.h>
# include <stdint.h>

typedef struct s_minirt_bmp_pixel
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_minirt_bmp_pixel;

typedef struct s_minirt_bmp
{
	size_t				width;
	size_t				height;
	t_minirt_bmp_pixel	extra[];
}	t_minirt_bmp;

#endif
