/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:23:06 by kmendes           #+#    #+#             */
/*   Updated: 2022/06/29 17:33:22 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>

static unsigned int usec_diff_timeval(struct timeval a, struct timeval b)
{
	unsigned int	delta;
	int						sec;

	sec = a.tv_sec - b.tv_sec;
	if (sec)
	{
		--sec;
		delta = 1000000 - b.tv_usec;
		delta += a.tv_usec;
		delta += 1000000 * sec; //unsafe
	}
	else
		delta = a.tv_usec - b.tv_usec;
	return (delta);
}

static unsigned int msec_diff_timeval(struct timeval a, struct timeval b)
{
	unsigned int	delta;
	int						sec;

	sec = a.tv_sec - b.tv_sec;
	if (sec)
	{
		--sec;
		delta = 1000000 - b.tv_usec;
		delta += a.tv_usec;
	}
	else
		delta = a.tv_usec - b.tv_usec;
	delta /= 1000; //usec to msec
	delta += 1000 * sec;
	return (delta);
}

unsigned int	get_time(int msec)
{
	static int		init = 1;
	static struct	timeval tv_start;
	struct				timeval tv;
	
	gettimeofday(&tv, NULL);
	if (init)
	{
		tv_start = tv;
		init = 0;
	}
	if (msec)
		return (usec_diff_timeval(tv, tv_start));
	else
		return (msec_diff_timeval(tv, tv_start));
}