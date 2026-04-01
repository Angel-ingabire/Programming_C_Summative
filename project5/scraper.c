#include "scraper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* If libcurl is available, define HAVE_LIBCURL when compiling (e.g. -DHAVE_LIBCURL)
    Otherwise a lightweight fallback stub is used so the project builds without network. */
#ifdef HAVE_LIBCURL
#include <curl/curl.h>
#endif

struct memory_chunk {
    char *memory;
    size_t size;
};

#ifdef HAVE_LIBCURL
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct memory_chunk *mem = (struct memory_chunk *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        return 0; /* out of memory -> abort transfer */
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

void *fetch_url_thread(void *arg)
{
    fetch_args_t *a = (fetch_args_t *)arg;
    struct memory_chunk chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    CURL *curl = curl_easy_init();
    if (!curl) {
        char fname[1024];
        snprintf(fname, sizeof(fname), "%s/output_%d.err.txt", a->output_dir, a->index);
        FILE *f = fopen(fname, "w");
        if (f) {
            fprintf(f, "ERROR: failed to initialize CURL for URL: %s\n", a->url);
            fclose(f);
        }
        free(chunk.memory);
        return NULL;
    }

    curl_easy_setopt(curl, CURLOPT_URL, a->url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "project5-mt-scraper/1.0");
    /* reasonable per-request timeout (seconds) */
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);

    CURLcode res = curl_easy_perform(curl);

    char outname[1024];
    snprintf(outname, sizeof(outname), "%s/output_%d.html", a->output_dir, a->index);
    FILE *out = fopen(outname, "wb");
    if (!out) {
        /* try writing an error file */
        char errname[1024];
        snprintf(errname, sizeof(errname), "%s/output_%d.err.txt", a->output_dir, a->index);
        FILE *e = fopen(errname, "w");
        if (e) {
            fprintf(e, "ERROR: failed to open output file '%s' for writing.\n", outname);
            if (res != CURLE_OK) fprintf(e, "CURL error: %s\n", curl_easy_strerror(res));
            fclose(e);
        }
    } else {
        if (res != CURLE_OK) {
            fprintf(out, "ERROR fetching URL %s:\n%s\n", a->url, curl_easy_strerror(res));
        } else {
            fwrite(chunk.memory, 1, chunk.size, out);
        }
        fclose(out);
    }

    curl_easy_cleanup(curl);
    free(chunk.memory);

    return NULL;
}
#else
/* Fallback stub when libcurl is not available: write a simple placeholder file. */
void *fetch_url_thread(void *arg)
{
    fetch_args_t *a = (fetch_args_t *)arg;
    char outname[1024];
    snprintf(outname, sizeof(outname), "%s/output_%d.html", a->output_dir, a->index);
    FILE *out = fopen(outname, "w");
    if (!out) {
        char errname[1024];
        snprintf(errname, sizeof(errname), "%s/output_%d.err.txt", a->output_dir, a->index);
        FILE *e = fopen(errname, "w");
        if (e) {
            fprintf(e, "ERROR: failed to open output file '%s' for writing.\n", outname);
            fclose(e);
        }
        return NULL;
    }
    fprintf(out, "STUB: libcurl not available. URL: %s\n", a->url ? a->url : "(null)");
    fclose(out);
    return NULL;
}
#endif
