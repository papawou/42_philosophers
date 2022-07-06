/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:46:57 by kmendes           #+#    #+#             */
/*   Updated: 2022/07/06 04:09:43 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#include "philosophers.h"

void	rick_watch(t_rick *rick)
	struct timeval	sv;
	int							d;

	while (i < PHILO_NUM)
	{
		gettimeofday(&sv, NULL);
		d = msec_diff_timeval(sv, *last_eat);
		if (d < TIME_TO_DIE)
			usleep(TIME_TO_DIE - d);
		else
		{
			pthread_mutex_lock(&deathnote);
			death_flag = 1;
			pthread_mutex_unlock(&deathnote);
			philo_die(ph);
		}
	}
}

int	start_threads(t_rick *rick)
{
	int	i;

	i = 0;
	while (i < rick->nb_phils)
	{
		if (pthread_create(rick->ths + i, NULL, &philo_routine, rick->phs + i))
		{
			pthread_mutex_lock(&rick->mut_sim_status);
			rick->sim_status = SIM_STOP;
			pthread_mutex_unlock(&rick->mut_sim_status);
			wait_phils_thread(rick->ths, i - 1);
			return (1);
		}
		++i;
	}
	return (0);
}

void wait_phils_thread(pthread_t ths[], int i)
{
	while (0 <= i)
	{
		pthread_join(ths[i], NULL);
		--i;	
	}
}

int	main(int argc, char *argv[])
{
	int			nb_phils;
	t_rick	rick;
	int			i;
	
	if (create_rick(&rick, nb_phils))
		return (EXIT_FAILURE);
	if (init_rick(&rick))
		return clean_exit();
	if (start_threads(&rick))
	{
		clean_muts_rick(&rick, rick.nb_phils - 1);
		return (clean_exit());
	}
	rick_watch(rick);
	wait_phils_thread(rick.ths, rick.nb_phils - 1);
	clean_muts_rick(&rick, rick.nb_phils - 1);
	clean_exit();
	return (0);
}