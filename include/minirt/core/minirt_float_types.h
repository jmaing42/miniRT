/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_float_types.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 2023/06/12 16:20:29 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_FLOAT_TYPES_H
# define MINIRT_FLOAT_TYPES_H

# if defined(MINIRT_PRECISION) && MINIRT_PRECISION == 0

typedef float		t_minirt_float;

# elif defined(MINIRT_PRECISION) && MINIRT_PRECISION == 2

typedef long double	t_minirt_float;

# else

#  ifdef MINIRT_PRECISION
#   undef MINIRT_PRECISION
#  endif
#  define MINIRT_PRECISION 1

typedef double		t_minirt_float;

# endif

#endif
