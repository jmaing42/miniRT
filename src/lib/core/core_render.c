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

#include "minirt/core/minirt_funcs.h"

#include <stdbool.h>

t_err	minirt_render(
	t_minirt_image *target_image,
	t_minirt_world *world,
	t_minirt_camera *camera,
	t_minirt_context *context
)
{
	(void)target_image;
	(void)world;
	(void)camera;
	(void)context;
	return (true);
}
