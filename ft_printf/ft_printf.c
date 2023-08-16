/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:14:21 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/08/16 17:45:55 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

void	ft_putchar(char c, int *d)
{
	write(1, &c, 1);
	(*d)++;
}

void	ft_putstr(char *s, int *d)
{
	if (!s)
		ft_putstr("(null)", d);
	else
		while (*s)
			ft_putchar(*s++, d);
}

void	ft_putnbr(int nb, int *d)
{
	long	n;

	n = nb;
	if (n >= 0 && n <= 9)
		ft_putchar(n + '0', d);
	if (n < 0)
	{
		ft_putchar('-', d);
		n *= (-1);
	}
	if (n > 9)
	{
		ft_putnbr(n / 10, d);
		ft_putnbr(n % 10, d);
	}
}

void	ft_puthexa(unsigned int n, int *d)
{
	char	*base;

	base = "0123456789abcdef";
	if (n < 16)
		ft_putchar(base[n], d);
	else
	{
		ft_puthexa(n / 16, d);
		ft_putchar(base[n % 16], d);
	}
}

void	check(char c, va_list args, int *d)
{
	if (c == 's')
		ft_putstr(va_arg(args, char *), d);
	else if (c == 'd')
		ft_putnbr(va_arg(args, int), d);
	else if (c == 'x')
		ft_puthexa(va_arg(args, unsigned int), d);
	else
		ft_putchar(c, d);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;

	va_start(args, s);
	i = 0;
	while (*s)
	{
		if (*s != '%')
			ft_putchar(*s, &i);
		else
		{
			s++;
			check(*s, args, &i);
		}
		s++;
	}
	va_end(args);
	return (i);
}
