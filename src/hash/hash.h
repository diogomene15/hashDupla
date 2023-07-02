#ifndef HASH_FACOM_LIB
#define HASH_FACOM_LIB
#include <stdlib.h>
typedef struct {
    uintptr_t * table;
    int size;
    int max;
    uintptr_t deleted;
    char * (*get_key)(void *);
}thash;

int hash_insere(thash * h, void * bucket);
int hash_constroi(thash * h,int nbuckets, char * (*get_key)(void *) );
void * hash_busca(thash h, const char * key);
int hash_remove(thash * h, const char * key);
void hash_apaga(thash *h);
#endif //HASH_FACOM_LIB

//Por: Diogo Menezes - 202219060206