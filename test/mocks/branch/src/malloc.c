/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 2023/06/25 02:06:43 by Juyeong Maing    ###   ########.fr       */
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
	branch_unexpected_error();
	fputs("Failed to find original malloc() function.\n", stderr);
	exit(BRANCH_ERROR);
}

static void	failed_to_allocate_memory(void)
{
	branch_unexpected_error();
	fputs("Failed to allocate memory.\n", stderr);
	exit(BRANCH_ERROR);
}

static void	exit_unexpected_error(void)
{
	branch_unexpected_error();
	fputs("Unexpected error occurred.\n", stderr);
	exit(BRANCH_ERROR);
}

void	*malloc(size_t size)
{
	const t_original	original = (t_original)dlsym(RTLD_NEXT, "malloc");
	int					current;
	void				*result;

	if (!original)
		failed_to_find_original();
	if (!mock_branch_internal()->started || mock_branch_internal()->paused)
		return (original(size));
	current = branch(2);
	if (current == -1)
		exit_unexpected_error();
	if (current == 1)
		return (NULL);
	mock_branch_internal()->malloc_count++;
	result = original(size);
	if (!result)
		failed_to_allocate_memory();
	return (result);
}
