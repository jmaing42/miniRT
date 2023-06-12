/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_float.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 2023/06/12 16:41:33 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_FLOAT_H
# define MINIRT_FLOAT_H

# include "minirt/core/minirt_float_types.h"

t_minirt_float	minirt_square(t_minirt_float f);
t_minirt_float	minirt_min(t_minirt_float a, t_minirt_float b);
t_minirt_float	minirt_max(t_minirt_float a, t_minirt_float b);

t_minirt_float	minirt_sqrt(t_minirt_float f);

#endif
