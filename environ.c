#include "shell.h"

/**
 * _myenv - PRINT current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function Prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}
/**
 * _getenv - GETS value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *m;

	while (node)
	{
		m = starts_with(node->str, name);
		if (m && *m)
			return (m);
		node = node->next;
	}
	return (NULL);
}
/**
 * _mysetenv - INITIATE a new environment variable,
 *             or Modify an Existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
/**
 * _myunsetenv - To Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int q;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (q = 1; i <= info->argc; ++q)
		_unsetenv(info, info->argv[q]);

	return (0);
}
/**
 * populate_env_list -POPULATE env linked LIST
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function Prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t q;

	for (q = 0; environ[q]; ++q)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
