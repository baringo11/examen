/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:35:42 by jbaringo          #+#    #+#             */
/*   Updated: 2020/02/05 14:25:21 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_printf.c"

int	ft_printf(char *s, ...);

int	main(void)
{
	int a;
	ft_printf("%x\n", 4294967295u);
	a = printf("%x\n", 4294967295u);
//	ft_printf("Hexadecimal for %d is %x\n", 42, 0);
//	a = printf("Hexadecimal for %d is %x\n", 42, 0);

	printf("a: %d\n", a);
}