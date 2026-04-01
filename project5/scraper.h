#ifndef SCRAPER_H
#define SCRAPER_H

#include <pthread.h>

typedef struct fetch_args {
    char *url;          /* URL to fetch (ownership transferred to thread) */
    int index;          /* 1-based index used for output filename */
    char *output_dir;   /* directory to save output (not owned) */
} fetch_args_t;

/* Thread entry point: fetches the URL and writes output to a file. */
void *fetch_url_thread(void *arg);

#endif /* SCRAPER_H */
