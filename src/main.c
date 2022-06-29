/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:46:57 by kmendes           #+#    #+#             */
/*   Updated: 2022/06/29 17:36:07 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "philosophers.h"

#define PTHREAD_NUM 2

static pthread_t th[PTHREAD_NUM]; //philo
//static	pthread_mutex_t muts[PTHREAD_NUM]; //fork

void	*routine(void *args)
{
	int id;

	id = *(int *)args;
	usleep(1000);
	printf("%u - Thread %d\n", get_time(1), id);
	return args;
}

int	main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	
	get_time(0);
	int	i = 0;
	while (i < PTHREAD_NUM)
	{
		int *th_args;

		th_args = malloc(sizeof(int));
		*th_args = i;
		pthread_create(th + i, NULL, &routine, th_args);
		++i;
	}

	i = 0;
	while (i < PTHREAD_NUM)
	{
		pthread_join(th[i], NULL);
		++i;
	}	
	return (0);
}