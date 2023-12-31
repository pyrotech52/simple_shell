#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command
 * @info: The info struct
 * @path: Path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
    struct stat st;

    (void)info;
    if (!path || stat(path, &st) != 0)
        return 0;

    return S_ISREG(st.st_mode);
}

/**
 * dup_chars - Duplicates characters from a string within a range
 * @pathstr: The PATH string
 * @start: Starting index
 * @stop: Stopping index
 *
 * Return: Pointer to the new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
    static char buf[1024];
    int k = 0;

    for (int i = start; i < stop && pathstr[i] != ':'; i++)
    {
        buf[k++] = pathstr[i];
    }
    buf[k] = '\0';

    return buf;
}

/**
 * find_path - Finds the full path of a command in the PATH string
 * @info: The info struct
 * @pathstr: The PATH string
 * @cmd: The command to find
 *
 * Return: Full path of the command if found, otherwise NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    if (!pathstr)
        return NULL;

    if (_strlen(cmd) > 2 && starts_with(cmd, "./") && is_cmd(info, cmd))
    {
        return cmd;
    }

    int i = 0, curr_pos = 0;
    char *path = NULL;

    while (pathstr[i])
    {
        if (pathstr[i] == ':')
        {
            path = dup_chars(pathstr, curr_pos, i);

            if (*path != '\0')
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }
            else
            {
                _strcpy(path, cmd);
            }

            if (is_cmd(info, path))
            {
                return path;
            }

            curr_pos = i + 1;
        }

        i++;
    }

    return NULL;
}

