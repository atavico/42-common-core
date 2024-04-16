/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:43:48 by atarsi            #+#    #+#             */
/*   Updated: 2022/07/13 16:43:48 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	my_sleep(long long time, t_rules *rules)
{
	long long	tmp;

	tmp = ft_time();
	while (time > ft_time() - tmp)
	{
		usleep(50);
	}
	if (rules->start == 1)
		return ;
}

void	ft_philo_msg(t_rules *rules, int id, char *str)
{
	sem_wait(rules->msg);
	printf("%lld ", ft_time() - rules->start);
	printf("%d %s\n", id, str);
	sem_post(rules->msg);
}
