#include "../include/philo.h"

void    good_usleep(long usec)
{
	long	start;
	long	elapsed;
	long	rem;

	start = time_control(US);
	while (time_control(US) - start < usec)
	{
		elapsed = time_control(US) - start;
		rem = usec - elapsed;
		if (rem > 1e3) // Uso pasivo de CPU
			usleep(rem / 2);
		else
		{
			while (time_control(US) - start < usec) // Spinlock: uso activo de CPU para + precisión
				;
		}
	}
}

int main(void)
{
	struct timeval start, end;
	long elapsed_us, elapsed_ms;

	// Tiempo inicial
	gettimeofday(&start, NULL);

	// Dormir por 2000 microsegundos (2 milisegundos)
	usleep(200000);

	// Tiempo final
	gettimeofday(&end, NULL);

	// Calcular diferencia en microsegundos
	elapsed_us = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
	elapsed_ms = (end.tv_sec - start.tv_sec) * 1000L + (end.tv_usec - start.tv_usec) / 1000L;

	printf("usleep(2000) tardó aproximadamente: %ld microsegundos (%ld milisegundos)\n\n", elapsed_us, elapsed_ms);

	// Tiempo inicial
	gettimeofday(&start, NULL);

	// Dormir por 2000 microsegundos (2 milisegundos)
	precise_usleep(200000);
	
	// Tiempo final
	gettimeofday(&end, NULL);
	
	// Calcular diferencia en microsegundos
	elapsed_us = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
	elapsed_ms = (end.tv_sec - start.tv_sec) * 1000L + (end.tv_usec - start.tv_usec) / 1000L;
	
	printf("usleep(2000) tardó aproximadamente: %ld microsegundos (%ld milisegundos)\n", elapsed_us, elapsed_ms);

	return 0;
}
