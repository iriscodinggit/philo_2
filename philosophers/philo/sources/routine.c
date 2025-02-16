#include "../header/philosophers.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_log(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_log(philo, "has taken a fork");
	print_log(philo, "is eating");
	pthread_mutex_lock(&get_rules()->meals);
	get_time_ms(&philo->last_meal, 0);
	pthread_mutex_unlock(&get_rules()->meals);
	wait_time(get_rules()->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&get_rules()->meals);
	philo->nb_of_meals++;
	pthread_mutex_unlock(&get_rules()->meals);
}

static void	zzz(t_philo *philo)
{
	print_log(philo, "is sleeping");
	wait_time(get_rules()->time_to_sleep);
}

static void	think(t_philo *philo)
{
	print_log(philo, "is thinking");
	if (get_rules()->philo_nb % 2 != 0)
		usleep((get_rules()->time_to_eat) * 1000); //para convertir a miliseconds multiplico por 1000
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (get_rules()->philo_nb == 1 && forever_alone((t_philo *)arg))
		return (NULL);
	pthread_mutex_lock(&get_rules()->meals);
	get_time_ms(&philo->last_meal, 0);
	pthread_mutex_unlock(&get_rules()->meals);
	if (philo->index % 2 != 0)
		usleep(10000);
	while (!read_everyone_ate() && !check_death_flag())
	{
		eat((t_philo *)arg);
		zzz((t_philo *)arg);
		think((t_philo *)arg);
	}
	return (NULL);
}