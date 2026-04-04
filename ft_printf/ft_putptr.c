/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emheuga <emheuga@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:51:19 by emheuga           #+#    #+#             */
/*   Updated: 2025/11/12 15:05:19 by emheuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_hexa(unsigned long i, int count)
{
	char	c;

	if (i < 10)
		c = '0' + i;
	else
		c = 'a' + (i - 10);
	write (1, &c, 1);
	return (count + 1);
}

static int	ft_hexaptr(unsigned long i, int count)
{
	if (i >= 16)
		count = ft_hexaptr(i / 16, count);
	count = ft_print_hexa(i % 16, count);
	return (count);
}

int	ft_putptr(void *ptr, int count)
{
	unsigned long	addr;

	if (!ptr)
	{
		write (1, "(nil)", 5);
		return (count + 5);
	}
	addr = (unsigned long)ptr;
	write(1, "0x", 2);
	count += 2;
	if (addr == 0)
	{
		write(1, "0", 1);
		count += 1;
	}
	else
		count = ft_hexaptr(addr, count);
	return (count);
}
