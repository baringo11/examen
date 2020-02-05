/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:27:21 by jbaringo          #+#    #+#             */
/*   Updated: 2020/02/05 14:39:06 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

typedef	struct s_print
{
	char	*str;
	int		i;
	int		j;
	int		length;
	int		precision;
	int		p;
	int		width;
	va_list	ap;
}		t_variables;

void	ft_putchar(char c)
{
	write(1, &c, 1);	
}

t_variables *set_init (char *s)
{
	t_variables *var;
	
	if (!(var = malloc(sizeof(var))))
		return (NULL);
	var->str = s;
	var->i = 0;
	var->j = 0;
	var->length = 0;
	var->precision = 0;
	var->p = 0;
	var->width = 0;
	return (var);
}

void	set_to_cero(t_variables **var)
{
	(*var)->length = 0;
	(*var)->precision = 0;
	(*var)->p = 0;
	(*var)->width = 0;
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

char	*ft_strchr(char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

int		num_size(int n)
{
	int i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	i++;
	return (i);
}

void	ft_putnbr(int n)
{
	unsigned int nb;
	
	if (n < 0)
	{
		ft_putchar('-');
		nb = (unsigned int)n * -1;
	}
	else
		nb = (unsigned int)n;
	if (nb >= 10)
		ft_putnbr(nb / 10);
	ft_putchar((nb % 10) + 48);
}

void	ft_putstrn(char *s, int n)
{
	int i;
	
	i = 0;
	while (s[i] && i < n)
	{
		ft_putchar(s[i]);
		i++;
	}
}

void	ft_putstr(char *s)
{
	int i;
	
	i = 0;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
}

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	check_length(char *s, t_variables **var)
{
	char	*num;
	
	while (ft_isdigit(s[(*var)->i]))
	{
		num = ft_strchr("0123456789", s[(*var)->i]);
		(*var)->length += num[0] - 48;
		if (ft_isdigit(s[(*var)->i + 1]))
			(*var)->length *= 10;
		(*var)->i++;
	}
}

void	check_precision(char *s, t_variables **var)
{
	char	*num;

	(*var)->p = 1;
	(*var)->i++;
	while (ft_isdigit(s[(*var)->i]))
	{
		num = ft_strchr("0123456789", s[(*var)->i]);
		(*var)->precision += num[0] - 48;
		if (ft_isdigit(s[(*var)->i + 1]))
			(*var)->precision *= 10;
		(*var)->i++;
	}
}

int		cont_hex(unsigned int n, t_variables **var)
{
	int i;
	
    i = 0;
    if (!(n == 0 && (*var)->p == 1 && (*var)->precision == 0))
        i++;
	while (n > 16)
	{
		n /= 16;
		i++;
	}
	if ((*var)->length != 0 && (*var)->length > i)
		(*var)->j += (*var)->length;
	else if ((*var)->p == 1 && (*var)->precision > i)
		(*var)->j += (*var)->precision;
	else
		(*var)->j += i;
	(*var)->width += (*var)->length - i;
	if ((*var)->p == 1 && (*var)->precision > i)
		(*var)->width -= (*var)->precision - i;
	return (i);
}

void		print_hex(unsigned int n)
{
	char *hex;
	
	hex = "0123456789abcdef";
	if (n >= 16)
		print_hex(n / 16);
	ft_putchar(hex[n % 16]);
}

void		if_hexadecimal(int n, t_variables **var)
{
	int i;

	i = cont_hex(n, var);
	while ((*var)->width > 0)
	{
		ft_putchar(' ');
		(*var)->width--;
	}
	while (((*var)->precision - i) > 0)
	{
		ft_putchar('0');
		(*var)->precision--;
	}
    if (!(n == 0 && (*var)->p == 1 && (*var)->precision == 0))
        print_hex(n);
	(*var)->i++;
}

void		cont_str(char *str, t_variables **var)
{
	int i;
	
	i = 0;
	while (str[i] != '\0')
		i++;
	if ((*var)->p == 1 && (*var)->precision < i)
		i = (*var)->precision;
	if ((*var)->length > i)
		(*var)->j += (*var)->length;
	else
		(*var)->j += i;
}

void	if_string(char *s, t_variables **var)
{
    if (!s)
        s = "(null)";
	if ((*var)->p == 1 && (*var)->precision < ft_strlen(s))
		(*var)->width = (*var)->length - (*var)->precision;
	else
		(*var)->width = (*var)->length - ft_strlen(s);
	while ((*var)->width > 0)
	{
		ft_putchar(' ');
		(*var)->width--;
	}
	if ((*var)->p == 1)
		ft_putstrn(s, (*var)->precision);
	else
		ft_putstr(s);
	cont_str(s, var);
	(*var)->i++;
}

void	cont_int(int n, t_variables **var)
{
	int size;

	size = num_size(n);
	if (n < 0)
		size++;
	if ((*var)->length > size && (*var)->length > (*var)->precision)
		(*var)->j += (*var)->length;
	else if ((*var)->p == 1 && (*var)->precision > size)
	{
		(*var)->j += (*var)->precision;
		if (n < 0)
			(*var)->j++;
	}
	else
		(*var)->j += size;
}

void	if_int(int n, t_variables **var)
{
	(*var)->width = (*var)->length - num_size(n);
	if ((*var)->precision > num_size(n))
		(*var)->width -= (*var)->precision - num_size(n);
    if (n < 0)
        (*var)->width--;
    cont_int(n, var);
	while ((*var)->width > 0)
	{
		ft_putchar(' ');
		(*var)->width--;
	}
    if ((*var)->p == 1 && n < 0)
        ft_putchar('-');
    while ((*var)->precision - num_size(n) > 0)
    {
        ft_putchar('0');
        (*var)->precision--;
    }
    if ((*var)->p == 1 && n < 0)
        n = n * -1;
    if (!(n == 0 && (*var)->p == 1 && (*var)->precision == 0))
        ft_putnbr(n);
    else if ((*var)->length == 0)
        (*var)->j--;
    else
        ft_putchar(' ');
    (*var)->i++;
}

void	check_flag(char *s, t_variables **var)
{
	if (ft_isdigit(s[(*var)->i]))
		check_length(s, var);
	if (s[(*var)->i] == '.')
		check_precision(s, var);
	if (s[(*var)->i] == 'd')
		if_int(va_arg((*var)->ap, int), var);
	if (s[(*var)->i] == 's')
		if_string(va_arg((*var)->ap, char *), var);
	if (s[(*var)->i] == 'x')
		if_hexadecimal(va_arg((*var)->ap, int), var);
}

void	find_percent(char *s, t_variables **var)
{
	while (s[(*var)->i])
	{
		if (s[(*var)->i] == '%')
		{
			(*var)->i++;
			check_flag(s, var);
			set_to_cero(var);
		}
		else
		{
			ft_putchar(s[(*var)->i]);
			(*var)->i++;
			(*var)->j++;
		}
	}
}

int	ft_printf(char *format, ...)
{
	t_variables *var;

	var = set_init(format);
	va_start(var->ap, format);
	find_percent(format, &var);
	va_end(var->ap);
	//printf("final j: %d\n", var->j);
	free(var);
	return (var->j);
}
