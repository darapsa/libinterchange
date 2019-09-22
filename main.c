#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <icclient/client.h>

int main(void)
{
	char *url_line = NULL, *name_line = NULL, *pass_line = NULL;
	printf("URL: ");
	ssize_t url_nread = getline(&url_line, &(size_t){0}, stdin);
	printf("Name: ");
	ssize_t name_nread = getline(&name_line, &(size_t){0}, stdin);
	printf("Pass: ");
	ssize_t pass_nread = getline(&pass_line, &(size_t){0}, stdin);

	char *url = malloc(--url_nread + 1), *name = malloc(--name_nread + 1)
		, *pass = malloc(--pass_nread + 1);
	strncpy(url, url_line, url_nread);
	free(url_line);
	strncpy(name, name_line, name_nread);
	free(name_line);
	strncpy(pass, pass_line, pass_nread);
	free(pass_line);

	icclient_init(url);
	free(url);

	icclient_login(name, pass, "member/home", NULL, NULL);
	free(name);
	free(pass);

	icclient_logout();
	icclient_cleanup();
}
