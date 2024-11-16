#include <unistd.h>
#include <stdarg.h>

void	ft_putchar(char c, int *count)
{
	if (*count != -1)
	{
		write(1, &c, 1);
		(*count)++;
	}

}

void	ft_putstr(char *str, int  *count)
{
	int i = 0;
	
	if  (!str)
	{
		ft_putstr("(null)", count);
		return ;
	}
	while (str[i])
	{
		ft_putchar(str[i], count);
		i++;
	}
}

void	ft_putnbr_base(long long nbr, int base, int *count)
{
	char *print = "0123456789abcdef";

	if (*count == -1)
		return;
	if (nbr < 0)
	{
		ft_putchar('-', count);
		if (nbr == -2147483648)
		{
			ft_putstr("2147483648", count);
			return ;
		}
		nbr = -nbr;
	}
	if (nbr >= base)
		ft_putnbr_base((nbr / base), base, count);
	ft_putchar(print[nbr % base], count);
}

int ft_printf(const char *str, ... )
{
	int i = 0;
	int count = 0;
	va_list arg;

	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%'  && str[i + 1])
		{
			i++;
			if (str[i] == 'd')
				ft_putnbr_base(va_arg(arg, int), 10, &count);
			else if (str[i] == 'x')
				ft_putnbr_base(va_arg(arg, unsigned int), 16, &count);
			else if (str[i] == 's')
				ft_putstr(va_arg(arg, char *), &count);
		}
		else
			ft_putchar(str[i], &count);
		i++;
	}
	va_end(arg);
	return (count);
}