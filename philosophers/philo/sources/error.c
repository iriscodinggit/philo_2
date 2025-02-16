#include "../header/philosophers.h"

bool	write_error(char *str)
{
	int length;

	length = 0;
	while (str[length])
	{
		length++;
	}
	write(2, str, length); // 2 is the file descriptor for stderr
	return (length);
}