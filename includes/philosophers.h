/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 04:07:19 by kmendes           #+#    #+#             */
/*   Updated: 2022/07/06 04:08:42 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define PHILO_NUM 2

# define TIME_TO_DIE 1000
# define TIME_TO_EAT 10
# define TIME_TO_SLEEP 10
# define NB_TIMES_EAT	1

#include <pthread.h>

enum e_sim_status
{
	SIM_RUN,
	SIM_STOP,
	SIM_WAIT
};

typedef struct	s_rick
{
	unsigned int 				nb_phils;
	unsigned int 				time_to_die;
	unsigned int 				time_to_sleep;
	unsigned int 				time_to_eat;
	unsigned int 				nb_times_eat;

	pthread_t						*ths;
	pthread_mutex_t			*forks;

	pthread_mutex_t			*muts_lasteat;
	unsigned int				*lasteats;

	pthread_mutex_t			mut_sim_status;
	enum e_sim_status		sim_status;

	t_philo							*phs;
}	t_rick;

enum e_phil_msg {
	PHIL_FORK_TAKEN,
	PHIL_EAT,
	PHIL_SLEEP,
	PHIL_THINK,
	PHIL_DIE
};

typedef struct s_philo
{
	int									id;
	unsigned int				*last_eat;
	pthread_mutex_t			*m_eat;
	pthread_mutex_t			*forks[2];
	t_rick							*rick;
}	t_philo;

//time.c
unsigned int	msec_diff_timeval(struct timeval a, struct timeval b);
unsigned int	usec_diff_timeval(struct timeval a, struct timeval b);
unsigned int	get_time(int msec);
unsigned int	get_timestamp(void);

//msg.c
int	print_msg(t_rick *rick, int id, unsigned int ts, enum e_phil_msg msg);


//philo
t_philo	create_philo(t_rick *rick, unsigned int idx);

//clean_exit
int	clean_exit(void);

//rick
int	clean_rick(void *ptr_rick);
int	create_rick(t_rick *rick, unsigned int nb_phils);
int	init_rick(t_rick *rick);
int clean_muts_rick(t_rick *rick, int i);
#endif