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

#ifndef ARRAY_BUILDER_H
# define ARRAY_BUILDER_H

# include <stddef.h>

# include "minirt/base_types.h"

typedef struct s_minirt_array_builder
{
	size_t	item_size;
	size_t	capacity;
	size_t	length;
	void	*array;
}	t_minirt_array_builder;

t_minirt_array_builder	*minirt_array_builder_new(
							size_t item_size);
void					minirt_array_builder_free(
							t_minirt_array_builder *self);
t_err					minirt_array_builder_append(
							t_minirt_array_builder *self,
							size_t length,
							const void *buf);
void					*minirt_array_builder_build(
							t_minirt_array_builder *self);

#endif
