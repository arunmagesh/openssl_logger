#define _GNU_SOURCE
#include <dlfcn.h>
#include <openssl/ssl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*SSL_write_type)(SSL *ssl, const void *buf, int num);
typedef int (*SSL_read_type)(SSL *ssl, void *buf, int num);

static SSL_write_type real_SSL_write = NULL;
static SSL_read_type real_SSL_read = NULL;
static FILE *log_file = NULL;

static void initLogFile() {
    if (!log_file) {
        log_file = fopen("ssl_traffic.log", "w");
        if (!log_file) {
            perror("Failed to open log file");
            exit(1);
        }
    }
}

int SSL_write(SSL *ssl, const void *buf, int num) {
    initLogFile();

    int result = real_SSL_write(ssl, buf, num);

    if (result > 0) {
        fprintf(log_file, "Sent Data:\n");
        fwrite(buf, 1, result, log_file);
        fprintf(log_file, "\n");
    }

    return result;
}

int SSL_read(SSL *ssl, void *buf, int num) {
    initLogFile();

    int result = real_SSL_read(ssl, buf, num);

    if (result > 0) {
        fprintf(log_file, "Received Data:\n");
        fwrite(buf, 1, result, log_file);
        fprintf(log_file, "\n");
    }

    return result;
}

__attribute__((constructor))
void init() {
    real_SSL_write = dlsym(RTLD_NEXT, "SSL_write");
    real_SSL_read = dlsym(RTLD_NEXT, "SSL_read");
}
