#include "shell.h"

/**
 * displayEnvironment - prints the current environment
 * @info: structures
 * Return: 0
*/
int displayEnvironment(info_t *info)
{
	printEnvironmentList(info->env);
	return (0);
}

/**
 * _getEnv - gets the value of an environmental variable
 * @info: structure
 * @name: name of the environmental variable
 * Return: the value of the environment variable
*/
char *_getEnv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *value;

	while (node)
	{
		value = startsWith(node->str, name);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}


/**
 * _setEnvR - inializes or modifies an environtal variable
 * @info: structure
 * Return: 0 on success else 1
*/

int _setEnvR(info_t *info)
{
	if (info->argc != 3)
	{
		printError("Incorrect number of arguments\n");
		return (1);
	}
	if (setEnvvariable(info, info->argv[1], info->argv[2]) == 0)
		return (0);
	return (1);
}

/**
 * unsetEnvR - removes an environt variable
 * @info: structure
 * Return: 0 on success else 1
*/
int unsetEnvR(info_t *info)
{
	if (info->argc == 1)
	{
		printError("Too few arguments\n");
		return (1);
	}
	for (int i = 1; i <= info->argc; i++)
		unsetEnvVariable(info, info->argc[i]);
	return (0);
}

/**
 * populateEnv_list - populates environment linked list
 * @info: structure
 * Return: 0
*/

int populateEnv_list(info_t *info)
{
	list_t *node = NULL;

	for (size_t i = 0; environ[i]; i++)
		addNodeEnd(&node, environ[i], 0);
	info->env = node;
	return (0);
}
