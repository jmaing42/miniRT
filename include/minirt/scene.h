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

#ifndef SCENE_H
# define SCENE_H

# include <stdbool.h>

# include "minirt/core/minirt_types.h"
# include "minirt/json.h"

struct			s_minirt_scene_file_loader;

typedef t_err	(*t_minirt_scene_file_loader_read_file_contents)(
					struct s_minirt_scene_file_loader *self,
					const char *path,
					char **out);

typedef struct s_minirt_scene_file_loader
{
	t_minirt_scene_file_loader_read_file_contents	read_file_contents;
}	t_minirt_scene_file_loader;

typedef struct s_minirt_scene_parse_string
{
	union u_minirt_scene_parse_string_content
	{
		const char	*is_static;
		char		*is_dynamic;
	}		content;
	bool	is_dynamic;
}	t_minirt_scene_parse_string;

struct			s_minirt_scene_plugin;

typedef void	(*t_minirt_scene_plugin_validate)(
					struct s_minirt_scene_plugin *self,
					t_minirt_json value,
					t_minirt_scene_parse_string **out_error_messages);
typedef t_err	(*t_minirt_scene_plugin_apply)(
					struct s_minirt_scene_plugin *self,
					t_minirt_json value,
					void *out);

typedef struct s_minirt_scene_plugin
{
	const char						*name;
	t_minirt_scene_plugin_validate	validate;
	t_minirt_scene_plugin_apply		apply;
}	t_minirt_scene_plugin;

typedef union u_minirt_scene_parse_result
{
	t_minirt_world				*success;
	t_minirt_scene_parse_string	*error_messages;
}	t_minirt_scene_parse_result;

t_err	minirt_scene_parse(
			const char *path,
			const t_minirt_scene_plugin *const *plugins,
			const t_minirt_scene_file_loader *loader,
			t_minirt_scene_parse_result *out);

#endif
