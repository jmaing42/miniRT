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

#ifndef PATH_H
# define PATH_H

# include "minirt/base_types.h"

# include <stddef.h>

typedef enum e_minirt_path_segment_type
{
	MINIRT_PATH_SEGMENT_PARENT,
	MINIRT_PATH_SEGMENT_CHILD,
}	t_minirt_path_segment_type;

typedef struct s_minirt_path_segment
{
	t_minirt_path_segment_type	type;
	char						*str;
}	t_minirt_path_segment;

typedef struct s_minirt_path
{
	t_minirt_path_segment	*segments;
	size_t					length;
}	t_minirt_path;

t_err	minirt_path_parse(
			const char *str,
			t_minirt_path **out);
t_err	minirt_path_normalize(
			t_minirt_path *in,
			t_minirt_path **out);
t_err	minirt_path_join(
			t_minirt_path *from,
			t_minirt_path *path,
			t_minirt_path **out);

#endif
