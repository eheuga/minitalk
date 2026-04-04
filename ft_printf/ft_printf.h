/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emheuga <emheuga@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:09:52 by emheuga           #+#    #+#             */
/*   Updated: 2026/04/04 14:07:06 by emheuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	ft_type(const char *format, int count, va_list args);
int	ft_putchar(int c, int count);
int	ft_putstr(char *str, int count);
int	ft_putnbr(int i, int count);
int	ft_putunsigned(unsigned int i, int count);
int	ft_puthexa(unsigned int i, int count, char format);
int	ft_putptr(void *ptr, int count);

#endif
