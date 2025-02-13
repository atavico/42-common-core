/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:50:38 by atarsi            #+#    #+#             */
/*   Updated: 2022/10/25 20:37:52 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_finish(t_philo *ph, int tmp, int i, int check)
{
	i = 0;
	check = 0;
	while (i < ph->rules->n_ph)
	{
		pthread_mutex_lock(&ph->rules->philo_time);
		tmp = ft_time() - ph->rules->start - ph[i].last_meal;
		pthread_mutex_unlock(&ph->rules->philo_time);
		if (tmp > ph->rules->time_death)
		{
			ft_death(ph);
			usleep(2000);
			ft_philo_msg(&ph[i], ph[i].id, "died");
			return (1);
		}
		if (check_mutex(1, &ph[i]))
			check++;
		i++;
	}
	if (check == ph->rules->n_ph)
	{
		ft_death(ph);
		return (1);
	}
	return (0);
}

void	ft_monitor(void *philo)
{
	t_philo	*ph;
	int		tmp;
	int		i;
	int		check;

	tmp = 0;
	check = 0;
	i = 0;
	ph = philo;
	while (1)
	{
		if (ft_finish(ph, tmp, i, check) == 1)
			break ;
	}
}

void	*ft_meal(void *philo)
{
	t_philo	*ph;

	ph = philo;
	ft_last_meal(ph);
	if (ph->id % 2 == 0)
		my_sleep(ph->rules->time_eat);
	while (check_mutex(0, ph))
	{
		if (ft_take_forks(ph) == 1)
			break ;
		if (check_mutex(0, ph))
			ft_philo_msg(ph, ph->id, "is eating");
		ph->n_eat++;
		if (ph->n_eat == ph->rules->must_eat)
		{
			pthread_mutex_lock(&ph->rules->must_eat_mutex);
			ph->end = 1;
			pthread_mutex_unlock(&ph->rules->must_eat_mutex);
		}
		ft_last_meal(ph);
		ft_routine(ph);
	}
	return (NULL);
}

void	ft_exit(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	philo = rules->philo;
	i = 0;
	while (i < rules->n_ph)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		pthread_mutex_destroy(&rules->philo_time);
		i++;
	}
	pthread_mutex_destroy(&rules->lock);
	pthread_mutex_destroy(&rules->die_mutex);
	pthread_mutex_destroy(&rules->must_eat_mutex);
	free(philo);
	free(rules->forks);
}

void	ft_thread(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	philo = rules->philo;
	rules->start = ft_time();
	i = 0;
	while (i < rules->n_ph)
	{
		pthread_create(&philo[i].thread, NULL, ft_meal, &philo[i]);
		i++;
	}
	ft_monitor(philo);
}
