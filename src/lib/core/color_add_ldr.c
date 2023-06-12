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

#include "minirt/core/math.h"

#include "minirt/core/minirt_float.h"

t_minirt_color	minirt_color_add_ldr(
	t_minirt_color a,
	t_minirt_color b
)
{
	return ((t_minirt_color){
		minirt_min(a.r + b.r, 1),
		minirt_min(a.g + b.g, 1),
		minirt_min(a.b + b.b, 1),
	});
}
