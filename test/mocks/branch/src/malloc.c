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

#include "prelude_gnu_source.h"

#include <stdlib.h>

#include <stdio.h>

#include <dlfcn.h>

#include "branch.h"
#include "mock_branch_internal.h"

typedef void	*(*t_original)(size_t size);

static void	failed_to_find_original(void)
{
	fputs("Failed to find original malloc() function.", stderr);
	exit(BRANCH_ERROR);
}

static void	failed_to_allocate_memory(void)
{
	fputs("Failed to allocate memory.", stderr);
	exit(BRANCH_ERROR);
}

static void	exit_unexpected_error(void)
{
	fputs("Unexpected error occurred.", stderr);
	exit(BRANCH_ERROR);
}

void	*malloc(size_t size)
{
	const t_original	original = (t_original)dlsym(RTLD_NEXT, "malloc");
	const int			current = branch(2);
	void				*result;

	if (!original)
	{
		branch_unexpected_error();
		failed_to_find_original();
	}
	if (!mock_branch_internal()->started || mock_branch_internal()->paused)
		return (original(size));
	if (current == -1)
		exit_unexpected_error();
	if (current == 1)
	{
		mock_branch_internal()->malloc_count++;
		result = original(size);
		if (!result)
			failed_to_allocate_memory();
		return (result);
	}
	return (NULL);
}
