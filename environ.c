#include "shell.h"

/**
 * displayEnvironment - prints the current environment
 * @info: structure
 * Return: 0
 */
int displayEnvironment(info_t *info)
{
    printEnvironmentList(info->env);
    return 0;
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
            return value;
        node = node->next;
    }
    return NULL;
}

/**
 * _setEnvVariable - initializes or modifies an environmental variable
 * @info: structure
 * Return: 0 on success else 1
 */
int _setEnvVariable(info_t *info)
{
    if (info->argc != 3)
    {
        printError(info, "Incorrect number of arguments\n");
        return 1;
    }

    if (setEnvVariable(info, info->argv[1], info->argv[2]) == 0)
        return 0;

    return 1;
}

/**
 * unsetEnvR - removes an environmental variable
 * @info: structure
 * Return: 0 on success else 1
 */
int unsetEnvR(info_t *info)
{
    if (info->argc == 1)
    {
        printError(info, "Too few arguments\n");
        return 1;
    }

    for (int i = 1; i < info->argc; i++)
        unsetEnvVariable(info, info->argv[i]);

    return 0;
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
    return 0;
}

/**
 * nodeStartsWith - finds a node in the list that starts with the specified prefix
 * @list: the list to search
 * @prefix: the prefix to match
 * @n: length of the prefix
 * Return: pointer to the matching node or NULL if not found
 */
list_t *nodeStartsWith(list_t *list, char *prefix, int n)
{
    while (list)
    {
        if (startsWith(list->str, prefix) == list->str)
            return list;
        list = list->next;
    }

    return NULL;
}

