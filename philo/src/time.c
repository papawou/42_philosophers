/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:23:06 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/18 16:36:46 by kmendes          ###   ########.fr       */
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
	static unsigned int	ts_ms_start = 0;
	struct timeval		tv_tmp;

	if (!ts_ms_start)
	{
		gettimeofday(&tv_tmp, NULL);
		ts_ms_start = tv_tmp.tv_sec * 1000 + (tv_tmp.tv_usec) / 1000;
		return (0);
	}
	gettimeofday(&tv_tmp, NULL);
	return ((tv_tmp.tv_sec * 1000 + (tv_tmp.tv_usec) / 1000) - ts_ms_start);
}
