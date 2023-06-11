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

#ifndef MINIRT_FUNCS_H
# define MINIRT_FUNCS_H

# include "minirt/base_tyeps.h"

# include "./minirt_types.h"

t_err	minirt_render(
			t_minirt_image *target_image,
			t_minirt_world *world,
			t_minirt_camera *camera,
			t_minirt_context *context);

#endif
