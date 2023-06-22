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

#include "minirt/common/compat/unistd.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

# include <io.h>

ssize_t	minirt_write(int fd, const void *buf, unsigned int count)
{
	return (_write(fd, buf, count));
}

#else

# include <unistd.h>

ssize_t	minirt_write(int fd, const void *buf, unsigned int count)
{
	return (write(fd, buf, count));
}

#endif
