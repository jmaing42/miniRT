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

#ifndef MATH_TYPES_H
# define MATH_TYPES_H

# include "minirt/core/minirt_float_types.h"

typedef struct s_minirt_normal
{
	t_minirt_float	x;
	t_minirt_float	y;
	t_minirt_float	z;
}	t_minirt_normal;

typedef struct s_minirt_scale
{
	t_minirt_float	x;
	t_minirt_float	y;
	t_minirt_float	z;
}	t_minirt_scale;

typedef struct s_minirt_position
{
	t_minirt_float	x;
	t_minirt_float	y;
	t_minirt_float	z;
}	t_minirt_position;

typedef struct s_minirt_distance
{
	t_minirt_float	x;
	t_minirt_float	y;
	t_minirt_float	z;
}	t_minirt_distance;

typedef struct s_minirt_color
{
	t_minirt_float	r;
	t_minirt_float	g;
	t_minirt_float	b;
}	t_minirt_color;

#endif
