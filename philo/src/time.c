/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:23:06 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/16 02:39:07 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>

unsigned int	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + (tv.tv_usec / 1000));
}

unsigned int	get_timestamp_start(void)
{
	static unsigned int	time_start = 0;
	unsigned int		ts;

	if (time_start == 0)
	{
		time_start = get_timestamp();
		return (0);
	}
	ts = get_timestamp();
	return (ts - time_start);
}
