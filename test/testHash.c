//
// Created by diogo on 02/07/2023.
//
#include <assert.h>
#include <stdio.h>
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
        hash_insere(&h, (*municipios)+i);
    }
    municipio* res = hash_busca(h, "5200050\0");
    res;
//    hash_apaga(&h);
}
//void test_search(){
//    thash h;
//    int nbuckets = 10;
//    municipio * munici;
//    hash_constroi(&h,nbuckets,get_key);
//    assert(hash_insere(&h,aloca_munici("edson","0123456789"))==EXIT_SUCCESS);
//    assert(hash_insere(&h,aloca_munici("takashi","1123456789"))==EXIT_SUCCESS);
//    assert(hash_insere(&h,aloca_munici("matsubara","2123456789"))==EXIT_SUCCESS);
//
//    munici = hash_busca(h,"edson");
//    assert(munici->cpf[0]=='0');
//    munici = hash_busca(h,"takashi");
//    assert(munici->cpf[0]=='1');
//    munici = hash_busca(h,"matsubara");
//    assert(munici->cpf[0]=='2');
//    munici = hash_busca(h,"patricia");
//    assert(munici == NULL);
//
//    hash_apaga(&h);
//}
//
//void test_remove(){
//    thash h;
//    int nbuckets = 10;
//    municipio * munici;
//    hash_constroi(&h,nbuckets,get_key);
//    assert(hash_insere(&h,aloca_munici("edson","0123456789"))==EXIT_SUCCESS);
//    assert(hash_insere(&h,aloca_munici("takashi","1123456789"))==EXIT_SUCCESS);
//    assert(hash_insere(&h,aloca_munici("matsubara","2123456789"))==EXIT_SUCCESS);
//
//    munici = hash_busca(h,"edson");
//    assert(munici->cpf[0]=='0');
//    munici = hash_busca(h,"takashi");
//    assert(munici->cpf[0]=='1');
//    munici = hash_busca(h,"matsubara");
//    assert(munici->cpf[0]=='2');
//    munici = hash_busca(h,"patricia");
//    assert(munici == NULL);
//
//    assert(h.size == 3);
//    assert(hash_remove(&h,"edson")==EXIT_SUCCESS);
//    munici = hash_busca(h,"edson");
//    assert(munici == NULL);
//    assert(h.size == 2);
//
//    assert(hash_remove(&h,"edson")==EXIT_FAILURE);
//
//    munici = hash_busca(h,"matsubara");
//    assert(munici->cpf[0]=='2');
//
//
//    hash_apaga(&h);
//
//}

int main(int argc, char* argv[]){
    test_hash();
//    test_search();
//    test_remove();
    return 0;
}