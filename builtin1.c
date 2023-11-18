#include "shell.h"

/**
 * displayHistory - displays the command history
 * @info: structure
 * Return: 0
 */
int displayHistory(info_t *info)
{
    printList(info->history);
    return (0);
}

/**
 * removeAlias - Removes an alias from the list
 * @info: structure
 * @aliasStr: alias to remove
 * Return: 0 on success else 1
 */
int removeAlias(info_t *info, char *aliasStr)
{
    char *separator;
    int result;

    separator = strchr(aliasStr, '=');
    if (!separator)
        return (1);

    *separator = '\0';
    result = deleteNodeAtIndex(&(info->alias),
                               getNodeIndex(info->alias, nodeStartsWith, aliasStr));
    *separator = '=';

    return (result);
}

/**
 * addAlias - adds an alias to the list
 * @info: structure
 * @aliasStr: alias to add
 * Return: 0 on success else 1
 */
int addAlias(info_t *info, char *aliasStr)
{
    char *separator;

    separator = strchr(aliasStr, '=');
    if (!separator)
        return (1);
    if (!*++separator)
        return (removeAlias(info, aliasStr));
    removeAlias(info, aliasStr);
    return (addNodeEnd(&(info->alias), aliasStr, 0) == NULL);
}

/**
 * printAlias - prints an alias string
 * @node: the alias node
 * Return: 0 on success else 1
 */
int printAlias(list_t *node)
{
    char *separator, *alias;

    if (node)
    {
        separator = strchr(node->str, '=');
        for (alias = node->str; alias <= separator; alias++)
            _putchar(*alias);

        _putchar('\'');
        _puts(separator + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * manageAliases - manage alias functionality
 * @info: structure
 * Return: 0
 */
int manageAliases(info_t *info)
{
    int i;
    char *separator;

    if (info->argc == 1)
    {
        list_t *node = info->alias;

        while (node)
        {
            printAlias(node);
            node = node->next;
        }
        return (0);
    }
    for (i = 1; info->argv[i]; i++)
    {
        separator = strchr(info->argv[i], '=');
        if (separator)
            addAlias(info, info->argv[i]);
        else
            printAlias(nodeStartsWith(info->alias, info->argv[i], '='));
    }
    return (0);
}

