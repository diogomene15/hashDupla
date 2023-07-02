#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash.h"
#define SEED    0x12345678
#define SEED2    0x83741237

void grow_hash(thash* h){
    int novoTam = h->max + 20;
    uintptr_t* newTable = calloc(novoTam, sizeof(uintptr_t));
    for(int i=0; i< h->max; i++){
        *(newTable+i) = *((h->table)+i);
    }
    free(h->table);
    h->table = newTable;
    h->max = novoTam;
}

uint32_t hashf(const char* str, uint32_t h){
    /* One-byte-at-a-time Murmur hash 
    Source: https://github.com/aappleby/smhasher/blob/master/src/Hashes.cpp */
    for (; *str; ++str) {
        h ^= *str;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return h;
}

int getNumDigits(int pos){
    if(pos == 0) return 1;
    int size = 0;
    while(pos > 0){
        pos/=10;
        size++;
    }
    return size;
}

int hash_insere(thash * h, void * bucket){
    uint32_t hash = hashf(h->get_key(bucket),SEED);
    int pos = (int) (hash % (h->max));
    if (h->max <= (h->size+1)){
//        free(bucket);
        grow_hash(h);
//        return EXIT_FAILURE;
    }else{
        int secondHashDif = 0;
        while(h->table[pos] != 0){
            if (h->table[pos] == h->deleted)
                break;
            unsigned long long tamChars = getNumDigits(pos);
            char posStr[tamChars+1];
            snprintf((char *) &posStr, tamChars + 1, "%d", pos);
            secondHashDif = (int) ((secondHashDif + hashf(posStr, SEED2) % (h->max -1))% (h->max -1));
            secondHashDif*=secondHashDif;
            pos = ((pos) + secondHashDif) %(h->max);
            secondHashDif++;
        }
        h->table[pos] = (uintptr_t) bucket;
        h->size +=1;
    }
    return EXIT_SUCCESS;
}



int hash_constroi(thash * h,int nbuckets, char * (*get_key)(void *) ){
    h->max = (int)(nbuckets*1.3) + 1;
    h->table = calloc(h->max,sizeof(uintptr_t));
    if (h->table == NULL){
        return EXIT_FAILURE;
    }
    h->size = 0;
    h->deleted = (uintptr_t) & (h->size);
    h->get_key = get_key;
    return EXIT_SUCCESS;
}


void * hash_busca(thash h, const char * key){
    int pos = (int) (hashf(key,SEED) %(h.max));
    int secondHashDif = 0;
    while(h.table[pos] != 0){
        if (strcmp (h.get_key((void*)h.table[pos]),key) ==0)
            return (void *)h.table[pos];
        unsigned long long tamChars = getNumDigits(pos);
        char posStr[tamChars+1];
        snprintf((char *)&posStr, tamChars+1, "%d", pos);
        secondHashDif = (int)((secondHashDif + hashf(posStr, SEED2) % (h.max -1))% (h.max -1));
        secondHashDif*=secondHashDif;
        pos = ((pos) + secondHashDif) %(h.max);
        secondHashDif++;
    }
    return NULL;
}

int hash_remove(thash * h, const char * key){
    int pos = (int) (hashf(key,SEED) % (h->max));
    while(h->table[pos]!=0){
        if (strcmp (h->get_key((void*)h->table[pos]),key) ==0){
            free((void *) h->table[pos]);
            h->table[pos] = h->deleted;
            h->size -=1;
            return EXIT_SUCCESS;
        }else{
            pos = (pos+1)%h->max;
        }

    }
    return EXIT_FAILURE;
}

void hash_apaga(thash *h){
    int pos;
    for(pos =0;pos< h->max;pos++){
        if (h->table[pos] != 0){
            if (h->table[pos]!=h->deleted){
                free((void *)h->table[pos]);
            }
        }
    }
    free(h->table);
}


