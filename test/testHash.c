//
// Created by diogo on 02/07/2023.
//
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../src/hash.h"
#include "../src/problema1/problema1.h"
char * get_key(void * reg){
    return (*((municipio *)reg)).codIBGE;
}

void test_hash(){
    thash h;
    municipio** municipios;
    int numMuni;
    lerMunicipios(&municipios, &numMuni);
    hash_constroi(&h,numMuni,get_key);
    for(int i=0; i<numMuni; i++){
        hash_insere(&h, *(municipios+i));
    }
    hash_apaga(&h);
}
void test_search(){
    thash h;
    municipio** municipios;
    int numMuni;
    lerMunicipios(&municipios, &numMuni);
    hash_constroi(&h,numMuni,get_key);
    for(int i=0; i<numMuni; i++){
        hash_insere(&h, *(municipios+i));
    }

    municipio* res = hash_busca(h, "3100203\0");
    assert(strcmp(res->codIBGE, "3100203\0") == 0);
    assert(strcmp(res->nomeMunicipio, "Abaeté\0") == 0);
    assert(strcmp(res->codigoUf, "MG\0") == 0);

    res = hash_busca(h, "5002704\0");
    assert(strcmp(res->codIBGE, "5002704\0") == 0);
    assert(strcmp(res->nomeMunicipio, "Campo Grande\0") == 0);
    assert(strcmp(res->codigoUf, "MS\0") == 0);

    res = hash_busca(h, "2313302\0");
    assert(strcmp(res->codIBGE, "2313302\0") == 0);
    assert(strcmp(res->nomeMunicipio, "Tauá\0") == 0);
    assert(strcmp(res->codigoUf, "CE\0") == 0);

    hash_apaga(&h);
}

int main(int argc, char* argv[]){
    test_hash();
    test_search();
    return 0;
}