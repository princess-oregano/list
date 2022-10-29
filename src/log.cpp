#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <stdarg.h>
#include "log.h"

const int MAX_FILE_NAME_SIZE = 100;
// Stream to print log to. Stderr by default.
FILE *LOGSTREAM = stderr;

void
log(const char *format, ...)
{
        va_list arglist;

        va_start(arglist, format);

        vfprintf(LOGSTREAM, format, arglist);

        va_end(arglist);
}

// Prints starting lines to log.
static void
printf_start_log()
{
        time_t rawtime;
        tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);

        log("<pre>\n\n");
        log("<h2>LOG FILE</h2>\n\n");
        log("TIME OF CREATION: %s\n\n", asctime(timeinfo));
        log("------------------------------------------------------------\n\n");
}

static void
print_end_log()
{
        time_t rawtime;
        struct tm * timeinfo;
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );

        log("------------------------------------------------------------\n\n");
        log("END OF LOG FILE\n\n");
        log("TIME OF CLOSURE: %s\n\n", asctime(timeinfo));
}

void
open_log(const char *filename)
{
        LOGSTREAM = fopen(filename, "w");
        if (LOGSTREAM == nullptr) {
                fprintf(stderr, "Couldn't open log file.\n");
                return;
        }

        printf_start_log();
}

FILE *
get_logfile_ptr()
{
        return LOGSTREAM;
}

void
include_graph(const char *path)
{
        FILE *test_ptr = fopen(path, "r");
        if (test_ptr != nullptr) {
                fclose(test_ptr);
        }
        else {
                fprintf(stderr, "Error: file '%s' is invalid.\n", path);
                return;
        }

        log("<img src=%s width = 1200/>\n\n", path);
}

void
close_log()
{
        print_end_log();

        if (LOGSTREAM != nullptr)
                fclose(LOGSTREAM);
        else
                fprintf(stderr, "Error: LOGSTREAM == nullptr.\n");
}

