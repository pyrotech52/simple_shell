#include "shell.h"

/**
 * main - entry point for the shell
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 else 1
*/

int main(int argc, char **argv)
{
info_t shell_info = INFO_INIT;
int file_descriptor = STDERR_FILENO;
if (argc == 2)
{
int fd = open(argv[1], O_RDONLY);
if (fd == -1)
{

handle_file_open_error(argv);
}
else
{
shell_info.readfd = fd;
}
}
populate_and_read_history(&shell_info, argv);
return (EXIT_SUCCESS);
}
