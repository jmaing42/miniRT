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

t_minirt_float	minirt_length(
	t_minirt_distance distance
)
{
	const t_minirt_float	x = minirt_square(distance.x);
	const t_minirt_float	y = minirt_square(distance.y);
	const t_minirt_float	z = minirt_square(distance.z);

	return (minirt_sqrt(x + y + z));
}
