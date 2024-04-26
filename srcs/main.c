/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:37:16 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/26 15:55:21 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


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
		pthread_mutex_lock(&data->fork[philo->left_f]);
		print(data, philo->id, "\033[0;32;5;32mas taking a fork\033[0m");
		pthread_mutex_lock(&data->fork[philo->right_f]);
		print(data, philo->id, "\033[0;32;5;32mas taking a fork\033[0m");
		print(data, philo->id, "\033[0;38;5;39;3mis eating\033[0m");
			
		data->philos[philo->id - 1].last_eat_time = get_time_ms();
		// printf("|||||||||%llu||||||||||| (philo : %d)\n",data->philos[philo->id].last_eat_time,philo->id );
		my_sleep(data, data->time_to_eat);
		data->philos[philo->id - 1].nb_eat++;
		if (data->philos[philo->id - 1].nb_eat == data->nb_time_philo_eat)
			data->eat_max++;
		pthread_mutex_unlock(&data->fork[philo->left_f]);
		pthread_mutex_unlock(&data->fork[philo->right_f]);
		// if (data->eat_max == data->nb_philo)
		// {
		// 	// printf("max eat\n");
		// 	return (0);
		// }
		if (data->death == 0) //decortiquer et mettre plusieurs fois
		{
		print(data, philo->id, "\033[0;38;5;219mis sleeping\033[0m");
		my_sleep(data, data->time_to_sleep);
		print(data, philo->id, "\033[0;38;5;226mis thinking\033[0m");
		}
	}
	return 0;
}

int	destroy_mutex_init(t_data *data, int i)
{
	pthread_mutex_destroy(&data->mutex_msg);
	pthread_mutex_destroy(&data->mutex_death);
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i--;
	}
	return (-1);
}

int	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->philos)
		return (-1);
	if (pthread_mutex_init(&data->mutex_msg, NULL))
		return (-1);
	if (pthread_mutex_init(&data->mutex_death, NULL))
	{
		pthread_mutex_destroy(&data->mutex_msg);
		return (-1);
	}
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (destroy_mutex_init(data, i));
		i++;
	}
	return (0);
}


int	destroy_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_msg);
	pthread_mutex_destroy(&data->mutex_death);
	return (0);
}

int	free_all(t_data *data)
{
	free(data->fork);
	free(data->philos);
	return (0);
}

int	check_death(t_data *data)
{
	time_t	time;
	int		i;

	while (data->death == 0 || data->eat_max < data->nb_philo)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (data->eat_max == data->nb_philo)
				return (0);
			if (get_time_ms() - data->philos[i].last_eat_time > data->time_to_die)
			{
				pthread_mutex_lock(&data->mutex_death);
				time = get_time_ms() - data->time_start;
				print(data, i + 1, "\033[1;38;5;210mdied\033[0m");
				//printf("[%ld] [%d] %s\n", time, i + 1, "\033[1;38;5;210mdied\033[0m");
				data->death = 1;
				pthread_mutex_unlock(&data->mutex_death);
				return (0);
			}
			i++;
		}
	}
	return (0);
}

int	join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread_philo, NULL);
		i++;
	}
	return (0);
}

int	start_phil(t_data *data)
{
	int	i;

	i = 0;
	printf("nb philos = %d\n", data->nb_philo);
	if (mutex_init(data) == -1)
		return (-1);
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread_philo, NULL,
				&routine, (void *)&data->philos[i]) == -1)
		{
			free_all(data);
			destroy_all(data);
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

	if (verif_data(ac,av)|| init_data(&data, ac, av))
		return (printf(error_0), 1);
	if (data.nb_philo == 1)
		return (one_phil(&data));
	else
		return (start_phil(&data));
	return (0);
}