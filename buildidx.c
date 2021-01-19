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

int main(int argc, char *argv[]) {
    if (argc != 3){
        fprintf(stderr, "Usage: %s filename.kv capacity\n", argv[0]);
        exit(0);
    }
    /* setting user input */
    int capacity = atoi(argv[2]);
    char *filename = argv[1];

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL){
        printf("%s could not be opened\n", argv[1]);
        exit(1);
    } //Error check

    /* creating a khs file */
    getRid(filename);
    strcat(filename, "khs");
    FILE *khsFp = fopen(filename, "wb+");
    if (khsFp == NULL){
        printf("%s file could not be made\n", filename);
        exit(2);
    }
    write_empty(khsFp, capacity);

    /* creating a vhs file */
    getRid(filename);
    strcat(filename, "vhs");
    FILE *vhsFp = fopen(filename, "wb+");
    if (vhsFp == NULL){
        printf("%s file could not be made\n", filename);
        exit(3);
    }
    write_empty(vhsFp, capacity);

    int index = 0;
    char key[STRLEN];
    char val[STRLEN];
    /* getting the value and corresponding key hen storing it in the new khs file */
    while (read_keyval(fp, key, val) == 2){
        int hashV = hashfn(val, capacity);
        int hashK = hashfn(key, capacity);
        int vIndex = 0;
        int kIndex = 0;
        int iterator = hashV;

        while (iterator < capacity + hashV){
            read_index(vhsFp, iterator, &vIndex);
            if (vIndex == -1){
                break;
            }
            iterator++;
            if (iterator >= capacity){
                iterator = 0;
            }
        }
        /* writing values to file */
        write_index(vhsFp, index, iterator);

        iterator = hashK;
        while (iterator < capacity + hashK){
            read_index(khsFp, iterator, &kIndex);
            if (kIndex == -1){
                break;
            }
            iterator++;
            if (iterator >= capacity){
                iterator = 0;
            }
        }
        /* writing keys to file */
        write_index(khsFp, index, iterator);
        index++;
    }

    /* closing opened files */
    fclose(khsFp);
    fclose(vhsFp);
    fclose(fp);

    return(0);
}