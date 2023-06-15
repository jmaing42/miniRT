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

#ifndef ARRAY_BUILDER_TYPES_H
# define ARRAY_BUILDER_TYPES_H

# include <stddef.h>

# include "minirt/base_types.h"

typedef struct s_minirt_array_builder
{
	size_t	item_size;
	size_t	capacity;
	size_t	length;
	void	*array;
}	t_minirt_array_builder;

#endif
