/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:53:26 by ndessard          #+#    #+#             */
/*   Updated: 2024/04/26 12:35:40 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_sleep(t_data *data, time_t end)
{
	time_t	wake_up;

	wake_up = get_time(data) + end;
	while (data->dead != 1)
	{
		if (get_time(data) >= wake_up)
			break ;
		usleep(2 * data->nb_philo);
	}
}

int	str_cmp(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	if (s1[i] || s2[i])
	{
		i++;
		j = s1[i] - s2[i];
		if (j != 0)
			return (1);
	}
	return (0);
}

void	print(int id, t_data *data, char *msg)
{
	pthread_mutex_lock(&data->m_print);
	if (str_cmp(msg, "is eating"))
	{
		data->philo[id].last_eat = get_time(data);
		if (data->philo[id].nbr_eat == data->nb_of_time
			&& data->philo[id].verif == 0)
		{
			data->philo[id].verif = 1;
			data->eat_en++;
		}
	}
	if (!data->dead)
		printf("%u %d %s\n", (unsigned int)(get_time(data)), id, msg);
	pthread_mutex_unlock(&data->m_print);
}

void	ft_join(t_data *data)
{
	int	i;

	i = -1;
	while (data->philo && ++i < data->nb_philo)
		pthread_join(data->philo[i].thread, NULL);
}
