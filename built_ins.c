#include "shell.h"

/**
 * change_directory - calls cd built-in
 * @args: arguments received at getline
 * @info: pointer to info_t struct
 * Return: 0 on success, -1 on failure
 */
int change_directory(char **args, info_t *info)
{
	char *old_cwd, *home, *token;

	token = args[1];
	old_cwd = getcwd(NULL, 100);
	home = (_getenv("HOME", info->env_head))->value;

	if (!token)
	{
		chdir(home);
		_setenv("PWD", home, info->env_head);
		_setenv("OLDPWD", old_cwd, info->env_head);
		free(old_cwd);
		return (1);
	}
	if (token[0] == '-' && token[1] == '\0')
	{
		if (!(_getenv("OLDPWD", info->env_head)))
		{
			_puts("env var OLDPWD has no value\n");
			free(old_cwd);
			return (0);
		}
		token = _getenv("OLDPWD", info->env_head)->value;
		_puts(token);
	}
	if (chdir(token) == -1)
	{
		perror("Error");
		free(old_cwd);
		return (-1);
	}
	_setenv("PWD", token, info->env_head);
	_setenv("OLDPWD", old_cwd, info->env_head);
	free(old_cwd);
	return (0);
}

/**
 * exit_shell - frees allocated memory and exits shell
 * @exit_status: number representing exit status
 * @args:  arguments received by getline
 * @info: shell information struct
 */
void exit_shell(char *exit_status, char **args, info_t *info)
{
	int i;

	if (exit_status != NULL)
		i = _atoi(exit_status);
	else
		i = 0;

	free(args);
	free(info->line);
	free_path_list(info->path_head);
	free_env_list(info->env_head);
	free_history(info->hist_head);
	free(info);
	exit(i);
}

/**
 * print_env - prints the current environment
 * @head: pointer to first node in env_t struct
 * @info: pointer to info_t struct
 * Return: 0 on success;  -1 otherwise
 */
int print_env(env_t **head, __attribute__((__unused__))info_t *info)
{
	env_t *temp_node = *head;

	while (temp_node->next)
	{
		temp_node = temp_node->next;
		write(STDOUT_FILENO, temp_node->name, _strlen(temp_node->name));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, temp_node->value, _strlen(temp_node->value));
		_putchar('\n');
	}
	return (0);
}

/**
 * print_history - prints command history
 * @head: pointer to first node in hist_t list
 * Return: void
 */
void print_history(hist_t **head)
{
	hist_t *temp_node = *head;

	while(head)
	{
		print_unsigned_int(temp_node->index);
		_putchar('\t');
		write(STDOUT_FILENO, temp_node->cmd, _strlen(temp_node->cmd));
		/* _putchar('\n'); */
		if (temp_node->next)
		{
			temp_node = temp_node->next;
		}
		else
			break;
	}
}
