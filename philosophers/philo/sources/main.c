#include "../header/philosophers.h"

int	main(int ac, char **argv)
{
	if (ac < 5 || ac > 6)
		return (write_error("🍝 Ups! Please input 5 to 6 arguments."));
	if (start_simulation(argv) == false)
		return (1);
	return (0);
}