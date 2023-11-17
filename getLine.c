#include "shell.h"

/**
 * input_buffer - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buffer(info_t *info, char **buf, size_t *len)
{
    ssize_t bytes_read = 0;
    size_t buffer_len = 0;

    if (!*len) /* if nothing left in the buffer, fill it */
    {
        /*bfree((void **)info->cmd_buf);*/
        free(*buf);
        *buf = NULL;
        signal(SIGINT, sigintHandler);
#if USE_GETLINE
        bytes_read = getline(buf, &buffer_len, stdin);
#else
        bytes_read = _getline(info, buf, &buffer_len);
#endif
        if (bytes_read > 0)
        {
            if ((*buf)[bytes_read - 1] == '\n')
            {
                (*buf)[bytes_read - 1] = '\0'; /* remove trailing newline */
                bytes_read--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);
            /* if (_strchr(*buf, ';')) is this a command chain? */
            {
                *len = bytes_read;
                info->cmd_buf = buf;
            }
        }
    }
    return bytes_read;
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
    static char *buffer; /* the ';' command chain buffer */
    static size_t current_position, chain_start, buffer_len;
    ssize_t bytes_read = 0;
    char **buffer_ptr = &(info->arg), *current_command;

    _putchar(BUF_FLUSH);
    bytes_read = input_buffer(info, &buffer, &buffer_len);
    if (bytes_read == -1) /* EOF */
        return -1;
    if (buffer_len) /* we have commands left in the chain buffer */
    {
        chain_start = current_position; /* init new iterator to current buffer position */
        current_command = buffer + current_position; /* get pointer for return */

        check_chain(info, buffer, &chain_start, current_position, buffer_len);
        while (chain_start < buffer_len) /* iterate to semicolon or end */
        {
            if (is_chain(info, buffer, &chain_start))
                break;
            chain_start++;
        }

        current_position = chain_start + 1; /* increment past nulled ';'' */
        if (current_position >= buffer_len) /* reached end of buffer? */
        {
            current_position = buffer_len = 0; /* reset position and length */
            info->cmd_buf_type = CMD_NORM;
        }

        *buffer_ptr = current_command; /* pass back pointer to current command position */
        return _strlen(current_command); /* return length of current command */
    }

    *buffer_ptr = buffer; /* else not a chain, pass back buffer from _getline() */
    return bytes_read; /* return length of buffer from _getline() */
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @len: size
 *
 * Return: bytes read
 */
ssize_t read_buffer(info_t *info, char *buf, size_t *len)
{
    ssize_t bytes_read = 0;

    if (*len)
        return 0;
    bytes_read = read(info->readfd, buf, READ_BUF_SIZE);
    if (bytes_read >= 0)
        *len = bytes_read;
    return bytes_read;
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: bytes read
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t current_position, buffer_len;
    size_t k;
    ssize_t bytes_read = 0, total_bytes = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        total_bytes = *length;
    if (current_position == buffer_len)
        current_position = buffer_len = 0;

    bytes_read = read_buffer(info, buf, &buffer_len);
    if (bytes_read == -1 || (bytes_read == 0 && buffer_len == 0))
        return -1;

    c = _strchr(buf + current_position, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : buffer_len;
    new_p = _realloc(p, total_bytes, total_bytes ? total_bytes + k : k + 1);
    if (!new_p) /* MALLOC FAILURE! */
        return p ? free(p), -1 : -1;

    if (total_bytes)
        _strncat(new_p, buf + current_position, k - current_position);
    else
        _strncpy(new_p, buf + current_position, k - current_position + 1);

    total_bytes += k - current_position;
    current_position = k;
    p = new_p;

    if (length)
        *length = total_bytes;
    *ptr = p;
    return total_bytes;
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}

