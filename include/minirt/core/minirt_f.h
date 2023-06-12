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

#ifndef MINIRT_F_H
# define MINIRT_F_H

# if defined(MINIRT_PRECISION) && MINIRT_PRECISION == 0

typedef float		t_minirt_f;

# elif defined(MINIRT_PRECISION) && MINIRT_PRECISION == 2

typedef long double	t_minirt_f;

# else

typedef double		t_minirt_f;

# endif

typedef struct s_minirt_f3 {
	t_minirt_f	x;
	t_minirt_f	y;
	t_minirt_f	z;
}	t_minirt_f3;

typedef struct s_minirt_f4 {
	t_minirt_f	x;
	t_minirt_f	y;
	t_minirt_f	z;
	t_minirt_f	w;
}	t_minirt_f4;

typedef struct s_minirt_f4x4 {
	t_minirt_f3	x;
	t_minirt_f3	y;
	t_minirt_f3	z;
	t_minirt_f3	w;
}	t_minirt_f4x4;

#endif
