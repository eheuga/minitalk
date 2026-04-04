/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emheuga <emheuga@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:45:43 by emheuga           #+#    #+#             */
/*   Updated: 2025/11/12 15:05:19 by emheuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_type(const char *format, int count, va_list args)
{
	if (format == NULL || *format == '\0')
		return (count);
	if (*format == 'c')
		count = ft_putchar(va_arg(args, int), count);
	if (*format == 's')
		count = ft_putstr(va_arg(args, char *), count);
	if (*format == '%')
		count = ft_putchar('%', count);
	if (*format == 'i' || *format == 'd')
		count = ft_putnbr(va_arg(args, int), count);
	if (*format == 'u')
		count = ft_putunsigned(va_arg(args, unsigned int), count);
	if (*format == 'x' || *format == 'X')
		count = ft_puthexa(va_arg(args, unsigned int), count, *(char *)format);
	if (*format == 'p')
		count = ft_putptr(va_arg(args, void *), count);
	return (count);
}
