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

#include "minirt/common/compat/fcntl.h"

#include <stdarg.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

# include <io.h>
# include <sys/stat.h>

#else

# include <fcntl.h>

#endif

#ifdef O_TMPFILE

static const int	g_flags = O_CREAT | O_TMPFILE;

#else

static const int	g_flags = O_CREAT;

#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

static int	translate(int flags)
{
	int	result;

	result = 0;
	if (flags & 0444)
		result |= _S_IREAD;
	if (flags & 0222)
		result |= _S_IWRITE;
	return (result);
}

int	minirt_open(const char *path, int flags, ...)
{
	va_list	ap;
	int		additional_flags;
	int		result;

	flags |= _O_BINARY;
	if (flags & g_flags)
	{
		va_start(ap, flags);
		additional_flags = translate(va_arg(ap, int));
		va_end(ap);
		if (_sopen_s(&result, path, flags, _SH_DENYWR, additional_flags))
			return (-1);
		return (result);
	}
	if (_sopen_s(&result, path, flags, _SH_DENYWR, 0))
		return (-1);
	return (result);
}

#else

int	minirt_open(const char *path, int flags, ...)
{
	va_list	ap;
	int		additional_flags;

	if (flags & g_flags)
	{
		va_start(ap, flags);
		additional_flags = va_arg(ap, int);
		va_end(ap);
		return (open(path, flags, additional_flags));
	}
	return (open(path, flags));
}

#endif
