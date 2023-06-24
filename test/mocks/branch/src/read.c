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

#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

#include <dlfcn.h>

#include "branch.h"
#include "mock_branch_internal.h"

typedef ssize_t	(*t_original)(int fd, void *buf, size_t count);

static void	failed_to_find_original(void)
{
	branch_unexpected_error();
	fputs("Failed to find original malloc() function.", stderr);
	exit(BRANCH_ERROR);
}

static void	failed_to_read(void)
{
	branch_unexpected_error();
	fputs("Failed to read.", stderr);
	exit(BRANCH_ERROR);
}

static void	exit_unexpected_error(void)
{
	branch_unexpected_error();
	fputs("Unexpected error occurred.", stderr);
	exit(BRANCH_ERROR);
}

ssize_t	read(int fd, void *buf, size_t count)
{
	const t_original	original = (t_original)dlsym(RTLD_NEXT, "read");
	const bool			may_partial
		= (count > 1) && mock_branch_internal()->may_partial;
	int					current;
	ssize_t				result;
	size_t				real_count;

	if (!original)
		failed_to_find_original();
	if (!mock_branch_internal()->started || mock_branch_internal()->paused)
		return (original(fd, buf, count));
	current = branch(2 + !!may_partial);
	if (current == -1)
		exit_unexpected_error();
	if (current == 1 + !!may_partial)
		return (-1);
	real_count = count;
	if (current == 1)
		real_count = count - 1;
	result = original(fd, buf, real_count);
	if (result == -1)
		failed_to_read();
	return (result);
}
