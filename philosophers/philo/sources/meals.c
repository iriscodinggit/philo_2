#include "../header/philosophers.h"

bool	check_min_meals(int i)
{
	if (get_rules()->min_meals== -1) //if the user didn't specify max number of meals, return
		return (false);
	if (get_rules()->philo[i].nb_of_meals >= get_rules()->min_meals) //if he ate enough times, return true
		return (true);
	return (false);
}

bool	dead_enough_food(int i)
{
	long	time;
	//puede haber problemas con norminette si no inicializo time fuera del if

	pthread_mutex_lock(&get_rules()->time); //necesitamos el lock porque si no, si hay data race el resultado de get_time_ms lo puede conseguir 5 seg mas tarde (exageración) y no ser preciso
	pthread_mutex_lock(&get_rules()->meals); //y aquí lo necesitamos porque puede coger mal la hora de la última vez que comió (aunque esto no estoy tan segura porque va por índices [i]) da igual que vaya por indices, aunque sea un recurso propio del philo indiviudal, puede llamar otra función tmbn al indice
	if ((get_time_ms(&time, 1) - get_rules()->philo[i].last_meal) > get_rules()->time_to_die) 
	{
		pthread_mutex_unlock(&get_rules()->meals);
		pthread_mutex_unlock(&get_rules()->time);
		if (check_min_meals(i))
			return (true);
		return (false);
	}
	pthread_mutex_unlock(&get_rules()->meals);
	pthread_mutex_unlock(&get_rules()->time);
	return (true);
}

bool	read_everyone_ate(void)
{
	if (get_rules()->min_meals == -1)
		return (false);
	pthread_mutex_lock(&get_rules()->all_ate_mutex);
	if (get_rules()->all_ate)
	{
		pthread_mutex_unlock(&get_rules()->all_ate_mutex);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&get_rules()->all_ate_mutex);
		return (false);
	}
}

void	set_everyone_ate(void)
{
	pthread_mutex_lock(&get_rules()->all_ate_mutex);
	get_rules()->all_ate = true;
	pthread_mutex_unlock(&get_rules()->all_ate_mutex);
}