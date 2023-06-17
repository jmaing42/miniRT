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

#ifndef PACK_H
# define PACK_H

# include <stddef.h>
# include <stdbool.h>

# include "minirt/base_types.h"

typedef struct s_minirt_pack_node
{
	size_t	name_offset;
	size_t	content_offset;
	size_t	content_length;
}	t_minirt_pack_node;

typedef struct s_minirt_pack
{
	size_t			size;
	size_t			node_count;
	unsigned char	array[];
}	t_minirt_pack;

/**
 * @brief get individual data from pack
 *
 * @return true if data is available
 * @return false if data is not available
 */
bool	minirt_pack_get(
			t_minirt_pack *self,
			const char *name,
			void **out,
			size_t *out_length);

typedef struct s_minirt_pack_in
{
	const char	*name;
	void		*content;
	size_t		content_length;
}	t_minirt_pack_in;

t_err	minirt_pack(
			t_minirt_pack_in *files,
			size_t file_count,
			t_minirt_pack **out);

#endif
