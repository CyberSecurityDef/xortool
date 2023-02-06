#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>

#include "xor.h"

void help(void){
    printf("OPTIONS:\n\t");
    printf("-i  input file\n\t");
    printf("-o  output file\n\t");
    printf("-k  key\n\t");
    printf("-h  Using help\n");
    printf("EXAMPLES:\n\t");
    printf("xortool -i infile -o outfile -k test\n");
}

int main(int argc, char **argv){
    FILE *fin = NULL;
    FILE *fout = NULL;
    char *input_file = NULL;
    char *output_file = NULL;
    char *in_file = NULL;
    char *out_file = NULL;
    char *key = NULL;
    _off64_t byte = 0;
    int opt = 0;
    opterr = false;
    while((opt = getopt(argc, argv, "i:o:k:h")) != EOF){
        switch(opt){
            case 'i' :
                input_file = optarg;
                break;
            case 'o' :
                output_file = optarg;
                break;
            case 'k' :
                key = optarg;
                break;
            case 'h':
                help();
                return 0;
            default :
                fprintf(stderr, "Invalid argument\n");
                return EOF;
        }
    }
    if(argc == 7){
        if((fin = fopen(input_file, "rb")) != NULL){
            fseek(fin, 0, SEEK_END);
            byte = ftello64(fin);
            fseek(fin, 0, SEEK_SET);

            in_file = (char*)malloc(sizeof(char) * byte);
            fread(in_file, sizeof(char), byte, fin);

            out_file = (char*)malloc(sizeof(char) * byte);
            xor(in_file, byte, key, strlen(key), out_file);

            fout = fopen(output_file, "wb");
            fwrite(out_file, sizeof(char), byte, fout);

            fclose(fin);
            fclose(fout);
            free(in_file);
            free(out_file);
        }
        else
            perror("");
    }
    else
        help();
    return 0;
}
