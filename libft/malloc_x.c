#include "libft.h"

void	*malloc_x(size_t bytes)
{
	void	*return_value;

	return_value = malloc(bytes);
	if (!return_value)
		exit(42);
	return (return_value);
}
