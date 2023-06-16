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

#ifndef LIBC_H
# define LIBC_H

# include <stddef.h>
# include <stdbool.h>

# include "minirt/base_types.h"

void	minirt_memcpy(void *dest, const void *source, size_t size);

size_t	minirt_strlen(const char *str);
bool	minirt_str_eq(const char *a, const char *b);
t_err	minirt_strdup(const char *src, char **out);
t_err	minirt_strndup(const char *src, size_t length, char **out);
bool	minirt_strchr(const char *str, char c, size_t *out);

#endif
