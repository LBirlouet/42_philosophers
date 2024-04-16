/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:37:16 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/16 13:13:38 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h" 

bool check_finish(t_data *data)
{
	if (data->finish == true)
		return (true);
	return (false);
}

void	check_last_eat(t_data *data, int i)
{
	u_int64_t act_time = get_time_ms();

	// printf("%llu - %llu > %llu\n", act_time, data->philos[i].last_eat_time, data->time_to_die);
	if ((act_time - data->philos[i].last_eat_time) > data->time_to_die)
	{
		data->philos[i].status = 4;
		print_death(data, i);
		data->finish = true;
	}
	return ;
}

void	*more_philos_r(void *data)
{
	int i = 0;;
	t_data	*cpdata = (t_data *)data;
	if (cpdata->ready == 1)
	{
		while (check_finish(data) == false)
		{
			if (i == cpdata->nb_philo)
			{
				// cpdata->finish = true;
				i = 0;
			}
			pthread_mutex_lock(&cpdata->philos[i].locked);
			printf("wi\n");
			check_last_eat(cpdata, i);
			pthread_mutex_unlock(&cpdata->philos[i].locked);
			i++;
		}
	}
	return 0;
}


int	more_phil(t_data *data)
{
	data->tempo = 0;
	printf("nb philos = %d\n", data->nb_philo);
	int	i;

	i = 0;
	while (i < data->nb_philo - 1)
	{
		pthread_mutex_init(&data->philos[i].locked, NULL);
		pthread_mutex_init(&data->philos[i].left_f, NULL);
		pthread_mutex_init(&data->philos[i].right_f, NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		// int w = 1;
		pthread_create(&data->philos[i].thread_philo, NULL, &more_philos_r, data);
		if (i + 1 == data->nb_philo)
		{
		data->tempo = 9;
			data->ready = 1;
		}
		i++;
	}


	
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread_philo, NULL);
		i++;
	}
		i = 0;
	while (i < data->nb_philo - 1)
	{
		pthread_mutex_destroy(&data->philos[i].locked);
		pthread_mutex_destroy(&data->philos[i].left_f);
		pthread_mutex_destroy(&data->philos[i].right_f);
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
		return (more_phil(&data));
	return (0);
}