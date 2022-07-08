/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:46:57 by kmendes           #+#    #+#             */
/*   Updated: 2022/07/08 03:36:42 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#include "philosophers.h"


void wait_phils_thread(pthread_t ths[], int i)
{
	while (0 <= i)
	{
		pthread_join(ths[i], NULL);
		--i;	
	}
}

void	rick_watch(t_rick *rick)
{
	unsigned int	i;
	unsigned time_sleep = 500 / rick->nb_phils;

	i = 0;
	while (i < rick->nb_phils)
	{
		pthread_mutex_lock(rick->muts_lasteat + i);
		if (get_timestamp_start() - rick->lasteats[i] > rick->time_to_die)
		{
			pthread_mutex_lock(&rick->mut_sim_status);
			rick->sim_status = SIM_STOP;
			pthread_mutex_unlock(&rick->mut_sim_status);
			printf(get_phil_msg(PHIL_DIE), get_timestamp_start(), i);
			pthread_mutex_unlock(rick->muts_lasteat + i);
			break ;
		}
		pthread_mutex_unlock(rick->muts_lasteat + i);
		++i;
		if (i == rick->nb_phils)
			i = 0;
		usleep(time_sleep);
	}
}

int	start_threads(t_rick *rick)
{
	unsigned int	i;

	i = 0;
	rick->sim_status = SIM_RUN;
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

int	main(int argc, char *argv[])
{
	t_rick	rick;
	
	(void) argc;
	(void) argv;
	get_timestamp_start();
	if (create_rick(&rick))
		return (EXIT_FAILURE);
	if (init_rick(&rick))
		return clean_exit();
	if (start_threads(&rick))
	{
		clean_muts_rick(&rick, rick.nb_phils - 1);
		return (clean_exit());
	}
	rick_watch(&rick);
	wait_phils_thread(rick.ths, rick.nb_phils - 1);
	clean_muts_rick(&rick, rick.nb_phils - 1);
	clean_exit();
	return (0);
}