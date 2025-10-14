/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:35:58 by jhijazi           #+#    #+#             */
/*   Updated: 2025/08/15 17:00:07 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charcheck(int i, const char *format, va_list args)
{
	int	count;

	count = 0;
	if (format[i + 1] == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (format[i + 1] == 'X')
		count += ft_puthex(1, (unsigned long)va_arg(args, unsigned int));
	else if (format[i + 1] == 'x')
		count += ft_puthex(0, (unsigned long)va_arg(args, unsigned int));
	else if (format[i + 1] == 'i' || format[i + 1] == 'd')
		count += ft_putint(va_arg(args, int));
	else if (format[i + 1] == '%')
		count += ft_putchar('%');
	else if (format[i + 1] == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (format[i + 1] == 'p')
		count += ft_putadd(va_arg(args, void *));
	else if (format[i + 1] == 'u')
		count += ft_putunsigned(va_arg(args, unsigned int));
	else
	{
		ft_putchar(format[i]);
		return (2);
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	args;
	size_t	i;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1])
		{
			count += ft_charcheck(i, format, args);
			i++;
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
