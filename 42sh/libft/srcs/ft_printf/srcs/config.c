/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:20:07 by vjovanov          #+#    #+#             */
/*   Updated: 2018/11/20 23:45:36 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** {identifier, *accepted_flags, *accepted_conversion_flags,
**  pointer to the conversion function, value_type}
*/

const t_color			g_colors[NB_COLORS] = {
	{"eoc", "\033[39m"},
	{"black", "\033[30m"},
	{"red", "\033[31m"},
	{"green", "\033[32m"},
	{"yellow", "\033[33m"},
	{"blue", "\033[34m"},
	{"magenta", "\033[35m"},
	{"cyan", "\033[36m"},
	{"white", "\033[37m"},

	{"brightblack", "\033[90m"},
	{"brightred", "\033[91m"},
	{"brightgreen", "\033[92m"},
	{"brightyellow", "\033[93m"},
	{"brightblue", "\033[94m"},
	{"brightmagenta", "\033[95m"},
	{"brightcyan", "\033[96m"},
	{"brightwhite", "\033[97m"},

	{"bgeoc", "\033[49m"},
	{"bgblack", "\033[40m"},
	{"bgred", "\033[41m"},
	{"bggreen", "\033[42m"},
	{"bgyellow", "\033[43m"},
	{"bgblue", "\033[44m"},
	{"bgmagenta", "\033[45m"},
	{"bgcyan", "\033[46m"},
	{"bgwhite", "\033[47m"},

	{"bgbrightblack", "\033[100m"},
	{"bgbrightred", "\033[101m"},
	{"bgbrightgreen", "\033[102m"},
	{"bgbrightyellow", "\033[103m"},
	{"bgbrightblue", "\033[104m"},
	{"bgbrightmagenta", "\033[105m"},
	{"bgbrightcyan", "\033[106m"},
	{"bgbrightwhite", "\033[107m"},

	{"normal", "\033[22;23;24m"},
	{"bold", "\033[1m"},
	{"eocbold", "\033[22m"},
	{"italic", "\033[3m"},
	{"eocitalic", "\033[23m"},
	{"underline", "\033[4m"},
	{"eocunderline", "\033[24m"}
};

const char			*g_conversion_flags[NB_CONVERSION_FLAGS] = {
	"hh", "h", "ll", "l", "j", "z", "L"
};

const char			*g_flags[NB_FLAGS] = {
	" ", "#", "+", "-", "0"
};

const t_config		g_identifiers[NB_IDENTIFIERS] = {
	{'c', {"-"}, {""}, &convert_char, "char"},
	{'s', {"-"}, {""}, &convert_string, "string"},
	{'p', {"-"}, {""}, &convert_pointer, "void*"},
	{'d', {" ", "+", "-", "0"}, {"hh", "h", "ll", "l", "j", "z"},
		&convert_int, "int"},
	{'i', {" ", "+", "-", "0"}, {"hh", "h", "ll", "l", "j", "z"},
		&convert_int, "int"},
	{'o', {"#", "-", "0"}, {"hh", "h", "ll", "l", "j", "z"},
		&convert_octal, "unsigned int"},
	{'u', {"-", "0"}, {"hh", "h", "ll", "l", "j", "z"},
		&convert_unsigned, "unsigned int"},
	{'x', {"#", "-", "0"}, {"hh", "h", "ll", "l", "j", "z"},
		&convert_hexa, "unsigned int"},
	{'X', {"#", "-", "0"}, {"hh", "h", "ll", "l", "j", "z"},
		&convert_hexa_upper, "unsigned int"},
	{'f', {" ", "#", "+", "-", "0"}, {"l", "L"}, &convert_double, "double"},
	{'%', {"-", "0"}, {""}, &convert_percent, "nothing"},
	{'b', {" ", "#", "+", "-", "0"}, {"hh", "h", "ll", "l", "j", "z"},
		&convert_binary, "int"}
};

const char		**get_flags(void)
{
	return (g_flags);
}

const char		**get_conversion_flags(void)
{
	return (g_conversion_flags);
}

const t_config	*get_identifiers(void)
{
	return (g_identifiers);
}

const t_color	*get_colors(void)
{
	return (g_colors);
}
