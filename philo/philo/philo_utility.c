/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:50:25 by atarsi            #+#    #+#             */
/*   Updated: 2022/10/25 20:28:20 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_mutex(int flag, t_philo *ph)
{
	int	tmp;

	tmp = 0;
	if (flag == 0)
	{
		pthread_mutex_lock(&ph->rules->die_mutex);
		tmp = ph->rules->die;
		pthread_mutex_unlock(&ph->rules->die_mutex);
	}
	else if (flag == 1)
	{
		pthread_mutex_lock(&ph->rules->must_eat_mutex);
		tmp = ph->end;
		pthread_mutex_unlock(&ph->rules->must_eat_mutex);
	}
	return (tmp);
}

void	ft_death(t_philo *ph)
{
	pthread_mutex_lock(&ph->rules->die_mutex);
	ph->rules->die = 0;
	pthread_mutex_unlock(&ph->rules->die_mutex);
}

void	ft_last_meal(t_philo *ph)
{
	pthread_mutex_lock(&ph->rules->philo_time);
	ph->last_meal = ft_time() - ph->rules->start;
	pthread_mutex_unlock(&ph->rules->philo_time);
}

int	ft_take_forks(t_philo *ph)
{
	pthread_mutex_lock(ph->right);
	if (check_mutex(0, ph))
		ft_philo_msg(ph, ph->id, "has taken a fork");
	if (ph->rules->n_ph == 1)
		return (1);
	pthread_mutex_lock(ph->left);
	if (check_mutex(0, ph))
		ft_philo_msg(ph, ph->id, "has taken a fork");
	return (0);
}

void	ft_routine(t_philo *ph)
{
	my_sleep(ph->rules->time_eat);
	pthread_mutex_unlock(ph->right);
	pthread_mutex_unlock(ph->left);
	if (check_mutex(0, ph))
		ft_philo_msg(ph, ph->id, "is sleeping");
	my_sleep(ph->rules->time_sleep);
	if (check_mutex(0, ph))
		ft_philo_msg(ph, ph->id, "is thinking");
}
