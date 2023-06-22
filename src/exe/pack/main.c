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

#include <stdio.h>
#include <stdlib.h>

#include "minirt/common/compat/unistd.h"
#include "minirt/common/compat/fcntl.h"
#include "minirt/common/array_builder_types.h"
#include "minirt/common/libc.h"
#include "minirt/common/array_builder.h"
#include "minirt/args.h"
#include "minirt/pack.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif
#if BUFFER_SIZE < 1
# error BUFFER_SIZE must be positive number
#endif

static const t_minirt_args_options_string	g_string_options[] = {
{
	"outfile",
	'o',
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_STRING_ERROR,
},
};

static const t_minirt_args_options			g_options = {
	g_string_options,
	sizeof(g_string_options) / sizeof(g_string_options[0]),
	NULL,
	0,
	NULL,
	0,
	NULL,
	0,
	MINIRT_ARGS_OPTIONS_UNKNOWN_PARAMETER_ERROR,
	MINIRT_ARGS_OPTIONS_MALFORMED_PARAMETER_ERROR,
	false
};

static int	error(bool malloc_error)
{
	if (malloc_error)
	{
		minirt_write(STDERR_FILENO, "Error: failed to allocate memory\n", 33);
		return (EXIT_FAILURE);
	}
	minirt_write(STDOUT_FILENO,
		"Usage: pack [-o filename | --outfile filename] ...files\n", 56);
	return (EXIT_FAILURE);
}

static int	failed_to_read_file(const char *filename)
{
	minirt_write(STDERR_FILENO, "Error: failed to read file: ", 28);
	minirt_write(
		STDERR_FILENO, filename, (unsigned int)minirt_strlen(filename));
	minirt_write(STDERR_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}

static t_err	read_file_contents(
	const char *path,
	void **out,
	size_t *out_length
)
{
	unsigned char					buffer[BUFFER_SIZE];
	t_minirt_array_builder *const	builder = minirt_array_builder_new(1);
	int								fd;
	ssize_t							read_size;

	fd = minirt_open(path, O_RDONLY);
	if (!builder || fd < 0)
		return (true);
	read_size = -1;
	while (read_size)
	{
		read_size = minirt_read(fd, buffer, BUFFER_SIZE);
		if (read_size < 0)
			return (true);
		if (minirt_array_builder_append(builder, read_size, buffer))
			return (true);
	}
	minirt_close(fd);
	*out = minirt_array_builder_build(builder);
	*out_length = builder->length;
	if (!*out)
		return (true);
	minirt_array_builder_free(builder);
	return (false);
}

static int	write_file(const char *filename, t_minirt_pack *pack)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (filename)
		fd = minirt_open(filename, O_WRONLY);
	if (fd < 0)
	{
		minirt_write(STDERR_FILENO, "Error: failed to open output file: ", 35);
		minirt_write(
			STDERR_FILENO, filename, (unsigned int)minirt_strlen(filename));
		minirt_write(STDERR_FILENO, "\n", 1);
		return (EXIT_FAILURE);
	}
	if (minirt_write(fd, pack, (unsigned int)pack->size) != (ssize_t)pack->size)
	{
		minirt_write(STDERR_FILENO, "Error: failed to write\n", 23);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_minirt_args_result	a;
	size_t					i;
	t_minirt_pack_in		*input;
	t_minirt_pack			*pack;
	t_minirt_args			*params;

	if (minirt_args(argc, argv, g_options, &a))
		return (error(a.value.error.type == MINIRT_ARGS_ERROR_MALLOC_FAILURE));
	params = &a.value.ok;
	input = malloc(sizeof(t_minirt_pack_in) * a.value.ok.arg_count);
	if (!input)
		return (error(true));
	i = (size_t)-1;
	while (++i < params->arg_count)
	{
		input[i].name = params->args[i];
		if (read_file_contents(
				input[i].name, &input[i].content, &input[i].content_length))
			return (failed_to_read_file(input[i].name));
	}
	minirt_pack(input, params->arg_count, &pack);
	return (write_file(minirt_args_get_string(params, "outfile"), pack));
}
