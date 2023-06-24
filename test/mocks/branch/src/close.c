/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 2023/06/25 02:06:20 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude_gnu_source.h"

#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include <dlfcn.h>

#include "branch.h"
#include "mock_branch_internal.h"

typedef int	(*t_original)(int fd);

static void	failed_to_find_original(void)
{
	fputs("Failed to find original close() function.\n", stderr);
	exit(BRANCH_ERROR);
}

int	close(int fd)
{
	const t_original	original = (t_original)dlsym(RTLD_NEXT, "close");

	if (!original)
	{
		branch_unexpected_error();
		failed_to_find_original();
	}
	if (!mock_branch_internal()->started || mock_branch_internal()->paused)
		return (original(fd));
	mock_branch_internal()->opened_fd_count--;
	return (original(fd));
}
