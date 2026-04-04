/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emheuga <emheuga@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:42:56 by emheuga           #+#    #+#             */
/*   Updated: 2025/11/12 15:05:19 by emheuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int i, int count)
{
	long	nb;

	nb = i;
	if (nb < 0)
	{
		nb = -nb;
		count = ft_putchar('-', count);
	}
	if (nb > 9)
	{
		count = ft_putnbr(nb / 10, count);
		count = ft_putnbr(nb % 10, count);
	}
	else
		count = ft_putchar(nb + '0', count);
	return (count);
}
