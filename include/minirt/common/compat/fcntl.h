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

#ifndef FCNTL_H
# define FCNTL_H

# include <fcntl.h>

# if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

#  include <io.h>

#  define O_RDONLY _O_RDONLY
#  define O_WRONLY _O_WRONLY
#  define O_RDWR _O_RDWR

#  define O_EXCL _O_EXCL
#  define O_CREAT _O_CREAT
#  define O_APPEND _O_APPEND

# endif

int	minirt_open(const char *pathname, int flags, ...);

#endif
