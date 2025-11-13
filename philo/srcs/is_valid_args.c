/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:21:09 by shunwata          #+#    #+#             */
/*   Updated: 2025/11/13 18:35:15 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_valid_int(const char *str)
{
	int		len;

	if (!str || *str == '\0')
		return (false);
	len = ft_strlen(str);
	if (*str == '-')
	{
		if (len > 11)
			return (false);
		if (len == 11 && ft_strncmp(str, "-214748364", 10) == 0 && \
				str[10] > '8')
			return (false);
	}
	else
	{
		if (len > 10)
			return (false);
		if (len == 10 && ft_strncmp(str, "214748364", 9) == 0 && \
				str[9] > '7')
			return (false);
	}
	return (true);
}

static bool	is_numeric(const char *str)
{
	if (!str || *str == '\0')
		return (false);
	if (*str == '-')
		str++;
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

static bool	is_positive(const char *str)
{
	if (!str || *str == '\0')
		return (false);
	while (*str != '\0')
	{
		if (*str == '-')
			return (false);
		str++;
	}
	return (true);
}

bool	is_valid_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (false);
	i = 1;
	while (i < argc)
	{
		if (!is_numeric(argv[i]) || !is_valid_int(argv[i])
			|| !is_positive(argv[i]))
			return (false);
		if (ft_atoi(argv[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}
