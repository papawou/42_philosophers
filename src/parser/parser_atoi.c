/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_atoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:57:09 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/15 13:54:58 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static int	ft_atoi_safe_3(int *nb, char *str, int sign)
{
	int	acc;

	if ((*nb < 0 && (INT_MIN / 10) > *nb) || (*nb > 0 && (INT_MAX / 10) < *nb))
		return (-1);
	*nb *= 10;
	acc = (*str - '0') * sign;
	if ((acc < 0 && (INT_MIN - acc) > *nb)
		|| (acc > 0 && (INT_MAX - acc) < *nb))
		return (-1);
	*nb += acc;
	return (0);
}

static char	*ft_atoi_safe_2(char *str, int *sign)
{
	*sign = 1;
	while (*str && ft_isspace(*str))
		++str;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sign = -1;
		++str;
	}
	return (str);
}

int	ft_atoi_safe(char *str, int *dst)
{
	int		nb;
	int		sign;
	char	*src_str;

	if (!str || !dst)
		return (-1);
	src_str = str;
	nb = 0;
	str = ft_atoi_safe_2(str, &sign);
	if (!ft_isdigit(*str))
		return (-1);
	while (*str && ft_isdigit(*str))
	{
		if (ft_atoi_safe_3(&nb, str, sign) == -1)
			return (-1);
		++str;
	}
	*dst = nb;
	return (str - src_str);
}
