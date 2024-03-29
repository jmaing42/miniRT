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

#ifdef MOCK_BRANCH_NO_WRAP
# include "prelude_gnu_source.h"
#endif

#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef MOCK_BRANCH_NO_WRAP
# include <dlfcn.h>
#endif
#include <sys/stat.h>
#include <errno.h>

#include "branch.h"
#include "mock_branch_internal.h"

typedef int			(*t_original)(const char *path, int flags, ...);

static void	failed(const char *message)
{
	branch_unexpected_error();
	fputs(message, stderr);
	exit(BRANCH_ERROR);
}

static int	real_mock(
	const char *path,
	int flags,
	unsigned int additional_flags,
	t_original original
)
{
	const int	current = branch(2);
	int			result;

	if (current == 1)
		return (-1);
	mock_branch_internal()->opened_fd_count++;
	if (flags & O_CREAT)
	{
		result = original(path, flags, additional_flags);
		if (result == -1)
			failed("Failed to open()\n");
		return (result);
	}
	else
	{
		result = original(path, flags);
		if (result == -1)
			failed("Failed to open()\n");
		return (result);
	}
}

static int	mock(
	const char *path,
	int flags,
	unsigned int additional_flags,
	t_original original
)
{
	struct stat	file_stat;

	if (flags & ~(O_CREAT | O_EXCL | O_RDONLY | O_WRONLY | O_RDWR))
		failed("Failed to validate open() flags (unknown flags given)\n");
	if (additional_flags & ~0777)
		failed("Failed to validate open() flags"
			" (unknown additional flags given)\n");
	if (flags & O_EXCL && !(flags & O_CREAT))
		failed("Failed to validate open() flags"
			" (O_EXCL given without O_CREAT)\n");
	if (stat(path, &file_stat) == -1)
	{
		if (errno == ENOENT)
		{
			if (!(flags | O_CREAT))
				return (-1);
			return (real_mock(path, flags, additional_flags, original));
		}
		failed("Failed to call stat()\n");
	}
	if ((flags & (O_CREAT | O_EXCL)) == (O_CREAT | O_EXCL))
		return (-1);
	if ((file_stat.st_mode & additional_flags) != additional_flags)
		return (-1);
	return (real_mock(path, flags, additional_flags, original));
}

#ifdef MOCK_BRANCH_NO_WRAP

int	open(const char *path, int flags, ...)
{
	const t_original	original = (t_original)dlsym(RTLD_NEXT, "open");
	va_list				ap;
	unsigned int		additional_flags;

	if (!original)
		failed("Failed to find original open() function.\n");
	additional_flags = 0;
	if (flags & O_CREAT)
	{
		va_start(ap, flags);
		additional_flags = va_arg(ap, int);
		va_end(ap);
	}
	if (!mock_branch_internal()->started || mock_branch_internal()->paused)
	{
		if (flags & O_CREAT)
			return (original(path, flags, additional_flags));
		return (original(path, flags));
	}
	return (mock(path, flags, additional_flags, original));
}

#else

extern int	__real_open(const char *path, int flags, ...);

int	__wrap_open(const char *path, int flags, ...)
{
	const t_original	original = __real_open;
	va_list				ap;
	unsigned int		additional_flags;

	if (!original)
		failed("Failed to find original open() function.\n");
	additional_flags = 0;
	if (flags & O_CREAT)
	{
		va_start(ap, flags);
		additional_flags = va_arg(ap, int);
		va_end(ap);
	}
	if (!mock_branch_internal()->started || mock_branch_internal()->paused)
	{
		if (flags & O_CREAT)
			return (original(path, flags, additional_flags));
		return (original(path, flags));
	}
	return (mock(path, flags, additional_flags, original));
}

#endif
