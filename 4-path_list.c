#include "shell.h"

typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;

char *_getenv(const char *name)
{
	extern char **environ;
	const char *token;
	char *result = malloc(sizeof(char) * 256);

	while(*environ)
	{
		token = strtok(*environ, "=");
		while(token)
		{
			if (strcmp(name, token) == 0)
			{
				token = strtok(NULL, "=");
				strcpy(result, token);
				return (result);
			}
			token = strtok(NULL, "=");
		}
		environ++;
	}
	return ("unable to locate requested environmental variable\n");
}

list_t *add_node_end(list_t **head, const char *str)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *temp_node;

	if (!new_node)
		return (NULL);

	new_node->str = strdup(str);
	new_node->len = strlen(str);
	new_node->next = NULL;

	if (!*head)
		*head = new_node;
	else
	{
		temp_node = *head;
		while (temp_node->next)
			temp_node = temp_node->next;

		temp_node->next = new_node;
	}
	return (new_node);
}

size_t print_list(const list_t *h)
{
	size_t len = 0;

	while (h)
	{
		printf("[%u] %s\n", h->len, h->str);
		h = h->next; len++;
	}
	return (len);
}
char *exebuiltin(char *file, const list_t *h)
{
	unsigned int i;
	struct stat st;
	char *path;
	while (h)
	{
		path = malloc(sizeof(char) * (strlen(file) + strlen(h->str)));
/*		strcat("/", file);
*/		path = strcat(h->str, file);
		if (stat(path, &st) == 0)
		{
			printf("found %s\n", path);
			return (path);
		}
		else
			printf("not found %s\n", path);
		h = h->next;
	}
	free(path);
	return("fail");
}
int  main(int ac, char **av)
{
	list_t *head = NULL;
	char *path = _getenv("PATH");
	char *token;
	char *file;
	unsigned int i = 1;
	if (!path)
		return (-1);

	token = strtok(path, ":");

	while (token)
	{
		add_node_end(&head, token);
		token = strtok(NULL, ":");
	}
/*	while (ac != 0)
	(
*		exebuiltin(av[i], head);
*		ac--;
	}
*/
	exebuiltin(av[1], head);
	return (0);
}