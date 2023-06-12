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

#ifndef MATH_H
# define MATH_H

# include "minirt/core/math_types.h"

t_minirt_float		minirt_length(
						t_minirt_distance distance);

t_minirt_normal		minirt_normal(
						t_minirt_distance distance);
t_minirt_normal		minirt_normal_reverse(
						t_minirt_normal normal);

t_minirt_scale		minirt_scale(
						t_minirt_float x,
						t_minirt_float y,
						t_minirt_float z);
t_minirt_scale		minirt_scale_multiply(
						t_minirt_scale scale,
						t_minirt_float f);
t_minirt_scale		minirt_scale_scale(
						t_minirt_scale a,
						t_minirt_scale b);

t_minirt_position	minirt_position_add(
						t_minirt_position a,
						t_minirt_distance b);
t_minirt_position	minirt_position_subtract(
						t_minirt_position a,
						t_minirt_distance b);

t_minirt_distance	minirt_distance(
						t_minirt_position from,
						t_minirt_position to);
t_minirt_distance	minirt_distance_add(
						t_minirt_distance a,
						t_minirt_distance b);
t_minirt_distance	minirt_distance_subtract(
						t_minirt_distance a,
						t_minirt_distance b);
t_minirt_distance	minirt_distance_multiply(
						t_minirt_distance a,
						t_minirt_float b);
t_minirt_distance	minirt_distance_scale(
						t_minirt_distance a,
						t_minirt_scale b);

t_minirt_color		minirt_color_add_ldr(
						t_minirt_color a,
						t_minirt_color b);
t_minirt_color		minirt_color_add_hdr(
						t_minirt_color a,
						t_minirt_color b);
t_minirt_color		minirt_color_multiply(
						t_minirt_color a,
						t_minirt_color b);
t_minirt_color		minirt_color_lerp(
						t_minirt_color a,
						t_minirt_color b,
						t_minirt_float ratio);

#endif
