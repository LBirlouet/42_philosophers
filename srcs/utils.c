/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:48:25 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/12 07:54:27 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int ft_atoi(char *str)
// {
    
// }
int	mini_atoi(char *str)
{
	long long	ret;
	int	i;

	ret = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9' && ret < 9223372036854775807)
	{
		ret = (ret * 10) + (str[i] - 48);
		i++;
	}
	if (ret > __INT_MAX__)
		return (-1);
	return ((int)ret);
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