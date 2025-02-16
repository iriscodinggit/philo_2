#include "../header/philosophers.h"

void	stop_simulation(int philo_nb) //should take an int (philo nb when called from main or i (number of philos created so far) when called from init_threads
{
	
	int	i;

	i = 0;

	while (i < philo_nb) //repite el ciclo una vez por cada filo creado
	{
		pthread_join(get_rules()->philo[i].id, NULL); //joinea los threads para liberar recursos de memoria
		i++;
	}
	i = 0;
	while (i < philo_nb) //repite una vez por filo
	{
		pthread_mutex_destroy(&get_rules()->forks[i]); //Destruye los mutexes de los forks
		i++;
	}
	pthread_mutex_destroy(&get_rules()->print); 
	pthread_mutex_destroy(&get_rules()->death);
	pthread_mutex_destroy(&get_rules()->meals);
	pthread_mutex_destroy(&get_rules()->time);
	pthread_mutex_destroy(&get_rules()->all_ate_mutex);
	free(get_rules()->forks); //libera el array de los mutexes de fork (antes solo se habían destuido los mutexes como tal, ahora liberamos la memoria de malloc)
	free(get_rules()->philo); //libera las structs
}