#include <unistd.h>

/**
* main - hello world
* Return: 0 on success
*/
int main(void)

{
	write(1, "Hello, World!\n", 15);
	return (0);
}
