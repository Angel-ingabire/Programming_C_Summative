#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#if defined(_WIN32)
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif
#include "scraper.h"

static void usage(const char *prog) {
    fprintf(stderr, "Usage: %s <urls_file> [output_dir]\n", prog);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        usage(argv[0]);
        return 1;
    }

    const char *urls_file = argv[1];
    char *output_dir = ".";
        if (argc >= 3) output_dir = argv[2];

        /* create output directory if it doesn't exist */
        if (output_dir && strcmp(output_dir, ".") != 0) {
    #if defined(_WIN32)
        _mkdir(output_dir);
    #else
        mkdir(output_dir, 0755);
    #endif
        }

    FILE *f = fopen(urls_file, "r");
    if (!f) {
        perror("fopen");
        return 1;
    }

    char line[4096];
    char **urls = NULL;
    int url_count = 0;

    while (fgets(line, sizeof(line), f)) {
        /* trim leading/trailing whitespace */
        char *s = line;
        while (*s == ' ' || *s == '\t') s++;
        char *e = s + strlen(s) - 1;
        while (e >= s && (*e == '\n' || *e == '\r' || *e == ' ' || *e == '\t')) { *e = '\0'; e--; }
        if (*s == '\0') continue;
        urls = realloc(urls, sizeof(char*) * (url_count + 1));
        urls[url_count++] = strdup(s);
    }
    fclose(f);

    if (url_count == 0) {
        fprintf(stderr, "No URLs found in %s\n", urls_file);
        return 1;
    }

    pthread_t *threads = malloc(sizeof(pthread_t) * url_count);
    fetch_args_t **args = malloc(sizeof(fetch_args_t*) * url_count);

    for (int i = 0; i < url_count; ++i) {
        args[i] = malloc(sizeof(fetch_args_t));
        args[i]->url = urls[i]; /* thread will own this string until joined */
        args[i]->index = i + 1;
        args[i]->output_dir = output_dir;

        if (pthread_create(&threads[i], NULL, fetch_url_thread, args[i]) != 0) {
            perror("pthread_create");
            free(args[i]->url);
            free(args[i]);
            threads[i] = 0;
        }
    }

    for (int i = 0; i < url_count; ++i) {
        if (threads[i]) pthread_join(threads[i], NULL);
        if (args[i]) {
            free(args[i]->url);
            free(args[i]);
        }
    }

    free(threads);
    free(args);
    free(urls);

    return 0;
}
