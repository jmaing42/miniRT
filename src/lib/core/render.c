/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 2023/06/12 14:42:27 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/core/minirt.h"

#include <stdbool.h>

t_err	minirt_render(
	t_minirt_image *target_image,
	const t_minirt_world *world,
	const t_minirt_camera *camera,
	t_minirt_renderer *renderer
)
{
	(void)target_image;
	(void)world;
	(void)camera;
	(void)renderer;
	return (true);
}
