/* Programa de distribuição de cartas */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void Embaralhar(short[][13]);
void Distribuir(const short[][13], const char *[], const char *[]);
bool Comparar(const short[], const short[], const short[], const short[]);
bool VerRoyal(const short[], const short[]);
bool VerStraightFlush(const short[], const short[]);
bool VerQuadra(const short[], const short[]);
bool VerFull(const short[], const short[]);
bool VerFlush(const short[], const short[]);
bool VerStraight(const short[], const short[]);
bool VerTrinca(const short[], const short[]);
bool VerTwo(const short[], const short []);
bool VerPar(const short[], const short[]);

int main()
{
    const char *naipe[4] = { "Copas","Ouros","Paus","Espadas" };
    const char *face[13] = {"As", "Dois", "Tres", "Quatro","Cinco", "Seis", "Sete", "Oito", "Nove", "Dez", "Valete", "Dama", "Rei"};
    short baralho[4][13] = {0};
    srand(time(NULL));
    Embaralhar(baralho);
    Distribuir(baralho, face, naipe);
    return 0;
}

void Embaralhar(short wBaralho[][13]){
    short carta, linha, coluna;
    for (carta = 1; carta <= 52; carta++){
        do{ linha = rand() % 4;
            coluna = rand() % 13;
        }while(wBaralho[linha][coluna] != 0);
        wBaralho[linha][coluna] = carta;
    }
}

void Distribuir(const short wBaralho[][13], const char *wFace[], const char *wNaipe[]){
    short carta, linha, coluna, hf = -1,hf2 = -1, naipes[4] = {0}, faces[13] = {0},naipes2[4] = {0}, faces2[13] = {0};
    short mao1[5][2],mao2[5][2];
    printf("Jogador 1:\n\n");

    for (carta = 1; carta < 6; carta++)
        for (linha = 0; linha < 4; linha++)
            for (coluna = 0; coluna < 13; coluna++)
                if (wBaralho[linha][coluna] == carta){
                    if(!coluna || (hf && coluna > hf))hf = coluna; // A é a maior carta, ou seja, hf parou no 0, não pode sair.
                    mao1[carta-1][0] = coluna;
                    mao1[carta-1][1] = linha;
                    naipes[linha]++;
                    faces[coluna]++;
                    printf("%6s de %-7s%c",wFace[coluna], wNaipe[linha],carta % 2 == 0 ? '\n' : '\t');
                }

    printf("\n\n\nJogador 2:");
    printf("\n\n");

    for (carta = 6; carta < 11; carta++)
        for (linha = 0; linha < 4; linha++)
            for (coluna = 0; coluna < 13; coluna++)
                if (wBaralho[linha][coluna] == carta){
                    if(!coluna || (hf2 && coluna > hf2)) hf2 = coluna; // A é a maior carta
                    mao2[carta-1][0] = coluna;
                    mao2[carta-1][1] = linha;
                    naipes2[linha]++;
                    faces2[coluna]++;
                    printf("%6s de %-7s%c",wFace[coluna], wNaipe[linha],(carta+1) % 2 == 0 ? '\n' : '\t');
                }

    printf("\n\n");

    if(!Comparar(naipes,faces,naipes2,faces2)){
        if(hf == hf2)
            printf("Jogo empato os dois jogadores tem como maior carta %s", wFace[hf]);
        else if((!hf && hf2) || (hf > hf2 && hf2))
            printf("Jogador um vence com a carta %s!",wFace[hf]);
        else
            printf("Jogador dois vence com a carta %s!",wFace[hf2]);
    }

    return;
}



bool VerRoyal(const short naipe[], const short face[]){
    if(VerFlush(naipe,face)){
        if(face[0] && face[9] && face[10] && face[11] && face[12]) return 1;
    }
    return 0;
}

bool VerStraightFlush(const short naipe[], const short face[]){
    if (VerFlush(naipe,face) && VerStraight(naipe,face)) return 1;
    return 0;
}

bool VerQuadra(const short[], const short face[]){
    for(short i = 0; i < 13; i++) if(face[i]==4) return 1;
    return 0;
}

bool VerFull(const short naipe[], const short face[]){
    if (VerTrinca(naipe,face) && VerPar(naipe,face)) return 1;
    return 0;
}

bool VerFlush(const short naipe[], const short[]){
    for(short i = 0; i < 4; i++) if(naipe[i]==5) return 1;
    return 0;
}

bool VerStraight(const short[], const short face[]){
    for(short i = 0; i < 8; i ++)
        if(face[i] && face[i + 1] && face[i + 2] && face[i + 3] && face[(i + 4) % 13]) return 1;
    return 0;
}

bool VerTrinca(const short[], const short face[]){
    for(short i = 0; i < 13; i++) if(face[i]==3) return 1;
    return 0;
}

bool VerTwo(const short[], const short face[]){
    bool par = 0;
    for(short i = 0; i < 13; i++){
        if(face[i]==2 && par) return 1;
        else if(face[i]==2) par = 1;
    }
    return 0;
}

bool VerPar(const short[], const short face[]){
    for(short i = 0; i < 13; i++) if(face[i]==2) return 1;;
    return 0;
}

bool VerKicker(const short[], const short face[]){
    for(short i = 0; i < 13; i++) if(face[i]==2) return 1;;
    return 0;
}

bool Comparar(const short naipe[], const short face[],const short naipe2[], const short face2[]){
    bool (*funcao[])(const short[], const short[]) = {
        VerRoyal,
        VerStraightFlush,
        VerQuadra,
        VerFull,
        VerFlush,
        VerStraight,
        VerTrinca,
        VerTwo,
        VerPar
    };

    const char* maos[] = {
        "Royal Flush",
        "Straight Flush",
        "Quadra",
        "Full House",
        "Flush",
        "Straight",
        "Trinca",
        "Dois Pares",
        "Par"
    };

    for(int i = 0; i < 9;i++){
        bool x = funcao[i](naipe,face), y = funcao[i](naipe2, face2);
        if (x && !y){
            printf("Jodador um vence com %s.\n", maos[i]);
            return 1;
        }

        else if (!x && y){
            printf("Jodador dois vence com %s.\n", maos[i]);
            return 1;
        }
        else if (x && y){
            // 1. Royal Flush:
            //        Não criterio de desempate, divisão do pote;
            //
            // 2. Straight Flush (as 5 cartas serem iguias):
            //        Criterio1(se existir mão maior):
            //            Ganha quem tiver a maior carta
            //
            //        Criterio2(se não existir mão maior):
            //            Divisão do pote
            //
            // 3. Quadra:
            //        Criterio1(se existir quadra maior):
            //            Maior quadra vence
            //
            //        Criterio2(se não existir quadra maior):
            //            Maior kicker vence
            //
            //        Criterio3(Se não tiver maior kicker):
            //            Divisão de pote
            //
            // 4. Full House:
            //        Criterio1(se existir trinca maior):
            //            Maior trinca vence
            //
            //        Criterio2(par)
            //            Maior Par vence
            //
            //        Criterio3(se não existir par maior)
            //            Divisão do pote
            //
            // 5. Flush
            //        Criterio1(comparar carta por carta)
            //            Vence a maior carta que não der empate, se compara até a quinta carta
            //
            //        Criterio2(não tem maior carta)
            //            Divisão do pote
            //
            // 6. Straight
            //        Criterio1(a uma sequencia maior)
            //            Maior sequencia vence
            //        Criterio2(não a)
            //            Divisão do pote
            //
            // 7. Trinca
            //        Criterio1(trinca)
            //            Maior vence
            //
            //        Criterio2(kicker)
            //            Compara os kickes em sequencia, o maior vence
            //
            //        Criterio3(não a kinker maior)
            //            Divisão do pote
            //
            // 8. Dois pares
            //        Criterio1(pares)
            //            Compara os pares em sequencia, o maior vence
            //
            //        Criterio2(kicker)
            //            O maior kicker vence
            //
            //        Criterio3(não tem kicker)
            //            Divisção do pote
            //
            // 9. Par
            //        Criterio1(par)
            //            O maior par vence
            //
            //        Criterio2(kicker)
            //            O maior kicker vence
            //
            //        Criterio3(não tem kicker)
            //            Divisção do pote
            //
            // 10. Maior carta
            //       Criterio1(carta)
            //            O maior carta vence
            //
            //        Criterio2(não tem carta mais alta)
            //            Divisção do pote
            //



            printf("Os dois jogadores tem %s.\n", maos[i]);
            return 0;
        }
    }
    return 0;
}
