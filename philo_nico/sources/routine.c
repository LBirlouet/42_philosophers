/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndessard <ndessard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:11:53 by ndessard          #+#    #+#             */
/*   Updated: 2024/04/19 15:39:15 by ndessard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*only_one_2(void *phil)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)phil;
	data = philo->data;
	pthread_mutex_lock(&data->fork[0]);
	print(1, data, "has taken a fork");
	ft_sleep(data, data->t_to_die);
	print(1, data, "is dead");
	pthread_mutex_unlock(&data->fork[0]);
	destroy_all(data);
	return (NULL);
}

int	only_one(t_data *data)
{
	if (pthread_create(&data->philo[0].thread, NULL, only_one_2,
			(void *)&data->philo[0]))
		return (destroy_all(data), 1);
	ft_sleep(data, data->t_to_die);
	pthread_join(data->philo[0].thread, NULL);
	return (0);
}

void	eat(t_philo *philo, int id)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->fork[philo->left_fork]);
	print(philo->id, data, "has taken a fork");
	pthread_mutex_lock(&data->fork[philo->right_fork]);
	print(philo->id, data, "has taken a fork");
	print(philo->id, data, "is eating");
	data->philo[id].nbr_eat++;
	ft_sleep(data, data->t_to_eat);
	pthread_mutex_unlock(&(data->fork[philo->left_fork]));
	pthread_mutex_unlock(&(data->fork[philo->right_fork]));
}

void	*routine(void *phil)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)phil;
	data = philo->data;
	philo->last_eat = data->start_time;
	if (philo->id % 2 == 0)
		ft_sleep(data, 10);
	while (data->dead != 1 || data->eat_en >= data->nb_philo)
	{
		eat(philo, philo->id);
		print(philo->id, data, "is sleeping");
		ft_sleep(data, data->t_to_sleep);
		print(philo->id, data, "is thinking");
		if (data->eat_en >= data->nb_philo)
			return (NULL);
	}
	return (NULL);
}
