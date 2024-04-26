/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:48:25 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/26 14:48:27 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h" 

time_t	get_time_ms(void)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	my_sleep(t_data *data, time_t time)
{
	// time_t	act_t;
	time_t	final;

(void)data;
	final = get_time_ms() + time;
	while (1)
	{
		if (get_time_ms() >= final)
			break;
		usleep(2 * data->nb_philo);
	}
	return ;
}

long long	mini_atoi(char *str)
{
	long long	ret;
	long long	i;

	ret = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9' && ret < 9223372036854775807)
	{
		ret = (ret * 10) + (str[i] - 48);
		i++;
	}
	return (ret);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_is_nb(char c)
{
	if (c < '0' || c > '9')
		return (-1);
	return (0);
}