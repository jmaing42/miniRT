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

#ifndef JSON_H
# define JSON_H

# include <stddef.h>
# include <stdbool.h>

# include "minirt/base_types.h"

typedef void	*t_minirt_json;

t_err			minirt_json_parse(const char *str, t_minirt_json *out);
void			minirt_json_free(t_minirt_json value);

bool			minirt_json_is_null(t_minirt_json value);
bool			minirt_json_is_boolean(t_minirt_json value);
bool			minirt_json_is_number(t_minirt_json value);
bool			minirt_json_is_string(t_minirt_json value);
bool			minirt_json_is_list(t_minirt_json value);
bool			minirt_json_is_dict(t_minirt_json value);

size_t			minirt_json_list_length(t_minirt_json value);
bool			minirt_json_dict_has_key(t_minirt_json value, const char *key);

bool			minirt_json_get_bool(t_minirt_json value);
double			minirt_json_get_number(t_minirt_json value);
const char		*minirt_json_get_string(t_minirt_json value);
t_minirt_json	minirt_json_get_list(t_minirt_json value, size_t index);
t_minirt_json	minirt_json_get_dict(t_minirt_json value, const char *key);

#endif
