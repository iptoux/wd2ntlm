#ifndef WD2NTLM_H
#define WD2NTLM_H

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <limits.h>

#define WD2NTLM_ASSERT assert
#define WD2NTLM_ISET_OUPUT NULL

#define MAX_PATH 256

typedef struct {
    long lines;
    long size;
    char filepath[MAX_PATH];
    char filename[MAX_PATH];
    char extension[MAX_PATH];
} Wd2ntlm_FileInfo;

typedef enum {
    _DEBUG,
    _INFO,
    _WARNING,
    _ERROR,
    _PANIC,
    _DONE,
} Wd2ntlm_LogLevel;

typedef enum {
    WD2NTLM_SQLITE3,
    WD2NTLM_JSON,
    WD2NTLM_CSV,
    WD2NTLM_XLSX,
} Wd2ntlm_OutPutExt;


#define WD2NTLM_DEFAULT_EXT WD2NTLM_SQLITE3

extern Wd2ntlm_LogLevel WD2NTLM_LOGGING;

void wd2ntlm_file_name_of_path(const char *filepath, char *filename);

void wd2ntlm_log(Wd2ntlm_LogLevel level, const char *fmt, ...);

Wd2ntlm_FileInfo wd2ntlm_get_file_information(FILE *file, const char *filepath);

Wd2ntlm_FileInfo wd2ntlm_process_file(const char *filename);

void wd2ntlm_print_file_info(Wd2ntlm_FileInfo fileInfo);

static char *shift(int *argc, char ***argv)
{
    assert(*argc >0);
    char *result = **argv;
    *argv += 1;
    *argc -= 1;
    return result;
}

#endif