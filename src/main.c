#include "lib/wd2ntlm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void usage(FILE *stream, const char *program)
{
    fprintf(stream, "Usage: wd2ntlm <intput> [OPTIONS] [FORMAT]\n");
    fprintf(stream, "OPTIONS:\n");
    fprintf(stream, "   -d              Debug Log Information\n");
    fprintf(stream, "   -o <output>     Provide output path\n");
    fprintf(stream, "   -h              Print this help to stdout\n\n");
    fprintf(stream, "FORMATS:\n");
    fprintf(stream, "   --json          Outputs in JSON format\n");
    fprintf(stream, "   --xlsx          Outputs in XLSX format\n");
    fprintf(stream, "   --csv           Ouptuts in CSV format\n");
}


int main(int argc, char **argv) {

    WD2NTLM_LOGGING = _INFO;
    wd2ntlm_log(_INFO, "--- STAGE 1 ---");

    const char * const program = shift(&argc, &argv);
    const char *input_file_path = NULL;
    const char *output_file_path = NULL;

    while (argc > 0) {
        const char *flag = shift(&argc, &argv);
        if (strcmp(flag, "-d") == 0) {
            WD2NTLM_LOGGING = _DEBUG;
            wd2ntlm_log(_DEBUG,"Enabling debug log.");
        } else if(strcmp(flag, "-o") == 0) {
            if (argc <= 0) {
                usage(stderr, program);
                wd2ntlm_log(_ERROR,"No value provided for flag %s.", flag);
                exit(1);
            }
            output_file_path = shift(&argc, &argv);
            wd2ntlm_log(_DEBUG,"+ Output File: %s", output_file_path);


        } else if (strcmp(flag, "-h") == 0) {
            wd2ntlm_log(_INFO,"Called help with flag %s.", flag);
            usage(stdout, program);
            exit(0);
        } else {
            wd2ntlm_log(_INFO,"+ Input File: %s", flag);
            input_file_path = flag;
        }
    }
    
    if (input_file_path == NULL) {
        wd2ntlm_log(_ERROR,"No input file path was provided.\n");
        usage(stderr, program);
        exit(1);
    }

    if (output_file_path == NULL) {
        char output_file_name[256];
        wd2ntlm_file_name_of_path(input_file_path, output_file_name);
        wd2ntlm_log(_INFO,"+ Output File: %s", output_file_name);
    }
    
    wd2ntlm_log(_DEBUG, "- STAGE 1 END -");
    wd2ntlm_log(_INFO, "--- STAGE 2 ---");

    Wd2ntlm_FileInfo fileInfo = wd2ntlm_process_file(input_file_path);
    
    if (fileInfo.lines != -1) {
        // Print the file information
        wd2ntlm_print_file_info(fileInfo);
    }
    
    wd2ntlm_log(_DEBUG, "- STAGE 2 END -");

    return 0;

}