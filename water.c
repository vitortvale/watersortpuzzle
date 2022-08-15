#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ANSI-color-codes.h"
#define TAM 5

typedef struct
{
    char cor[TAM][8];
}pote;

void imprimePotes(pote p[], int qtd_potes);
void geraFase(pote p[], int fase, char cores[][8]);
void despejo(pote p[], int pote_retirado, int pote_despejado);
int checagemCores(pote p[], int qtdpotes);

int main()
{
    char cores[6][8] = {"RED", "GRN", "YEL", "BLU", "MAG", "CYN"};
    char cor_aleatoria[8];
    pote lista_potes[6];
    //int contador_fases = 0;
    int pote_retirado, pote_despejado, fase = 1;
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            strcpy(lista_potes[i].cor[j], "VAZIO");
        }
    }
    srand(time(NULL));
    geraFase(lista_potes, fase, cores);
    while(fase <=3)
    {
        scanf("%d %d", &pote_retirado, &pote_despejado);
        if(pote_retirado >= 0 && pote_retirado <= 4 && pote_despejado >=0 && pote_despejado <=4)
        {
            despejo(lista_potes, pote_retirado, pote_despejado);
        }
        imprimePotes(lista_potes, 2);
        if(checagemCores(lista_potes, fase*2) == 0)
        {
            printf("\n");
            printf("Parabens! Voce passou pela fase %d!\n", fase);
            fase++;
            geraFase(lista_potes, fase, cores);
        }
    }
    return 0;
}

void imprimePotes(pote p[], int qtd_potes)
{
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < qtd_potes + 2; j++)
        {
            printf("|");
            if(strcmp(p[j].cor[i], RED) == 55)
            {
                printf(REDB "  " reset);
            }
            if(strcmp(p[j].cor[i], GRN) == 44)
            {
                printf(GRNB "  " reset);
            }
            if(strcmp(p[j].cor[i], YEL) == 62)
            {
                printf(YELB "  " reset);
            }
            if(strcmp(p[j].cor[i], BLU) == 39)
            {
                printf(BLUB "  " reset);
            }
            if(strcmp(p[j].cor[i], MAG) == 50)
            {
                printf(MAGB "  " reset);
            }
            if(strcmp(p[j].cor[i], CYN) == 40)
            {
            printf(CYNB "  " reset);
            }
            if (strcmp(p[j].cor[i], "VAZIO") == 0)
            {
                printf("  ");
            }
            printf("|");
        }
        printf("\n");
    }
}
void geraFase(pote p[], int fase, char cores[][8])
{
    char color1[8], color2[8];
    int c1 = rand()%6;
    int c2 = rand()%6;
    int conta_c1 = 0;
    int conta_c2 = 0;
    switch (fase)
    {
        case 1:
        strcpy(color1, cores[c1]);
        strcpy(color2, cores[c2]);
        char cores_fase[2][8];
        strcpy(cores_fase[0], color1);
        strcpy(cores_fase[1], color2);
        for(int numero_pote = 0; numero_pote < 2; numero_pote++)
        {
            for(int posicao_cor = 1; posicao_cor < TAM; posicao_cor++)
            {
                strcpy(p[numero_pote].cor[posicao_cor], cores_fase[rand()%2]);
            }
        }
        imprimePotes(p, 2);
        break;
        case 2: 
            for(int numero_pote = 0; numero_pote < 2; numero_pote++)
            {
                for(int posicao_cor = 1; posicao_cor < TAM; posicao_cor++)
                {
                    strcpy(p[numero_pote].cor[posicao_cor], cores[rand()%4]);
                }
            }
            imprimePotes(p, 4);
            break;
        case 3: // FASE 3(5 FRASCOS (2 VAZIOS), 3 CORES)
            for(int numero_pote = 0; numero_pote < 3; numero_pote++)
            {
                for(int posicao_cor = 1; posicao_cor < TAM; posicao_cor++)
                {
                    strcpy(p[numero_pote].cor[posicao_cor], cores[rand()%6]);
                }
            }
            imprimePotes(p, 6);
            break;
        }
}

void despejo(pote p[], int pote_retirado, int pote_despejado)
{
    char retirado[8], despejado[8];
    int checaHomogeneo = 0;
    char corHomogenea[8];
    int indexCor;
    for(int i = 0; i < TAM; i++)
    {
        if(strcmp(p[pote_despejado].cor[i], "VAZIO") != 0 )
        {
            strcpy(corHomogenea, p[pote_despejado].cor[i]);
            indexCor = i;
        }
    }
    for(int j = indexCor; j < TAM; j++)
    {
        if(strcmp(p[pote_despejado].cor[j], "VAZIO") != 0)
        {
            if(strcmp(p[pote_despejado].cor[j], corHomogenea) != 0)
            {
                checaHomogeneo++;
            }
        }
    }
    if(checaHomogeneo > 0)
    {
        printf("Voce nao pode fazer isso!\n");
    }
    else
    {
        
        for(int i = 0; i < TAM; i++)
        {
            if(strcmp(p[pote_retirado].cor[i], "VAZIO") != 0)
            {
                strcpy(retirado, p[pote_retirado].cor[i]);
                strcpy(p[pote_retirado].cor[i], "VAZIO");
                break;
            }
        }
        
        for(int j = 4; j >= 0; j--)
        {
            if(strcmp(p[pote_despejado].cor[j], "VAZIO") == 0)
            {
                strcpy(despejado, retirado);
                strcpy(p[pote_despejado].cor[j], retirado);
                break;
            }
        }
    }
}

int checagemCores(pote p[], int qtdpotes)
{
    int contador = 0;
    char corHomogenea[8];
    int indexCor;
    for(int i = 0; i < qtdpotes; i++)
    {
        for(int j = 0; j < TAM; j++)
            {
                if(strcmp(p[i].cor[j], "VAZIO") != 0)
                {
                    strcpy(corHomogenea, p[i].cor[j]);
                    indexCor = j;
                    for(int k = indexCor; k < TAM; k++)
                    {
                        if(strcmp(p[i].cor[k], corHomogenea) != 0)
                        {
                            contador++;
                        }
                    }
                }
            }
    }
    return contador;
}
