#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "./problema1/problema1.h"
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


int hash_insere(thash * h, void * bucket){
    uint32_t hash = hashf(h->get_key(bucket),SEED);
    int pos = hash % (h->max);
    if (h->max <= (h->size+1)){
//        free(bucket);
        grow_hash(h);
//        return EXIT_FAILURE;
    }else{
        while(h->table[pos] != 0){
            if (h->table[pos] == h->deleted)
                break;
            pos = (pos +1) % h->max;
        }
        h->table[pos] = (uintptr_t) bucket;
        h->size +=1;
    }
    return EXIT_SUCCESS;
}



int hash_constroi(thash * h,int nbuckets, char * (*get_key)(void *) ){
    h->table = calloc(sizeof(uintptr_t),nbuckets +1);
    if (h->table == NULL){
        return EXIT_FAILURE;
    }
    h->max = nbuckets +1;
    h->size = 0;
    h->deleted = (uintptr_t) & (h->size);
    h->get_key = get_key;
    return EXIT_SUCCESS;
}


void * hash_busca(thash h, const char * key){
    int pos = hashf(key,SEED) %(h.max);
    while(h.table[pos] != 0){
        if (strcmp (h.get_key((void*)h.table[pos]),key) ==0)
            return (void *)h.table[pos];
        else{
            int secondHashDif = hashf(key, SEED2) % (h.max-1);
            pos = ((pos) + secondHashDif) %(h.max);
        }
    }
    return NULL;
}

int hash_remove(thash * h, const char * key){
    int pos = hashf(key,SEED) % (h->max);
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


