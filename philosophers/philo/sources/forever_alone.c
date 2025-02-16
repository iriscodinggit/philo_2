#include "../header/philosophers.h"

bool	forever_alone(t_philo *philo)
{
	print_log(philo, "has taken a fork");
	wait_time(get_rules()->time_to_die);
	death_one_philo(philo);
	return (true);
}

int		death_one_philo(t_philo *philo) //sería necesario hacer locks aquí si solo hay un thread? quitar y probar hellgrind en el otro ordenador
{
	long			current_time;
	long			elapsed;

	get_time_mutex(&current_time);
	elapsed = time_passed(&philo->last_meal, &current_time);
	if (elapsed >= get_rules()->time_to_die)
	{
		print_log(philo, "died");
		philo->is_dead = 1;
		pthread_mutex_lock(&get_rules()->death);
		get_rules()->someone_died = true;
		pthread_mutex_unlock(&get_rules()->death);
		return (1);
	}
	pthread_mutex_lock(&get_rules()->death);
	if (get_rules()->someone_died == true)
	{
		pthread_mutex_unlock(&get_rules()->death);
		return(1);
	}
	return (0);
}