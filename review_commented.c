#include "ft_printf.h"

int		main(void)
{
	int a,b,c;
	int *p;

	puts("----------------Simple Conversion Management\n");

	a = printf("[42Tokyo]\n"); // [42Tokyo]
	b = ft_printf("[42Tokyo]\n");
	printf("%d, %d\n", a, b); // 10

	printf("---%%c---\n");
	a = printf("[%c][%c][%c]\n", '\0', '\0', 'C'); // [][][C]
	b = ft_printf("[%c][%c][%c]\n", '\0', '\0', 'C');
	printf("%d, %d\n", a, b); // 10

	printf("---%%s---\n");
	a = printf("[%s]\n", NULL); // [(null)]
	b = ft_printf("[%s]\n", NULL);
	printf("%d, %d\n", a, b); // 9
	a = printf("[%s] [%s]\n", "Born2Code", ""); // []
	b = ft_printf("[%s] [%s]\n", "Born2Code", "");
	printf("%d, %d\n", a, b); // 15

	printf("---%%d---\n");
	a = printf("[%d] [%s]\n",INT_MIN, NULL); // [-2147483648] [(null)]
	b = ft_printf("[%d] [%s]\n", INT_MIN, NULL);
	printf("%d, %d\n", a, b); // 23
	a = printf("[%d]\n", INT_MAX); // [2147483647]
	b = ft_printf("[%d]\n", INT_MAX);
	printf("%d, %d\n", a, b);
	a = printf("[%d]\n",0);
	b = ft_printf("[%d]\n", 0);
	printf("%d, %d\n", a, b); // 13

	printf("---%%i---\n");
	a = printf("[%i]\n",-12345); // [-12345]
	b = ft_printf("[%i]\n", -12345);
	printf("%d, %d\n", a, b); // 9

	printf("---%%u---\n");
	a = printf("[%u]\n",-12345); // [4294954951]
	b = ft_printf("[%u]\n", -12345);
	printf("%d, %d\n", a, b); // 13

	printf("---%%p---\n");
	int pt = 1;
	a = printf("[%p]\n", NULL); // [0x0]
	b = ft_printf("[%p]\n", NULL);
	printf("%d, %d\n", a, b); // 6

	a = printf("[%p]\n", &pt); // [省略]
	b = ft_printf("[%p]\n", &pt);
	printf("%d, %d\n", a, b); // 17

	printf("---%%x---\n");
	a = printf("[%x]\n",INT_MIN); // [80000000]
	b = ft_printf("[%x]\n",INT_MIN);
	printf("%d, %d\n", a, b); // 11
	a = printf("[%x]\n", INT_MAX); // [7fffffff]
	b = ft_printf("[%x]\n",INT_MAX);
	printf("%d, %d\n", a, b); // 11
	a = printf("[%x]\n", 0); // [0]
	b = ft_printf("[%x]\n", 0);
	printf("%d, %d\n", a, b); // 4

	printf("---%%X---\n");
	a = printf("[%X]\n",INT_MIN); // [80000000]
	b = ft_printf("[%X]\n", INT_MIN);
	printf("%d, %d\n", a, b); // 11
	a = printf("[%X]\n",INT_MAX); // [7FFFFFFF]
	b = ft_printf("[%X]\n", INT_MAX);
	printf("%d, %d\n", a, b); // 11
	a = printf("[%X]\n", 0); // [0]
	b = ft_printf("[%X]\n", 0);
	printf("%d, %d\n", a, b); // 4

	printf("-----various conversion-----\n");
	a = printf("%s %d %p %% %i %x %X %c \n", "monoue", 42, p, 42, 42, 42, 'c'); // monoue 42 0x0 % 42 2a 2A c
	b = ft_printf("%s %d %p %% %i %x %X %c \n", "monoue", 42, p, 42, 42, 42, 'c');
	printf("%d, %d\n", a, b); // 30
	a = printf("s: %s,b string p: %p, d:%d\n", "a string", p, 42); // s: a string,b string p: 0x0, d:42
	b = ft_printf("s: %s,b string p: %p, d:%d\n", "a string", p, 42);
	printf("%d, %d\n", a, b); // 34

	puts("\n----------------Simple Flag Management\n");

	printf("---[%%12s], 文字数9---\n");
	a = printf("[%12s]\n", "Born2Code"); // [   Born2Code]
	b = ft_printf("[%12s]\n", "Born2Code");
	printf("%d, %d\n", a, b); // 15
	printf("---[%%9s], 文字数9---\n"); // [Born2Code]
	a = printf("[%9s]\n", "Born2Code");
	b = ft_printf("[%9s]\n", "Born2Code");
	printf("%d, %d\n", a, b); // 12
	printf("---[%%3s], 文字数9---\n");
	a = printf("[%3s]\n", "Born2Code"); // [Born2Code]
	b = ft_printf("[%3s]\n", "Born2Code");
	printf("%d, %d\n", a, b); // 12


	printf("------ -flag ------\n");
	printf("---[%%-10s], 文字数7---\n");
	a = printf("[%-10s]\n", "42tokyo"); // [42tokyo   ]
	b = ft_printf("[%-10s]\n", "42tokyo");
	printf("%d, %d\n", a, b); // 13
	printf("---[%%-7s], 文字数7---\n");
	a = printf("[%-7s]\n", "42tokyo"); // [42tokyo]
	b = ft_printf("[%-7s]\n", "42tokyo");
	printf("%d, %d\n", a, b); // 10
	printf("---[%%-2s], 文字数7---\n");
	a = printf("[%-2s]\n", "42tokyo"); // [42tokyo]
	b = ft_printf("[%-2s]\n", "42tokyo");
	printf("%d, %d\n", a, b); // 10

	printf("------ 0flag ------\n");
	printf("---[%%012s], 文字数9---\n");
	a = printf("[%012s]\n", "Born2Code"); // [000Born2Code]
	b = ft_printf("[%012s]\n", "Born2Code");
	printf("%d, %d\n", a, b); // 15

	printf("---[%%09s], 文字数9---\n");
	a = printf("[%09s]\n", "Born2Code"); //[Born2Code]
	b = ft_printf("[%09s]\n", "Born2Code");
	printf("%d, %d\n", a, b); // 12

	printf("---[%%03s], 文字数9---\n");
	a = printf("[%03s]\n", "Born2Code"); // [Born2Code]
	b = ft_printf("[%03s]\n", "Born2Code");
	printf("%d, %d\n", a, b); // 12

	printf("---[%%9.5s], 文字数9---\n");
	a = printf("[%9.5s]\n", "Born2Code"); // [    Born2]
	b = ft_printf("[%9.5s]\n", "Born2Code");
	printf("%d, %d\n", a, b); // 12

	printf("---[%%9.12s], 文字数9---\n");
	a = printf("[%9.12s]\n", "Born2Code"); // [Born2Code]
	b = ft_printf("[%9.12s]\n", "Born2Code");
	printf("%d, %d\n", a, b); // 12

	printf("---[%%9.0s], 文字数9---\n");
	a = printf("[%9.0s]\n", "Born2Code"); // [         ]
	b = ft_printf("[%9.0s]\n", "Born2Code");
	printf("%d, %d\n", a, b); // 12

	printf("---[%%9.0.5s], 文字数9---\n");
	a = printf("[%9.0.5s]\n", "Born2Code"); // [    Born2]
	b = ft_printf("[%9.0.5s]\n", "Born2Code");
	printf("%d, %d\n", a, b); // 12


	printf("\n-----------------Advanced Flags Management*/\n");


	ft_printf("[%%10.12s]---------\n");
	a = printf("minimum field: [%*.12s]\n", 10,"42tokyo"); // minimum field: [   42tokyo]
	b = ft_printf("minimum field: [%*.12s]\n",10, "42tokyo");
	printf("%d, %d\n", a, b); // 28
	ft_printf("[%%-1.12s]----------\n");
	a = printf("minimum field: [%*.9s]\n",-1,"42tokyo"); // minimum field: [42tokyo]
	b = ft_printf("minimum field: [%*.9s]\n",-1, "42tokyo");
	printf("%d, %d\n", a, b); // 25
	ft_printf("[%%-12.12s]----------\n");
	a = printf("minimum field: [%*.9s]\n",-12,"42tokyo"); // minimum field: [42tokyo     ]
	b = ft_printf("minimum field: [%*.9s]\n",-12, "42tokyo");
	printf("%d, %d\n", a, b); // 30
	ft_printf("[%%0.12s]----------\n");
	a = printf("minimum field: [%*.9s]\n",0,"42tokyo");
	b = ft_printf("minimum field: [%*.9s]\n",0, "42tokyo");
	printf("%d, %d\n", a, b);

	printf("[%%.(-1)s]-------------\n");
	a = printf("precision[%9.*s]\n",-1, "born2code"); // 負は無効
	b = ft_printf("precision[%9.*s]\n",-1, "born2code");
	printf("%d, %d\n", a, b);
	printf("[%%.0s]----------------\n");
	a = printf("precision: [%9.*s]\n", 0,"42tokyo");
	b = ft_printf("precision: [%9.*s]\n", 0,"42tokyo");
	printf("%d, %d\n", a, b);
	printf("[%%.2s]---------------\n");
	a = printf("precision: [%.*s]\n", 4,"42tokyo");
	b = ft_printf("precision: [%.*s]\n", 4,"42tokyo");
	printf("%d, %d\n", a, b);

	printf("[%%20.2s]---------------\n");
	a = printf("both: [%*.*s]\n", 20,2,"42tokyo");
	b = ft_printf("both: [%*.*s]\n", 20,2,"42tokyo");
	printf("%d, %d\n", a, b);

	printf("\n---------------------*Get Crazy*\n");

	printf("---[-0-020.4u]---\n");
	a = printf("[%-0-020.4u]\n", -12345);
	b = ft_printf("[%-0-020.4u]\n", -12345);
	printf("%d, %d\n", a, b);

	printf("---[-00012.9x]---\n");
	a = printf("[%-00012.9x]\n",-12345);
	b = ft_printf("[%-00012.9x]\n", -12345);
	printf("%d, %d\n", a, b);

	printf("---[000*.*x]---\n");
	a = printf("[%000*.*x]\n",12, 30, -12345);
	b = ft_printf("[%000*.*x]\n", 12, 30,-12345);
	printf("%d, %d\n", a, b);

	printf("---[---*.*x]---\n");
	a = printf("[%---*.*x]\n",12, 3, -12345);
	b = ft_printf("[%---*.*x]\n", 12, 3,-12345);
	printf("%d, %d\n", a, b);

	printf("---[%%-5.4d]---\n");
	a = printf("[%-5.4d]\n",-123);
	b = ft_printf("[%-5.4d]\n",-123);
	printf("%d, %d\n", a, b);

	printf("---[%%12.2.9.3-5s]---\n");
	a = printf("[%12.2.9.3-05s]\n", "42tokyo");
	b = ft_printf("[%12.2.9.3-05s]\n", "42tokyo");
	printf("%d, %d\n", a, b);

	printf("---[%%7.10.20..13.5d]---\n");
	a = printf("[%7.10.20..13.5d]\n", 123);
	b = ft_printf("[%7.10.20..13.5d]\n", 123);
	printf("%d, %d\n", a, b);

	printf("---[%%.10.20d]---\n");
	a = ft_printf("[%.10.20d]\n", -42);
	b = printf("[%.10.20d]\n", -42);
	printf("%d %d\n\n", a, b);

	/* while (1); */
	return (0);
}
