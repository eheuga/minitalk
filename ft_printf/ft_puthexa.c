/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emheuga <emheuga@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:42:58 by emheuga           #+#    #+#             */
/*   Updated: 2025/11/12 15:05:19 by emheuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_hexamin(int i, int count)
{
	char	c;

	if (i < 10)
		c = '0' + i;
	else
		c = 'a' + (i - 10);
	write (1, &c, 1);
	return (count + 1);
}

static int	ft_print_hexamaj(int i, int count)
{
	char	c;

	if (i < 10)
		c = '0' + i;
	else
		c = 'A' + (i - 10);
	write (1, &c, 1);
	return (count + 1);
}

int	ft_puthexa(unsigned int i, int count, char format)
{
	long	nb;

	nb = i;
	if (i < 0)
		nb = 4294967296 + nb;
	if (nb >= 16)
		count = ft_puthexa(nb / 16, count, format);
	if (format == 'x')
		count = ft_print_hexamin(nb % 16, count);
	else if (format == 'X')
		count = ft_print_hexamaj(nb % 16, count);
	return (count);
}
