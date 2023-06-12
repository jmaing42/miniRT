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

# include "minirt/base_types.h"
# include "minirt/core/minirt_f.h"

typedef struct s_minirt_image
{
	size_t		width;
	size_t		height;
	t_minirt_f3	pixels[];
}	t_minirt_image;

typedef struct s_minirt_normal
{
	t_minirt_f3	normal;
}	t_minirt_normal;

typedef struct s_minirt_position
{
	t_minirt_f3	position;
}	t_minirt_position;

typedef struct s_minirt_color
{
	t_minirt_f3	color;
}	t_minirt_color;

// -----------------------------------------------------------------------------
// material
// -----------------------------------------------------------------------------

struct			s_minirt_material;

typedef t_err	(*t_minirt_material_free)(
					struct s_minirt_material *self);

typedef t_err	(*t_minirt_material_get_color)(
					struct s_minirt_material *self,
					t_minirt_color *out);

typedef t_err	(*t_minirt_material_get_f)(
					struct s_minirt_material *self,
					t_minirt_f *out);

typedef struct s_minirt_material
{
	t_minirt_material_free		free;
	t_minirt_material_get_color	ambient;
	t_minirt_material_get_color	diffuse;
	t_minirt_material_get_color	specular;
	t_minirt_material_get_f		specular_lobe;
}	t_minirt_material;

// -----------------------------------------------------------------------------
// hit
// -----------------------------------------------------------------------------

struct			s_minirt_hit;

typedef t_err	(*t_minirt_hit_free)(
					struct s_minirt_hit *self);

typedef t_err	(*t_minirt_hit_get_material)(
					struct s_minirt_hit *self,
					t_minirt_material **out);

typedef t_err	(*t_minirt_hit_get_normal)(
					struct s_minirt_hit *self,
					t_minirt_normal *out);

typedef t_err	(*t_minirt_hit_get_position)(
					struct s_minirt_hit *self,
					t_minirt_position *out);

typedef struct s_minirt_hit
{
	t_minirt_hit_free			free;
	t_minirt_hit_get_material	get_material;
	t_minirt_hit_get_normal		get_real_normal;
	t_minirt_hit_get_normal		get_light_normal;
	t_minirt_hit_get_position	get_position;
}	t_minirt_hit;

// -----------------------------------------------------------------------------
// world
// -----------------------------------------------------------------------------

struct			s_minirt_world;

typedef t_err	(*t_minirt_world_free)(
					struct s_minirt_world *self);

typedef t_err	(*t_minirt_world_hit)(
					struct s_minirt_world *self,
					t_minirt_normal ray,
					t_minirt_hit **out);

typedef struct s_minirt_world
{
	t_minirt_world_free	free;
	t_minirt_world_hit	hit;
}	t_minirt_world;

// -----------------------------------------------------------------------------
// camera
// -----------------------------------------------------------------------------

struct			s_minirt_camera;

typedef t_err	(*t_minirt_camera_free)(
					struct s_minirt_camera *self);

typedef t_err	(*t_minirt_camera_ray)(
					struct s_minirt_camera *self,
					t_minirt_f x,
					t_minirt_f );

typedef struct s_minirt_camera
{
	t_minirt_camera_free	free;
	t_minirt_camera_ray		ray;
}	t_minirt_camera;

// -----------------------------------------------------------------------------
// renderer
// -----------------------------------------------------------------------------

struct			s_minirt_renderer;

typedef t_err	(*t_minirt_renderer_free)(
					struct s_minirt_renderer *self);

typedef t_err	(*t_minirt_renderer_render_pixel)(
					struct s_minirt_renderer *self,
					const t_minirt_world *world,
					t_minirt_normal ray);

typedef struct s_minirt_renderer
{
	t_minirt_renderer_free			free;
	t_minirt_renderer_render_pixel	render_pixel;
}	t_minirt_renderer;

#endif
