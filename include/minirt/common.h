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

#ifndef COMMON_H
# define COMMON_H

# include <stddef.h>
# include <stdbool.h>

# include "minirt/base_types.h"

void	minirt_memcpy(void *dest, const void *source, size_t size);

size_t	minirt_strlen(const char *str);
bool	minirt_str_eq(const char *a, const char *b);
t_err	minirt_strdup(const char *src, char **out);

#endif
