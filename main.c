#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void Embaralhar(short wBaralho[][4]);
void Distribuir(const short wBaralho[][4], const char *stringFace[], const char *stringNaipe[]);
bool Comparar  (short mao1[5][2],short mao2[5][2], const char *stringFace[]);
int Troca(const void *a, const void *b);
short VerRoyal  (const short mao[5][2]);
short VerSFlush (const short mao[5][2]);
short VerQuadra (const short mao[5][2]);
short VerFull   (const short mao[5][2]);
short VerFlush  (const short mao[5][2]);
short VerS      (const short mao[5][2]);
short VerTrinca (const short mao[5][2]);
short VerTwo    (const short mao[5][2]);
short VerPar    (const short mao[5][2]);

int main(){
    const char *naipe[4] = {"Copas","Ouros","Paus","Espadas"};
    const char *face[13] = {"As", "Dois", "Tres", "Quatro","Cinco", "Seis", "Sete", "Oito", "Nove", "Dez", "Valete", "Dama", "Rei"};
    short baralho[13][4] = {0};

    srand(time(NULL));
    Embaralhar(baralho);
    Distribuir(baralho, face, naipe);
    return 0;
}


int Troca(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}


void Embaralhar(short wBaralho[][4]){
    short carta, face, naipe;

    for (carta = 1; carta <= 52; carta++){
        do{ naipe = rand() % 4;
            face = rand() % 13;
        }while(wBaralho[face][naipe] != 0);
        wBaralho[face][naipe] = carta;
    }
}

void Distribuir(const short wBaralho[][4], const char *stringFace[], const char *stringNaipe[]){
    short mao1[5][2],mao2[5][2];
    printf("Jogador 1:\n\n");

    for (int carta = 1; carta < 6; carta++) for(int face = 0; face < 13; face++) for(int naipe = 0; naipe < 4; naipe++)
        if (wBaralho[face][naipe] == carta){
            mao1[carta-1][0] = naipe;
            mao1[carta-1][1] = face;
            printf("%6s de %-7s%c",stringFace[face], stringNaipe[naipe],carta % 2 == 0 ? '\n' : '\t');
    }

    printf("\n\n\nJogador 2:");
    printf("\n\n");

    for(int carta = 6; carta < 11; carta++) for(int face = 0; face < 13; face++) for(int naipe = 0; naipe < 4; naipe++)
        if (wBaralho[face][naipe] == carta){
            mao2[carta-6][0] = naipe;
            mao2[carta-6][1] = face;
            printf("%6s de %-7s%c",stringFace[face], stringNaipe[naipe],(carta+1) % 2 == 0 ? '\n' : '\t');
     }
    printf("\n\n");
    Comparar(mao1,mao2,stringFace);
    return;
}

bool Comparar(short mao1[5][2], short mao2[5][2], const char *stringFace[]){
    short (*funcao[])(const short mao1[5][2]) = {
        VerRoyal,
        VerSFlush,
        VerQuadra,
        VerFull,
        VerFlush,
        VerS,
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
        short x = funcao[i](mao1), y = funcao[i](mao2);
        if(x && !y) {
            if(i == 2 || i == 6 || i == 8){
                printf("Jogador 1 vence com %s de %s", maos[i],stringFace[x-1]);
                return 1;
            }
            else{
                printf("Jogador 1 vence com %s", maos[i]);
                return 1;
            }
        }
        else if(!x && y){
            if(i == 2 || i == 6 || i == 8){
                printf("Jogador 2 vence com %s de %s", maos[i],stringFace[y-1]);
                return 1;
            }
            else{
                printf("Jogador 2 vence com %s", maos[i]);
                return 1;
            }
        }
        else if(x && y){
            switch(i){
                case 0: // Royal Flush
                case 4: // Flush
                    i = 10;
                    break;

                case 1: // Straight Flush
                case 5: // Straight
                    if (x == 42) x = 100;
                    if (y == 42) y = 100;
                    if (x > y){
                        printf("Jogador 1 vence com o maior %s.", maos[i-1]);
                        return 1;
                    }
                    else if (x < y){
                        printf("Jogador 2 vence com o maior %s.", maos[y-1]);
                        return 1;
                    }
                    else{
                        i = 10; //vai direto para o kicker
                    }
                    break;

                case 2: // Quadra
                case 6: // Trinca
                case 8: // Par
                    if (x > y){
                        printf("Jogador 1 vence com o maior %s, %s.", maos[i],stringFace[x-1]);
                        return 1;
                    }
                    else if (x < y){
                        printf("Jogador 2 vence com o maior %s, %s.", maos[i],stringFace[y-1]);
                        return 1;
                    }
                    else{
                        i = 10; //vai direto para o kicker
                    }
                    break;

                case 3: // Full House
                case 7: // Two par
                    if (x > y){
                        printf("Jogador 1 vence com o maior %s.", maos[i]);
                        return 1;
                    }
                    else if (x < y){
                        printf("Jogador 2 vence com o maior %s.", maos[i]);
                        return 1;
                    }
                    else{
                        short x1 = VerPar(mao1), y1 = VerPar(mao2);
                        if (x1 > y1){
                            printf("Jogador 1 vence com o maior %s.", maos[i]);
                            return 1;
                        }
                        else if (x1 < y1){
                            printf("Jogador 2 vence com o maior %s.", maos[i]);
                            return 1;
                        }
                        else i = 10; //vai direto para o kicker
                    }
                    break;
            }
        }
    }
    int maior_carta1 = -1, maior_carta2 = -1;
    qsort(mao1, 5, 2*sizeof(short), Troca);
    qsort(mao2, 5, 2*sizeof(short), Troca);
    for(int i = 0; i < 5; i++){
        if(mao1[i][1] > maior_carta1) maior_carta1 = mao1[i][1];
        if(mao2[i][1] > maior_carta2) maior_carta2 = mao2[i][1];
        if(maior_carta1 != -1 && maior_carta1 == maior_carta2){
            maior_carta1 = -1;
            maior_carta2 = -1;
        }
        if(maior_carta1 != maior_carta2) break;
    }
    if(maior_carta1 > maior_carta2) printf("Jogador 1 vence com a maior carta %s\n", stringFace[maior_carta1]);
    else if(maior_carta1 < maior_carta2) printf("Jogador 2 vence com a maior carta %s\n", stringFace[maior_carta2]);
    else if(maior_carta1 == maior_carta2) printf("Empate!");

    return 0;
}



short VerRoyal(const short mao[5][2]){
    if(VerFlush(mao) && VerS(mao) == 42) return 1;
    return 0;
}

short VerSFlush(const short mao[5][2]){
    short x = VerS(mao);
    if (VerFlush(mao) && x) return x;
    return 0;
}

short VerQuadra(const short mao[5][2]){
    short faces[13] = {0};
    for(int i = 0; i < 5; i ++) faces[mao[i][1]]++;
    for(int i = 0; i < 13; i++) if(faces[i]==4) return i+1;
    return 0;
}

short VerFull(const short mao[5][2]){
    short x = VerTrinca(mao);
    if (x && VerPar(mao)) return x;
    return 0;
}

short VerFlush(const short mao[5][2]){
    for(short i = 1; i < 5; i++) if(mao[0][0] != mao[i][0]) return 0;
    return 1;
}

short VerS(const short mao[5][2]){
    short faces[13] = {0};
    for(int i = 0; i < 5; i ++) faces[mao[i][1]]++;
    for(short i = 0; i < 10; i ++)
        if(faces[i] && faces[i + 1] && faces[i + 2] && faces[i + 3] && faces[(i + 4) % 13]) {
            short soma = 0;
            for(int i = 0; i < 5; i ++) soma+=mao[i][1];
            return soma;
        }
    return 0;
}

short VerTrinca(const short mao[5][2]){
    short faces[13] = {0};
    for(int i = 0; i < 5; i ++) faces[mao[i][1]]++;
    for(int i = 0; i < 13; i++) if(faces[i]==3) return i+1;
    return 0;
}

short VerTwo(const short mao[5][2]){
    short faces[13] = {0};
    bool par1=false;
    for(int i = 0; i < 5; i ++) faces[mao[i][1]]++;
    for(int i = 0; i < 13; i++) {
        if(faces[i]==2 && par1) return i+1;
        else if(faces[i] == 2) par1=true;
    }
    return 0;
}

short VerPar(const short mao[5][2]){
    short faces[13] = {0};
    for(int i = 0; i < 5; i ++) faces[mao[i][1]]++;
    for(int i = 0; i < 13; i++) if(faces[i]==2) return i+1;
    return 0;
}
