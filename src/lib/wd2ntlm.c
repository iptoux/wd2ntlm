#include "wd2ntlm.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

Wd2ntlm_LogLevel WD2NTLM_LOGGING = _INFO;

void wd2ntlm_log(Wd2ntlm_LogLevel level, const char *fmt, ...)
{
    if (level >= WD2NTLM_LOGGING) {
        switch (level) {
        case _DEBUG:
            //if (WD2NTLM_LOGGING <= _DEBUG) {
            fprintf(stdout, "[DEBUG] ");   
            //}
            break;
        case _INFO:
            fprintf(stdout, "[INFO]  ");
            break;
        case _WARNING:
            fprintf(stdout, "[WARNING] ");
            break;
        case _ERROR:
            fprintf(stdout, "[ERROR] ");
            break;
        case _PANIC:
            fprintf(stdout, "[PANIC] ");
            break;
        case _DONE:
            fprintf(stdout, "[DONE]  ");
            break;    
        default:
            WD2NTLM_ASSERT(0 && "unreachable");
        }

        va_list args;
        va_start(args, fmt);
        vfprintf(stdout, fmt, args);
        va_end(args);
        fprintf(stdout, "\n");
    }
}

void wd2ntlm_file_name_of_path(const char *filepath, char *filename) {
    // Find the last occurrence of the directory separator
    const char *lastSeparator = strrchr(filepath, '/');
    
    // Check if the filepath contains a directory separator
    if (lastSeparator != NULL) {
        // Copy the substring after the last separator to the filename
        strcpy(filename, lastSeparator + 1);
    } else {
        // If there is no directory separator, the filepath is the filename
        strcpy(filename, filepath);
    }
}

Wd2ntlm_FileInfo wd2ntlm_get_file_information(FILE *file, const char *filepath) {
    wd2ntlm_log(_DEBUG,"Getting file informations...");
    Wd2ntlm_FileInfo fileInfo;
    fileInfo.lines = 0;
    fileInfo.size = 0;


 // Get the absolute path of the file
    char resolvedPath[MAX_PATH];
    if (realpath(filepath, resolvedPath) == NULL) {
        perror("Error getting absolute path");
        fileInfo.lines = -1; // Indicate an error
        return fileInfo;
    }

    // Extract filename and extension from the path
    const char *lastSlash = strrchr(resolvedPath, '/');
    const char *filename = (lastSlash != NULL) ? lastSlash + 1 : resolvedPath;

    const char *lastDot = strrchr(filename, '.');
    const char *basename = (lastDot != NULL) ? lastDot + 1 : filename;

    snprintf(fileInfo.filepath, MAX_PATH, "%s", resolvedPath);
    snprintf(fileInfo.filename, MAX_PATH, "%s", filename);
    snprintf(fileInfo.extension, MAX_PATH, "%s", basename);

    // Count lines and calculate file size
    rewind(file);
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            fileInfo.lines++;
        }
        fileInfo.size++;
    }

    return fileInfo;
}

Wd2ntlm_FileInfo wd2ntlm_process_file(const char *filename) {
    Wd2ntlm_FileInfo fileInfo;
    wd2ntlm_log(_DEBUG,"Open file: %s", filename);
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        fileInfo.lines = -1; // Indicate an error
        return fileInfo;
    }

    fileInfo = wd2ntlm_get_file_information(file, filename);

    // Close the file
    fclose(file);

    return fileInfo;
}

void wd2ntlm_print_file_info(Wd2ntlm_FileInfo fileInfo) {
    const char *units[] = {"Bytes", "KB", "MB", "GB", "TB"};
    double size = (double)fileInfo.size;
    int unitIndex = 0;

    while (size >= 1024 && unitIndex < 4) {
        size /= 1024;
        unitIndex++;
    }

    wd2ntlm_log(_INFO,"+ File Information:");
    wd2ntlm_log(_DEBUG,"  + Path: %s", fileInfo.filepath);
    wd2ntlm_log(_INFO,"  + Filename: %s", fileInfo.filename);
    wd2ntlm_log(_DEBUG,"  + Extension: %s", fileInfo.extension);
    wd2ntlm_log(_INFO,"  + Lines: %ld", fileInfo.lines);
    wd2ntlm_log(_DEBUG,"  + Size: %.2f %s", size, units[unitIndex]);
}
