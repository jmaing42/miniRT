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
