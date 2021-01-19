#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "hashfn.h"

/* removes characters until "." is reached in filename */
void getRid (char *filename){
    int i = 0;
    while (filename[i] != '\0'){
        i++;
    }
    while (filename[i] != '.'){
        filename[i] = '\0';
        i--;
    }
}
  
int main(int argc, char *argv[]){
    if (argc != 3){
        fprintf(stderr, "Usage: %s filename.kv 'search term'\n", argv[0]);
        exit(0);
    }

    /* initialising user input */
    char *filename = argv[1];
    FILE *fp = fopen(filename, "rb");
    char term[STRLEN];
    strcpy(term, argv[2]);

    /* reading a khs file */
    getRid(filename);
    strcat(filename, "khs");
    FILE *khsFp = fopen(filename, "rb");
    int capacity = get_capacity(khsFp);


    char key[STRLEN];
    char val[STRLEN];
    int hash = hashfn(term, capacity);
    int index = 0;
    int counter = 0;
    int success = -1
    /* getting corresponding value with key */;
    while (success != 0){
        read_index(khsFp, hash, &index);
        read_key(fp, index, key);
        read_val(fp, index, val);
        if (strcmp(key, term) == 0){
            printf("%s\n", val);
            success = 0;
        }
        hash++;
        if (hash >= capacity){
            hash = 0;
        }
        if (counter == 2){
            break;
        } //using a counter to know break time
    }

    if (success != 0){
        printf("NOT FOUND\n");
    } //Error check

    /* closing opened files */
    fclose(fp);
    fclose(khsFp);
    return(0);
} 