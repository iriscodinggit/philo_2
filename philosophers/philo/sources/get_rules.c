#include "../header/philosophers.h"

t_rules	*get_rules(void)
{
	static t_rules	rules;

	return (&rules);
}
