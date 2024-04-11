/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:48:25 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/11 15:58:02 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int ft_atoi(char *str)
// {
    
// }

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