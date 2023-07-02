//
// Created by diogo on 13/06/2023.
//
#include "../problema1/problema1.h"
#include "../hash/hash.h"
#include <stdio.h>
#include <stdlib.h>

void limparTela(){
#ifdef _WIN32 //Deve atender a maior parte dos PC's :)
    system("cls");
#else
    system("clear");
#endif
}

void pause(){
#ifdef _WIN32 //Deve atender a maior parte dos PC's :)
    system("pause");
#else
    system("read -p \"Pressione enter para continuar...\" saindo");
#endif
}

void buscarMunicipio(thash * hashMunicipios){

    limparTela();
    char codIbge[8];
    printf("Cod IBGE: ");
    scanf("%7s", codIbge);


    municipio * res = hash_busca(*hashMunicipios,codIbge);
    if(res == NULL){
        printf("Nenhum municipio encontrado com o Codigo IBGE: %s", codIbge);
        pause();
        limparTela();
        return;
    }
    printf("\nNome: %s\n",res->nomeMunicipio);
    printf("Codigo IBGE: %s\n",res->codIBGE);
    printf("Codigo SIAFI: %s\n",res->codSIAFI);
    printf("Capital: %s\n",res->capital ? "Sim" : "Nao");
    printf("Numero UF: %d\n",res->numUf);
    printf("Codigo UF: %s\n",res->codigoUf);
    printf("UF: %s\n",res->ufEstado);
    printf("Regiao: %s\n",res->regiao);
    printf("DDD: %d\n",res->ddd);
    printf("Fuso Horario: %s\n",res->fusoHorario);
    printf("Latitude: %f\n",res->lat);
    printf("Longitude: %f\n",res->lon);
    printf("\n\n");
    pause();
    limparTela();
}
char * get_key(void * reg){
    return (*((municipio *)reg)).codIBGE;
}
int main(void){
    thash hashMunicipios;
    municipio** municipios;
    int numMuni;
    lerMunicipios(&municipios, &numMuni);
    hash_constroi(&hashMunicipios,numMuni,get_key);
    for(int i=0; i<numMuni; i++){
        hash_insere(&hashMunicipios, *(municipios+i));
    }
    int option = -1;
    while(option != 0){
        printf("Escolha uma opcao:\n(0)Sair\n(1)Buscar municipio\n>");
        scanf("%d",&option);
        if(option == 1){
            buscarMunicipio(&hashMunicipios);
        }
    }
    hash_apaga(&hashMunicipios);
    return EXIT_SUCCESS;
}