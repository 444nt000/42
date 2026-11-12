/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradix <444nt000@proton.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 17:01:18 by aradix            #+#    #+#             */
/*   Updated: 2026/11/12 20:01:44 by aradix           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>

#define FT(...) (label("  ft_printf : ["), ft_printf(__VA_ARGS__))
#define REAL(...) (label("]\n  printf    : ["), printf(__VA_ARGS__))
#define TEST(...) (g_ft = FT(__VA_ARGS__), check(g_ft, REAL(__VA_ARGS__)))

static int	g_ft;
static int	g_failed;

/* fflush so printf's buffered text is written before ft_printf's write */
static void	label(char *text)
{
	printf("%s", text);
	fflush(stdout);
}

static void	check(int ft, int real)
{
	printf("]\n");
	printf("  ret       : %d / %d", ft, real);
	if (ft == real)
		printf("  \033[32mOK\033[0m\n\n");
	else
	{
		printf("  \033[31mKO\033[0m\n\n");
		g_failed++;
	}
	fflush(stdout);
}

int	main(void)
{
	char	*null_str;
	int		n;

	null_str = NULL;
	printf("===== %%c =====\n");
	TEST("%c", 'a');
	TEST("%c%c%c", 'a', ' ', 'z');
	TEST("before %c after", 'x');
	printf("===== %%s =====\n");
	TEST("%s", "hello");
	TEST("%s", "");
	TEST("%s", null_str);
	TEST("[%s] [%s]", "two", "strings");
	printf("===== %%d / %%i =====\n");
	TEST("%d", 0);
	TEST("%d", 42);
	TEST("%d", -42);
	TEST("%d", INT_MAX);
	TEST("%d", INT_MIN);
	TEST("%i", -7);
	printf("===== %%u =====\n");
	TEST("%u", 0);
	TEST("%u", 42);
	TEST("%u", UINT_MAX);
	TEST("%u", -1);
	printf("===== %%x / %%X =====\n");
	TEST("%x", 0);
	TEST("%x", 255);
	TEST("%X", 255);
	TEST("%x", UINT_MAX);
	TEST("%x", -1);
	printf("===== %%p =====\n");
	TEST("%p", &n);
	TEST("%p", NULL);
	printf("===== %%%% =====\n");
	TEST("%%");
	TEST("100%% done");
	printf("===== mixed =====\n");
	TEST("%c %s %d %i %u %x %X %p %%", 'c', "str", -1, 2, 3, 255, 255, &n);
	if (g_failed == 0)
		printf("\033[32mAll values match.\033[0m\n");
	else
		printf("\033[31m%d test(s) KO.\033[0m\n", g_failed);
	return (0);
}
