#include "shell.h"

/**
 * getNodeIndex - Gets the index of a node in the list using the provided compare function.
 * @list: Pointer to the list.
 * @compare: Pointer to the comparison function.
 * @prefix: Prefix to compare.
 *
 * Return: Index of the node if found, UINT_MAX otherwise.
 */
unsigned int getNodeIndex(list_t *list, int (*compare)(char *, char *, char *), char *prefix)
{
    unsigned int index = 0;

    while (list)
    {
        if (compare(list->str, prefix, 0))
            return index;

        list = list->next;
        index++;
    }

    return UINT_MAX;  // Not found
}

/**
 * nodeStartSwith - Checks if the node's string starts with the given prefix.
 * @list: Pointer to the list.
 * @prefix: Prefix to check.
 * @n: Maximum number of characters to compare, -1 for the entire string.
 *
 * Return: 1 if the string starts with the prefix, 0 otherwise.
 */
int nodeStartSwith(list_t *list, char *prefix, int n)
{
    if (!list || !list->str || !prefix)
        return 0;

    while (*prefix && (n < 0 || n--))
    {
        if (*prefix != *list->str)
            return 0;

        prefix++;
        list->str++;
    }

    return (*prefix == '\0');
}

/**
 * addNodeEnd - Adds a node to the end of the list.
 * @head: Address of pointer to the head node.
 * @str: String field of the node.
 * @num: Node index used by history.
 *
 * Return: Pointer to the new node.
 */
list_t *addNodeEnd(list_t **head, char *str, int num)
{
    list_t *new_node, *node;

    if (!head)
        return NULL;

    node = *head;
    new_node = malloc(sizeof(list_t));

    if (!new_node)
        return NULL;

    _memset((void *)new_node, 0, sizeof(list_t));
    new_node->num = num;

    if (str)
    {
        new_node->str = _strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return NULL;
        }
    }

    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    else
        *head = new_node;

    return new_node;
}

/**
 * deleteNodeAtIndex - Deletes a node at the given index.
 * @head: Address of pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int deleteNodeAtIndex(list_t **head, unsigned int index)
{
    list_t *node, *prev_node;
    unsigned int i = 0;

    if (!head || !*head)
        return 0;

    if (!index)
    {
        node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return 1;
    }

    node = *head;

    while (node)
    {
        if (i == index)
        {
            prev_node->next = node->next;
            free(node->str);
            free(node);
            return 1;
        }

        i++;
        prev_node = node;
        node = node->next;
    }

    return 0;
}

