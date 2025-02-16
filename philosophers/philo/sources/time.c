#include "../header/philosophers.h"

/*void	get_time(t_time *time)
{
	struct timeval		tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		generic_err("🍝 Ups! Could not get the current time!");
		return ;
	}
	time->millisecs = (tv.tv_sec * 1000)
			+ (tv.tv_usec / 1000);
	time->microsecs = (tv.tv_sec * 1000000) + tv.tv_usec;
}*/

/*long	get_time_ms(void)
{
	t_time	time;

	get_time(&time, 1);
	return (time.millisecs);
}*/

long	get_time_ms(long *time, int returning)
{
	//maybe there is a prob with norminette with the return value -1 if it doesn't receive anything
	struct timeval		tv;
	long	millisecs;

	if (gettimeofday(&tv, NULL) == -1)
	{
		write_error("🍝 Ups! Could not get the current time!");
		return -1;
	}
	millisecs = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (time)
        *time = millisecs;
	if(returning == 1)
		return (millisecs);
	return -1;
}

void	get_time_mutex(long *time)
{
	pthread_mutex_lock(&get_rules()->time);
	get_time_ms(time, 0);
	pthread_mutex_unlock(&get_rules()->time);
}

long	time_passed(long *start, long *current)
{
	long	elapsed;

		elapsed = *current - *start;
		return (elapsed);
}

void	wait_time(long action_time)
{
	long	current_time;
	long	start;

	get_time_mutex(&start); //guarda la hora actual
	while (true) //se ejecuta hasta que se cumpla el if de dentro
	{
		usleep(245); //pausa 250 microsegundos, probar otro valor o ver comentario para otra modificación
		
		get_time_mutex(&current_time); //guarda la hora actual pero en otra variable
		if ((current_time- start) >= action_time) //cuando se haya acabado el tiempo que tenía para morir/comer, para el while y vuelve a one_philo/eat
			break ;
	}
}