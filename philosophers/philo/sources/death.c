#include "../header/philosophers.h"

int	check_death_flag(void)
{

	pthread_mutex_lock(&get_rules()->death);
	if (get_rules()->someone_died == true)
	{
		pthread_mutex_unlock(&get_rules()->death);
		return(1);
	}
	else
	{
		pthread_mutex_unlock(&get_rules()->death);
		return(0);
	}
}

void	print_death(int i)
{
	if (!dead_enough_food(i))
	{
		print_log(&get_rules()->philo[i], "died");
		pthread_mutex_lock(&get_rules()->death);
		get_rules()->someone_died = true;
		get_rules()->philo[i].is_dead = 1;
		pthread_mutex_unlock(&get_rules()->death);
	}
}

void	supervisor(void)
{
	int	i;
	int	j;

	while (!get_rules()->all_ate && !check_death_flag())
	{
		usleep(850);
		i = 0;
		j = 0;
		pthread_mutex_lock(&get_rules()->meals); //lockeamos porque vamos a leer el numero de meals que lleva comidos y no queremos que sobreescriba
		while (i < get_rules()->philo_nb)
		{
			if (check_min_meals(i))
				j++;
			i++;
		}
		pthread_mutex_unlock(&get_rules()->meals);
		if (j == get_rules()->philo_nb)
			set_everyone_ate();
		i = -1;
		while (++i < get_rules()->philo_nb)
			print_death(i);
	}
}
