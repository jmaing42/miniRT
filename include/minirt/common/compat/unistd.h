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

#ifndef UNISTD_H
# define UNISTD_H

# include <limits.h>
# include <stdint.h>

// ssize_t

# if SIZE_MAX == UINT16_MAX

typedef int16_t	t_ssize_t;

# elif SIZE_MAX == UINT32_MAX

typedef int32_t	t_ssize_t;

# elif defined(UINT64_MAX) && SIZE_MAX == UINT64_MAX

typedef int64_t	t_ssize_t;

# else
#  error "Failed to define ssize_t"
# endif

// other constants

# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define STDERR_FILENO 2

t_ssize_t	minirt_read(int fd, void *buf, unsigned int count);
t_ssize_t	minirt_write(int fd, const void *buf, unsigned int count);
int			minirt_close(int fd);

#endif
