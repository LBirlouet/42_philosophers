/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:37:16 by lbirloue          #+#    #+#             */
/*   Updated: 2024/05/06 10:19:22 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eat(t_data *data, t_philos *philo)
{
	if (data->death == 0 && data->eat_max != data->nb_philo)
	{
		pthread_mutex_lock(&data->fork[philo->left_f]);
		print(data, philo->id, TAKE_FORK);
		pthread_mutex_lock(&data->fork[philo->right_f]);
		print(data, philo->id, TAKE_FORK);
		print(data, philo->id, EATING);
		data->philos[philo->id - 1].last_eat_time = get_time_ms();
		my_sleep(data, data->time_to_eat);
		data->philos[philo->id - 1].nb_eat++;
		if (data->philos[philo->id - 1].nb_eat == data->nb_time_philo_eat)
			data->eat_max++;
		pthread_mutex_unlock(&data->fork[philo->left_f]);
		pthread_mutex_unlock(&data->fork[philo->right_f]);
	}
	return (0);
}

void	*routine(void *phil)
{
	t_data		*data;
	t_philos	*philo;

	philo = (t_philos *)phil;
	data = philo->data;
	if (philo->id % 2 == 0)
		my_sleep(data, 15);
	while (data->death == 0 && data->eat_max < data->nb_philo)
	{
		eat(data, philo);
		print(data, philo->id, SLEEPING);
		my_sleep(data, data->time_to_sleep);
		print(data, philo->id, THINKING);
	}
	return (0);
}

int	check_death(t_data *data)
{
	int	i;

	while (data->death == 0 || data->eat_max < data->nb_philo)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (data->eat_max == data->nb_philo)
				return (0);
			if (get_time_ms() - data->philos[i].last_eat_time
				> data->time_to_die)
			{
				pthread_mutex_lock(&data->mutex_death);
				print(data, i + 1, DIED);
				data->death = 1;
				pthread_mutex_unlock(&data->mutex_death);
				return (0);
			}
			i++;
		}
	}
	return (0);
}

int	philosophers(t_data *data)
{
	int	i;

	i = 0;
	if (mutex_init(data) == -1)
	{
		free_all(data);
		return (-1);
	}
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread_philo, NULL,
				&routine, (void *)&data->philos[i]) == -1)
		{
			destroy_all(data);
			free_all(data);
			return (-1);
		}
		i++;
	}
	my_sleep(data, 10);
	check_death(data);
	join(data);
	destroy_all(data);
	free_all(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (verif_data(ac, av) || init_data(&data, av))
	{
		printf(ERROR);
		return (1);
	}
	data.time_start = get_time_ms();
	if (data.nb_philo == 1)
		return (one_phil(&data));
	else
		return (philosophers(&data));
	return (0);
}
