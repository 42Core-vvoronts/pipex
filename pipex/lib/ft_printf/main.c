#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

int main()
{
	int result;
	int resultlib;
	int int_max    =  2147483647;         // Maximum value for an int
	int int_min    = -2147483648;         // Minimum value for an int
	long long_max  =  9223372036854775807; // Maximum value for a long
	long long_min  = -9223372036854775808; // Minimum value for a long
	unsigned long ulong_max =  18446744073709551615; // Maximum value for an unsigned long


	resultlib = printf("S NULL%sNULL\n", (char *)NULL);
	result = ft_printf("S NULL%sNULL\n", (char *)NULL);
	printf("Custom: %d Lib: %d\n\n", result, resultlib);

	resultlib = printf("P: %p %p \n", 0, 0);
	result = ft_printf("P: %p %p \n", 0, 0);
	printf("Custom: %d Lib: %d\n\n", result, resultlib);

	resultlib = printf("c: %c %c \n", 0, 1);
	result = ft_printf("c: %c %c \n", 0, 1);
	printf("Custom: %d Lib: %d\n\n", result, resultlib);

	resultlib = printf("%p", NULL);
	result = ft_printf("%p", NULL);
	printf("Custom: %d Lib: %d\n\n", result, resultlib);

	resultlib = printf("P: %pp%p%p\n", (void *)LONG_MAX + 423856, (void *)0, (void *)INT_MAX);
	result = ft_printf("P: %pp%p%p\n", (void *)LONG_MAX + 423856, (void *)0, (void *)INT_MAX);
	printf("Custom: %d Lib: %d\n\n", result, resultlib);

	resultlib = printf("P %p %p \n", (void *)0, (void *)0);
	result = ft_printf("P %p %p \n", (void *)0, (void *)0);
	printf("Custom: %d Lib: %d\n\n", result, resultlib);

	// Test cases d
	resultlib = printf("d %d \n", 0);
	result = ft_printf("d %d \n", 0);
	printf("Custom: %d Lib: %d\n\n", result, resultlib);

	resultlib = printf("d %d \n", INT_MIN);
	result = ft_printf("d %d \n", INT_MIN);
	printf("Custom: %d Lib: %d\n\n", result, resultlib);

	resultlib = printf("d %d \n", LONG_MIN);
	result = ft_printf("d %d \n", LONG_MIN);
	printf("Custom: %d Lib: %d\n\n", result, resultlib);

	resultlib = printf("d %d %d %d %d %d %d %d \n", int_max, int_min, long_max, long_min, ulong_max, 0, -42);
	result = ft_printf("d %d %d %d %d %d %d %d \n", int_max, int_min, long_max, long_min, ulong_max, 0, -42);
	printf("Custom: %d Lib: %d\n\n", result, resultlib);

	// Test cases i
	resultlib = printf("i %i \n", 0);
	result = ft_printf("i %i \n", 0);
	printf("Custom: %d Lib: %d\n\n", result, resultlib);

	resultlib = printf("i %i \n", INT_MIN);
	result = ft_printf("i %i \n", INT_MIN);
	printf("Custom: %d Lib: %d\n\n", result, resultlib);

	resultlib = printf("i %i \n", LONG_MIN);
	result = ft_printf("i %i \n", LONG_MIN);
	printf("Custom: %d Lib: %d\n\n", result, resultlib);

	resultlib = printf("i %i %i %i %i %i %i %i \n", int_max, int_min, long_max, long_min, ulong_max, 0, -42);
	result = ft_printf("i %i %i %i %i %i %i %i \n", int_max, int_min, long_max, long_min, ulong_max, 0, -42);
	printf("Custom: %d Lib: %d\n\n", result, resultlib);

	resultlib = printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%\n", 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
	result = ft_printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%\n", 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
	printf("Custom: %d Lib: %d\n\n", result, resultlib);

	return (0);
}
