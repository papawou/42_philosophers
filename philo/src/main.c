/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:46:57 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/16 03:22:06 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#include "philosophers.h"

void	wait_phils_thread(t_rick *rick, int i)
{
	while (0 <= i)
	{
		pthread_join(rick->phs[i].th, NULL);
		--i;
	}
}

static int	check_eat_times(int min_eat_times, int eat_times, int pot)
{
	if (min_eat_times != -1 && eat_times >= min_eat_times)
		return (pot + 1);
	return (0);
}

void	rick_watch(t_rick *rick)
{
	static unsigned int	i = 0;
	static unsigned int	time_sleep;
	static int			pot = 0;

	time_sleep = 900 / rick->nb_phils;
	while (i < rick->nb_phils)
	{
		pthread_mutex_lock(&rick->phs[i].m_eat);
		if (get_timestamp_start() - rick->phs[i].last_eat >= rick->time_to_die)
		{
			pthread_mutex_lock(&rick->mut_sim_status);
			rick->sim_status = SIM_STOP;
			pthread_mutex_unlock(&rick->mut_sim_status);
			printf(get_phil_msg(PHIL_DIE), get_timestamp_start(), i);
			pthread_mutex_unlock(&rick->phs[i].m_eat);
			break ;
		}
		pthread_mutex_unlock(&rick->phs[i].m_eat);
		pot = check_eat_times(rick->min_eat_times, rick->phs[i].eat_times, pot);
		if (pot == (int) rick->nb_phils)
			break ;
		++i;
		i %= rick->nb_phils;
		usleep(time_sleep);
	}
	rick->sim_status = SIM_STOP;
}

int	start_threads(t_rick *rick)
{
	unsigned int	i;

	i = 0;
	rick->sim_status = SIM_RUN;
	while (i < rick->nb_phils)
	{
		if (pthread_create(&rick->phs[i].th, NULL,
				&philo_routine, rick->phs + i))
		{
			pthread_mutex_lock(&rick->mut_sim_status);
			rick->sim_status = SIM_STOP;
			pthread_mutex_unlock(&rick->mut_sim_status);
			wait_phils_thread(rick, i - 1);
			return (1);
		}
		++i;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_rick	rick;

	if (parse_args(argv, argc, &rick))
		return (EXIT_FAILURE);
	get_timestamp_start();
	if (create_rick(&rick))
		return (EXIT_FAILURE);
	if (init_rick(&rick))
		return (clean_exit());
	if (start_threads(&rick))
	{
		clean_muts_rick(&rick, rick.nb_phils - 1);
		return (clean_exit());
	}
	rick_watch(&rick);
	wait_phils_thread(&rick, rick.nb_phils - 1);
	clean_muts_rick(&rick, rick.nb_phils - 1);
	clean_exit();
	return (EXIT_SUCCESS);
}
