#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "hashfn.h"

int main (int argc, char *argv[]){
    if (argc != 2){
        fprintf(stderr, "Usage: %s 'movie name'\n", argv[0]);
        exit(0);
    } //Error check

    /* initializing all needed files */
    char *movie = argv[1];
    FILE *nameKh = fopen("name.basics.khs", "rb");
    FILE *nameK = fopen("name.basics.kv", "rb");
    FILE *titleK = fopen("title.basics.kv", "rb");
    FILE *titleV = fopen("title.basics.vhs", "rb");
    FILE *prncplKh = fopen("title.principals.khs", "rb");
    FILE *prncplK = fopen("title.principals.kv", "rb");

    /* helper counters */
    int success = -1;
    int index = 0;
    int counter = 0;

    /* value storage needed to find movie */
    int capacity = get_capacity(titleK);
    int hash = hashfn(movie, capacity);
    char keyM[STRLEN];
    char val[STRLEN];

    /* gets value of the movie to use later*/
    while (success != 0){
        read_index(titleV, hash, &index);
        read_key(titleK, index, keyM);
        read_val(titleK, index, val);
        if (strcmp(movie, val) == 0){
            success = 0;
            break;
        }
        hash++;
        if (hash >= capacity){
            hash = 0;
            counter++;
        }
        if (counter == 2){
            break;
        }
    }

    if (success != 0){
        printf("NOT FOUND\n");
        exit(1);
    }

    /* reinitializing / value storage */
    capacity = get_capacity(prncplKh);
    hash = hashfn(keyM, capacity);
    index = 0;
    counter = 0;
    int i = 0;
    char actors[capacity][STRLEN];
    char keyP[STRLEN];
    char valP[STRLEN];

    /* uses value of movie to find actors and adds in actor array list if matched*/
    while (success != -1){
        read_index(prncplKh, hash, &index);
        read_key(prncplK, index, keyP);
        read_val(prncplK, index, valP);
        if (strcmp(keyM, keyP) == 0){
            strcpy(actors[i], valP);
            i++;
        }
        hash++;
        if (hash >= capacity){
            hash = 0;
            counter++;
        }
        if (counter == 2){
            break;
        }
    }

    char key[STRLEN];
    capacity = get_capacity(nameKh);
    counter = 0;
    index = 0;
    /* finds the name of the actors from name.basics using the arraylist retrieved*/
    for (i = 0; i <= capacity; i++){
        hash = hashfn(actors[i], capacity);
        read_index(nameKh, hash, &index);
        read_val(nameK, index, val);
        read_key(nameK, index, key);
        if (strcmp(key, actors[i]) == 0 && actors[0] != actors[i]){
            printf("%s\n", val);
        }
    }

    /* closing all files */
    fclose(nameKh);
    fclose(nameK);
    fclose(titleK);
    fclose(titleV);
    fclose(prncplKh);
    fclose(prncplK);
    return(0);
}  