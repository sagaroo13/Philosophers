#include "../include/philo.h"

// void    good_usleep(long usec)
// {
// 	long	start;
// 	long	elapsed;
// 	long	rem;

// 	start = time_control(US);
// 	while (time_control(US) - start < usec)
// 	{
// 		elapsed = time_control(US) - start;
// 		rem = usec - elapsed;
// 		if (rem > 1e3) // Uso pasivo de CPU
// 			usleep(rem / 2);
// 		else
// 		{
// 			while (time_control(US) - start < usec) // Spinlock: uso activo de CPU para + precisión
// 				;
// 		}
// 	}
// }

int main(void)
{
	int i = 0;

	while (i < 10)
	{
		printf("%d\n", i);
		i += 20;
		printf("%d\n", i);
	}
	return 0;
}
