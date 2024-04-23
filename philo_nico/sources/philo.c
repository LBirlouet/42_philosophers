/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndessard <ndessard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:42:21 by ndessard          #+#    #+#             */
/*   Updated: 2024/04/19 16:40:46 by ndessard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	is_dead(t_data *data)
{
	int	i;

	while (data->dead != 1 && data->eat_en <= data->nb_philo)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			if (data->eat_en == data->nb_philo)
				return ;
			if ((get_time(data) - data->philo[i].last_eat) > data->t_to_die)
			{
				pthread_mutex_lock(&data->m_dead);
				print(data->philo[i].id, data, "\033[0;38;5;214mdied\033[0m");
				data->dead = 1;
				pthread_mutex_unlock(&data->m_dead);
				return ;
			}
		}
	}
	return ;
}

static int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (destroy_fork(data, data->nb_philo, 1), 1);
	while (++i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_eat = 0;
		data->philo[i].nbr_eat = 0;
		data->philo[i].left_fork = i;
		data->philo[i].verif = 0;
		if (data->nb_philo > 1)
			data->philo[i].right_fork = (i + 1) % data->nb_philo;
		data->philo[i].data = data;
	}
	data->start_time = get_time(data);
	return (0);
}

static int	init_fork(t_data *data)
{
	int	i;

	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->fork)
		return (1);
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (destroy_fork(data, i, 0), 1);
	}
	if (pthread_mutex_init(&(data->m_print), NULL))
		return (destroy_fork(data, data->nb_philo, 0), 1);
	if (pthread_mutex_init(&(data->m_dead), NULL))
		return (destroy_fork(data, data->nb_philo, 0), 1);
	data->dead = 0;
	return (0);
}

static int	init_input(t_data *data, char **av)
{	
	data->nb_philo = ft_atol(av[0]);
	if (data->nb_philo > 200)
	{
		printf("coquin va\n");
		return (1);
	}
	data->t_to_die = ft_atol(av[1]);
	data->t_to_eat = ft_atol(av[2]);
	data->t_to_sleep = ft_atol(av[3]);
	data->all_eat = 0;
	data->dead = 0;
	data->eat_en = 0;
	data->nb_of_time = -1;
	if (av[4])
		data->nb_of_time = ft_atol(av[4]);
	data->philo = NULL;
	data->start_time = 0;
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (ac != 5 && ac != 6)
		return (printf("Error: Try with 5 or 6 arg\n"), 1);
	if (check_value(av + 1) || init_input(&data, av + 1))
		return (printf("Error: Invalid arg\n"), 1);
	if (init_fork(&data))
		return (printf("Error: Init_fork\n"), 1);
	if (init_philo(&data))
		return (printf("Error: Init_philo\n"), 1);
	i = -1;
	if (data.nb_philo == 1)
		return (only_one(&data));
	else
	{
		while (++i < data.nb_philo)
			if (pthread_create(&data.philo[i].thread, NULL,
					routine, (void *)&data.philo[i]))
				return (destroy_all(&data), 1);
	}
	ft_sleep(&data, 10);
	is_dead(&data);
	ft_join(&data);
	return (destroy_all(&data), 0);
}
