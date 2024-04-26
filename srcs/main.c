/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:37:16 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/26 13:25:17 by lbirloue         ###   ########.fr       */
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
	while (data->death == 0 || data->eat_max == 0)
	{
		pthread_mutex_lock(&data->fork[philo->left_f]);
		print(data, philo->id, "as taking a fork");
		pthread_mutex_lock(&data->fork[philo->right_f]);
		print(data, philo->id, "as taking a fork");
		print(data, philo->id, "is eating");
		data->philos[philo->id - 1].last_eat_time = get_time_ms();
		// printf("|||||||||%llu||||||||||| (philo : %d)\n",data->philos[philo->id].last_eat_time,philo->id );
		data->philos[philo->id - 1].nb_eat++;
		my_sleep(data, data->time_to_eat);
		pthread_mutex_unlock(&data->fork[philo->left_f]);
		pthread_mutex_unlock(&data->fork[philo->right_f]);
		/**/
		/*sleep*/
		print(data, philo->id, "is sleeping");
		my_sleep(data, data->time_to_sleep);
		/**/
		print(data, philo->id, "is thinking");
	}
	return 0;
}

int	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->philos)
		return (-1);
	pthread_mutex_init(&data->mutex_msg, NULL); //a verif
	pthread_mutex_init(&data->mutex_death, NULL); //a verif
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL); //a verif
		i++;
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
				&routine, (void *)&data->philos[i])  == -1)
		{
			//destroy mutex;
			return (-1);
		}
		i++;
	}
	my_sleep(data, 10);
	while (data->death == 0 || data->eat_max == 0)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			// printf("philo[%d] => %llu\n",i, data->philos[i].last_eat_time);
			// printf("%lu > %lu\n", data->philos[i].last_eat_time, data->time_to_die);
			if (get_time_ms() - data->philos[i].last_eat_time > data->time_to_die)
			{
				// printf("dead\n");
				pthread_mutex_lock(&data->mutex_msg);
				print(data, i + 1, "IS DEEEEEEEEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAD\n\n");
				data->death = 1;
				pthread_mutex_unlock(&data->mutex_msg);
				return (0);
			}
			i++;
		}
	}
	join(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (verif_data(ac,av)|| init_data(&data, ac, av))
		return (printf(error_0), 1);
	printf("good data\n");
	if (data.nb_philo == 1)
		return (one_phil(&data));
	else
		return (start_phil(&data));
	free_all(&data);
	destroy_all(&data);
	return (0);
}