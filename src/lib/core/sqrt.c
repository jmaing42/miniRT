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

#include <math.h>

#include "minirt/core/minirt_float.h"

#if MINIRT_PRECISION == 0

t_minirt_float	minirt_sqrt(t_minirt_float f)
{
	return (sqrtf(f));
}

#elif MINIRT_PRECISION == 1

t_minirt_float	minirt_sqrt(t_minirt_float f)
{
	return (sqrt(f));
}

#else

t_minirt_float	minirt_sqrt(t_minirt_float f)
{
	return (sqrtl(f));
}

#endif
