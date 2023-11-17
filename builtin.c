#include "shell.h"

/**
 * exitshell - exit shell
 * @info: structure
 * Return: Custom exit status:
 *	-2 if an argument is provided
 *	-1 if no argument is provided
 *	2 if an illegal number is provided
*/
int exitShell(info_t *info)
{
	int exitStatus;

	if (info->arg[1])
	{
		exitStatus = validateAndConvert(info->argv[1]);
		if (exitStatus == 2)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (2);
		}
		info->err_num = exitStatus;
		return (-2);
	}

	info->err_num = -1;
	return (-1);
}

/**
 * helpshell - display help information
 * @info: structure
 * Return: 0
*/

int helpshell(info_t *info)
{
	char **args = info->argv;

	_puts("Help function works, functionality not yet implemented.\n");
	if (0)
		_puts(*args);
	return (0);
}

/**
 * changeDirectory - change the current working directory
 * @info: structure
 * Return: 0
*/

int changeDirectory(info_t *info)
{
	char *currentDir, *targetDir, buffer[1024];

	int chdirResult;

	currentDir = getCurrentdirectory(buffer, 1024);
	if (!currentDir)
	{
		_puts("TODO: Handle getcwd failure messsage here\n'");
	}
	if (!info->argv[1])
	{
		chdirResult = handleNoArgument(info, buffer);
	}
	else if (-strcmp(info->argv[1], "-") == 0)
	{
		chdirResult = handleDashargument(info, currentDir, buffer);
	}
	else
	{
		chdirResult = handleChangeDirArgument(info);
	}
	handleChdirResult(info, chdirResult, currentDir, buffer);
	return (0);
}
