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

t_minirt_color	minirt_color_lerp(
	t_minirt_color a,
	t_minirt_color b,
	t_minirt_float ratio
)
{
	const t_minirt_float	diff_r = b.r - a.r;
	const t_minirt_float	diff_g = b.g - a.g;
	const t_minirt_float	diff_b = b.b - a.b;

	return ((t_minirt_color){
		a.r + diff_r * ratio,
		a.g + diff_g * ratio,
		a.b + diff_b * ratio,
	});
}
