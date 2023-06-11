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

#ifndef MINIRT_TYPES_H
# define MINIRT_TYPES_H

# include <stddef.h>

# include "./minirt_f3.h"

typedef struct s_minirt_image
{
	size_t		width;
	size_t		height;
	t_minirt_f3	pixels[];
}	t_minirt_image;

typedef struct s_minirt_ray
{
	t_minirt_f3	direction;
}	t_minirt_ray;

struct			s_minirt_hit;

typedef t_err	(*t_minirt_hit_get_material)(
					struct s_minirt_hit *self,
					t_minirt_material **out);

typedef struct s_minirt_hit
{
	t_minirt_hit_get_material	material;
}	t_minirt_hit;

struct			s_minirt_world;

typedef t_err	(*t_minirt_world_hit)(
					struct s_minirt_world *self,
					t_minirt_ray ray,
					t_minirt_hit **out);

typedef struct s_minirt_world
{
	t_minirt_world_hit	hit;
}	t_minirt_world;

#endif
