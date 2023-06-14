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

#ifndef BMP_H
# define BMP_H

# include <stddef.h>

# include "minirt/base_types.h"
# include "./bmp_types.h"

/**
 * @brief deserialize buffer into BMP
 *
 * @param buffer buffer
 * @param length length of buffer
 * @param out result image, or NULL if buffer isn't valid image
 * @return t_err true on malloc() failure
 * @remarks *out may be NULL even if return value indicates non-error
 */
t_err	minirt_bmp_deserialize(
			const void *buffer,
			size_t length,
			t_minirt_bmp **out);
char	*minirt_bmp_serialize(
			const t_minirt_bmp *bmp);

#endif
