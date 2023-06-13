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

#ifndef JSON_INTERNAL_H
# define JSON_INTERNAL_H

# include "minirt/json.h"

typedef struct s_minirt_json_stringbuilder_node
{
	struct s_minirt_json_stringbuilder_node	*next;
	size_t									capacity;
	size_t									length;
	char									str[];
}	t_minirt_json_stringbuilder_node;

typedef struct s_minirt_json_stringbuilder
{
	size_t								length;
	t_minirt_json_stringbuilder_node	*head;
	t_minirt_json_stringbuilder_node	*tail;
	size_t								buffer_size;
}	t_minirt_json_stringbuilder;

t_minirt_json_stringbuilder	*minirt_json_stringbuilder_new(
								size_t buffer_size);
void						minirt_json_stringbuilder_free(
								t_minirt_json_stringbuilder *self);
t_err						minirt_json_stringbuilder_append(
								t_minirt_json_stringbuilder *self,
								size_t length,
								const char *buf);
t_err						minirt_json_stringbuilder_append_char(
								t_minirt_json_stringbuilder *self,
								char c);
char						*minirt_json_stringbuilder_to_string(
								t_minirt_json_stringbuilder *self,
								size_t offset);

typedef enum e_minirt_json_value_type
{
	MINIRT_JSON_VALUE_TYPE_ERROR,
	MINIRT_JSON_VALUE_TYPE_NULL,
	MINIRT_JSON_VALUE_TYPE_BOOLEAN,
	MINIRT_JSON_VALUE_TYPE_NUMBER,
	MINIRT_JSON_VALUE_TYPE_STRING,
	MINIRT_JSON_VALUE_TYPE_LIST,
	MINIRT_JSON_VALUE_TYPE_DICT,
}	t_minirt_json_value_type;

typedef struct s_minirt_json_list_node
{
	struct s_minirt_json_list_node		*next;
	union u_minirt_json_value_internal	*value;
}	t_minirt_json_list_node;

typedef struct s_minirt_json_list
{
	t_minirt_json_list_node	*head;
	t_minirt_json_list_node	*tail;
}	t_minirt_json_list;

typedef struct s_minirt_json_dict_node
{
	struct s_minirt_json_dict_node		*next;
	char								*key;
	union u_minirt_json_value_internal	*value;
}	t_minirt_json_dict_node;

typedef struct s_minirt_json_dict
{
	t_minirt_json_dict_node	*head;
	t_minirt_json_dict_node	*tail;
}	t_minirt_json_dict;

typedef struct s_minirt_json_value_boolean
{
	t_minirt_json_value_type	type;
	bool						value;
}	t_minirt_json_value_boolean;

typedef struct s_minirt_json_value_number
{
	t_minirt_json_value_type	type;
	double						value;
}	t_minirt_json_value_number;

typedef struct s_minirt_json_value_string
{
	t_minirt_json_value_type	type;
	char						*value;
}	t_minirt_json_value_string;

typedef struct s_minirt_json_value_list
{
	t_minirt_json_value_type	type;
	t_minirt_json_list			value;
}	t_minirt_json_value_list;

typedef struct s_minirt_json_value_dict
{
	t_minirt_json_value_type	type;
	t_minirt_json_dict			value;
}	t_minirt_json_value_dict;

typedef union u_minirt_json_value_internal
{
	t_minirt_json_value_type	type;
	t_minirt_json_value_boolean	boolean;
	t_minirt_json_value_number	number;
	t_minirt_json_value_string	string;
	t_minirt_json_value_list	list;
	t_minirt_json_value_dict	dict;
}	t_minirt_json_value_internal;

typedef enum e_minirt_json_token_type
{
	MINIRT_JSON_TOKEN_TYPE_EOF,
	MINIRT_JSON_TOKEN_TYPE_NULL,
	MINIRT_JSON_TOKEN_TYPE_COMMA,
	MINIRT_JSON_TOKEN_TYPE_COLON,
	MINIRT_JSON_TOKEN_TYPE_TRUE,
	MINIRT_JSON_TOKEN_TYPE_FALSE,
	MINIRT_JSON_TOKEN_TYPE_BRACE_OPEN,
	MINIRT_JSON_TOKEN_TYPE_BRACE_CLOSE,
	MINIRT_JSON_TOKEN_TYPE_BRACKET_OPEN,
	MINIRT_JSON_TOKEN_TYPE_BRACKET_CLOSE,
	MINIRT_JSON_TOKEN_TYPE_NUMBER,
	MINIRT_JSON_TOKEN_TYPE_STRING,
}	t_minirt_json_token_type;

typedef struct s_minirt_json_token_number
{
	t_minirt_json_token_type	type;
	double						value;
}	t_minirt_json_token_number;

typedef struct s_minirt_json_token_string
{
	t_minirt_json_token_type	type;
	char						*value;
}	t_minirt_json_token_string;

typedef union u_minirt_json_token
{
	t_minirt_json_token_type	*type;
	t_minirt_json_token_number	*number;
	t_minirt_json_token_string	*string;
}	t_minirt_json_token;

typedef struct s_minirt_json_token_list_node
{
	struct s_minirt_json_token_list_node	*next;
	void									(*free_value)(t_minirt_json_token);
	t_minirt_json_token						value;
}	t_minirt_json_token_list_node;

typedef struct s_minirt_json_token_list
{
	t_minirt_json_token_list_node	*head;
	t_minirt_json_token_list_node	*tail;
}	t_minirt_json_token_list;

# define MINIRT_JSON_TOKENIZER_STATE_ERROR -1
# define MINIRT_JSON_TOKENIZER_STATE_DEFAULT 0
# define MINIRT_JSON_TOKENIZER_STATE_KEYWORD_T 1
# define MINIRT_JSON_TOKENIZER_STATE_KEYWORD_TR 2
# define MINIRT_JSON_TOKENIZER_STATE_KEYWORD_TRU 3
# define MINIRT_JSON_TOKENIZER_STATE_KEYWORD_F 4
# define MINIRT_JSON_TOKENIZER_STATE_KEYWORD_FA 5
# define MINIRT_JSON_TOKENIZER_STATE_KEYWORD_FAL 6
# define MINIRT_JSON_TOKENIZER_STATE_KEYWORD_FALS 7
# define MINIRT_JSON_TOKENIZER_STATE_KEYWORD_N 8
# define MINIRT_JSON_TOKENIZER_STATE_KEYWORD_NU 9
# define MINIRT_JSON_TOKENIZER_STATE_KEYWORD_NUL 10
# define MINIRT_JSON_TOKENIZER_STATE_STRING_ANY 11
# define MINIRT_JSON_TOKENIZER_STATE_STRING_BACKSLASH 12
# define MINIRT_JSON_TOKENIZER_STATE_STRING_X0 13
# define MINIRT_JSON_TOKENIZER_STATE_STRING_X1 14
# define MINIRT_JSON_TOKENIZER_STATE_NUMBER_SIGN 15
# define MINIRT_JSON_TOKENIZER_STATE_NUMBER_ZERO 16
# define MINIRT_JSON_TOKENIZER_STATE_NUMBER_INTEGER 17
# define MINIRT_JSON_TOKENIZER_STATE_NUMBER_DOT 18
# define MINIRT_JSON_TOKENIZER_STATE_NUMBER_FRACTION 19
# define MINIRT_JSON_TOKENIZER_STATE_NUMBER_E 20
# define MINIRT_JSON_TOKENIZER_STATE_NUMBER_E_SIGN 21
# define MINIRT_JSON_TOKENIZER_STATE_NUMBER_E_DIGIT 22

typedef struct s_minirt_json_tokenizer_state
{
	int		state;
	void	*data;
}	t_minirt_json_tokenizer_state;

typedef t_err	(*t_minirt_json_tokenizer_state_function)(
					char c,
					t_minirt_json_token_list *list,
					void *data,
					t_minirt_json_tokenizer_state *out_next_state);

t_err						minirt_json_tokenize(
								const char *str,
								t_minirt_json_token_list *out);
void						minirt_json_tokenize_free(
								t_minirt_json_token_list list);
t_err						minirt_json_tokenize_default(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_keyword_t(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_keyword_tr(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_keyword_tru(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_keyword_f(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_keyword_fa(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_keyword_fal(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_keyword_fals(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_keyword_n(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_keyword_nu(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_keyword_nul(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_string_any(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_string_backslash(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_string_x0(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_string_x1(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_number_sign(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_number_zero(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_number_integer(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_number_dot(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_number_fraction(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_number_e(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_number_e_sign(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);
t_err						minirt_json_tokenize_number_e_digit(
								char c,
								t_minirt_json_token_list *list,
								void *data,
								t_minirt_json_tokenizer_state *out_next_state);

typedef struct s_minirt_json_tokenizer_state_string
{
	t_minirt_json_stringbuilder	*stringbuilder;
	unsigned char				x;
}	t_minirt_json_tokenizer_state_string;

typedef struct s_minirt_json_tokenizer_state_number
{
	double	value;
	double	current_digit;
	int		sign;
	int		exp;
	int		exp_sign;
}	t_minirt_json_tokenizer_state_number;

t_err						minirt_json_tokenize_add_simple_token(
								t_minirt_json_token_list *list,
								t_minirt_json_token_type type);
t_err						minirt_json_tokenize_add_string_token(
								t_minirt_json_token_list *list,
								t_minirt_json_tokenizer_state_string *state);
t_err						minirt_json_tokenize_add_number_token(
								t_minirt_json_token_list *list,
								t_minirt_json_tokenizer_state_number *state);
t_err						minirt_json_tokenizer_state_string(
								void **to);
t_err						minirt_json_tokenizer_state_number(
								void **to,
								char c);

t_err						minirt_json_parse_value(
								t_minirt_json_token_list_node **head,
								t_minirt_json_value_internal *out);
t_err						minirt_json_parse_list(
								t_minirt_json_token_list_node **head,
								t_minirt_json_value_list *out);
t_err						minirt_json_parse_dict(
								t_minirt_json_token_list_node **head,
								t_minirt_json_value_dict *out);

bool						minirt_json_parse_next_is_value(
								t_minirt_json_token_type token_type);
bool						minirt_json_parse_next_is_list(
								t_minirt_json_token_type token_type);
bool						minirt_json_parse_next_is_dict(
								t_minirt_json_token_type token_type);

void						minirt_json_value_internal_free(
								t_minirt_json_value_internal *value);
void						minirt_json_value_string_free(
								t_minirt_json_value_string *value);
void						minirt_json_value_list_free(
								t_minirt_json_value_list *value);
void						minirt_json_value_dict_free(
								t_minirt_json_value_dict *value);

t_err						minirt_json_parse_internal(
								const char *str,
								t_minirt_json_value_internal *out);

#endif
