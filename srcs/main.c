/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:37:16 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/23 13:17:20 by lbirloue         ###   ########.fr       */
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
		my_sleep(data, 10);
	while (data->death == 0 || data->eat_max == 0)
	{
		pthread_mutex_lock(&data->fork[philo->left_f]);
printf("ho\n");
		print(data, philo->id, "as taking a fork");
		pthread_mutex_lock(&data->fork[philo->right_f]);
		print(data, philo->id, "as taking a fork");
		print(data, philo->id, "is eating");

		philo->nb_eat++;
		my_sleep(data, data->time_to_eat);
		pthread_mutex_unlock(&data->fork[philo->left_f]);
		pthread_mutex_unlock(&data->fork[philo->right_f]);
		print(data, philo->id, "is sleeping");
		my_sleep(data, data->time_to_sleep);

		
	}

	//boucle qui changera
	return 0;
}


int	start_phil(t_data *data)
{
	data->tempo = 0;
	data->index = 0;
	printf("nb philos = %d\n", data->nb_philo);
	int	i;

	i = 0;
	pthread_mutex_init(&data->mutex_msg, NULL);
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		// printf("av\n");
		pthread_create(&data->philos[i].thread_philo, NULL, &routine, &data->philos[i]);
		i++;
	}
	/*fct check*/

	// my_sleep(data, 10);
	// while(pas de mort)
	// {
		
	// }


	my_sleep(data, 10);
	printf("test\n");
	/*fin*/
	
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread_philo, NULL);
		i++;
	}
		i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
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
	return (0);
}