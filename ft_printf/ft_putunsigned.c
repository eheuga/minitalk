/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emheuga <emheuga@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:42:53 by emheuga           #+#    #+#             */
/*   Updated: 2025/11/12 15:05:19 by emheuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsigned(unsigned int i, int count)
{
	long	j;

	j = i;
	if (i < 0)
		j = 4294967296 + i;
	if (j > 9)
	{
		count = ft_putnbr(j / 10, count);
		count = ft_putnbr(j % 10, count);
	}
	else
		count = ft_putchar (j + '0', count);
	return (count);
}
