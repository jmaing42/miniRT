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

#include "minirt/scene.h"

t_err	minirt_scene_parse(
	const char *path,
	const t_minirt_scene_plugin *const	*plugins,
	const t_minirt_scene_file_loader	*loader,
	t_minirt_scene_parse_result *out
)
{
	(void)path;
	(void)plugins;
	(void)loader;
	(void)out;
	return (true);
}
