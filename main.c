/* Programa de distribuição de cartas */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void Embaralhar(short wBaralho[][4]);
void Distribuir(const short wBaralho[][4], const char *stringFace[], const char *stringNaipe[], short mao1[5][2], short mao2[5][2], short restante[42][2]);
void Carteador (short mao[5][2], short restante[42][2]);
void Comparar  (short mao1[5][2],short mao2[5][2], const char *stringFace[]);

short VerRoyal  (const short mao[5][2]);
short VerSFlush (const short mao[5][2]);
short VerQuadra (const short mao[5][2]);
short VerFull   (const short mao[5][2]);
short VerFlush  (const short mao[5][2]);
short VerS      (const short mao[5][2]);
short VerTrinca (const short mao[5][2]);
short VerTwo    (const short mao[5][2]);
short VerPar    (const short mao[5][2]);

short VerQuaseS     (const short mao[5][2]);
short VerQuaseS2    (const short mao[5][2]);
short VerQuaseFlush (const short mao[5][2], const short cabaca);

int Troca(const void *a, const void *b);


void main(){
    const char *naipe[4] = {"Copas","Ouros","Paus","Espadas"};
    const char *face[13] = {"As", "Dois", "Tres", "Quatro","Cinco", "Seis", "Sete", "Oito", "Nove", "Dez", "Valete", "Dama", "Rei"};
    //short baralho[13][4] = {0};
    short mao1[5][2], mao2[5][2], restante[42][2];

    srand(time(NULL));
    //Embaralhar(baralho);
    short baralho[13][4] = {
    {  1, 14, 27, 40 }, // A
    {  2, 15, 28, 41 }, // 2
    {  3, 16, 29, 42 }, // 3
    {  4, 17, 30, 43 }, // 4
    {  5, 18, 31, 44 }, // 5
    {  6, 19, 32, 45 }, // 6
    {  7, 20, 33, 46 }, // 7
    {  8, 21, 34, 47 }, // 8
    {  9, 22, 35, 48 }, // 9
    { 10, 23, 36, 49 }, // 10
    { 11, 24, 37, 50 }, // J
    { 12, 25, 38, 51 }, // Q
    { 13, 26, 39, 52 }  // K
    };
    Distribuir(baralho, face, naipe, mao1, mao2, restante);
    Carteador(mao1, restante);
    for(short i = 0; i < 5; i++)
    printf("%s de %s%c",face[mao1[i][1]],naipe[mao1[i][0]], i%2 ? '\n' : '\t');
    printf("\n\n");
    Comparar(mao1, mao2, face);
    return;
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

void Distribuir(const short wBaralho[][4], const char *stringFace[], const char *stringNaipe[], short mao1[5][2], short mao2[5][2], short restante[42][2]){
    printf("Cartedor:\n\n");
    short carta = 1;
    for (carta = 1; carta < 6; carta++) for(short face = 0; face < 13; face++) for(short naipe = 0; naipe < 4; naipe++)
        if (wBaralho[face][naipe] == carta){
            mao1[carta-1][0] = naipe;
            mao1[carta-1][1] = face;
            printf("%6s de %-7s%c",stringFace[face], stringNaipe[naipe],carta % 2 == 0 ? '\n' : '\t');
    }

    printf("\n\n\nJogador:");
    printf("\n\n");

    for(; carta < 11; carta++) for(short face = 0; face < 13; face++) for(short naipe = 0; naipe < 4; naipe++)
        if (wBaralho[face][naipe] == carta){
            mao2[carta-6][0] = naipe;
            mao2[carta-6][1] = face;
            printf("%6s de %-7s%c",stringFace[face], stringNaipe[naipe],(carta+1) % 2 == 0 ? '\n' : '\t');
     }
    printf("\n\n\nRestante:");
    printf("\n\n");
    for(; carta < 53; carta++) for(short face = 0; face < 13; face++) for(short naipe = 0; naipe < 4; naipe++)
        if (wBaralho[face][naipe] == carta){
            restante[carta-11][0] = naipe;
            restante[carta-11][1] = face;
            if(carta < 19)printf("%6s de %-7s%c",stringFace[face], stringNaipe[naipe], carta % 2 == 0 ? '\n' : '\t');
        }
    printf("\n\n");
    return;

}

void Carteador(short mao[5][2], short restante[42][2]){
    short (*funcao[])(const short mao[5][2]) = {
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

    short c = false;
    short trocas = 0;
    short segundo_teste;
    short tristeza = false;
    for(short m = 0; m < 9 && !c; m++){
        if(c  = (*funcao[m])(mao)){
            switch(m){
                case 2:{ // Quadra
                    for(short i = 0; i < 5; i++){
                        if(mao[i][1] != c-1){
                            if(mao[i][1] < 10 && mao[i][1] != 0){
                                mao[i][0] = restante[0][0];
                                mao[i][1] = restante[0][1];
                                trocas++;
                            }
                            break;
                        }
                    }
                }break;
                case 6:{ // Trinca
                    for(short i = 0; i < 5; i++){
                        if(mao[i][1] != c-1){
                            if(trocas) {
                                mao[i][0] = restante[1][0];
                                mao[i][1] = restante[1][1];
                                trocas++;
                                break;
                            }
                            else {
                                mao[i][0] = restante[0][0];
                                mao[i][1] = restante[0][1];
                                trocas++;
                            }

                        }
                    }
                }break;
                case 7:{ // Two
                    segundo_teste = VerPar(mao);
                    for(short i = 0; i < 5; i++){
                        if(mao[i][1] != c-1 && mao[i][1] != segundo_teste-1){
                            if(mao[i][1] < 6 && mao[i][1] != 0){
                                mao[i][0] = restante[0][0];
                                mao[i][1] = restante[0][1];
                                trocas++;
                            }
                            break;
                        }
                    }
                }break;
                case 8:{ // Par
                    if(segundo_teste = VerQuaseFlush(mao, 4))
                        for(int i = 0; i < 5 && !tristeza; i++)
                            if(mao[i][0] != segundo_teste -1) tristeza = i+1;

                    if(c<10 && c!=1){
                        if(tristeza && mao[tristeza-1][1]==c-1){
                            mao[tristeza-1][0] = restante[0][0];
                            mao[tristeza-1][1] = restante[0][1];
                            trocas++;
                            break; // break do switch
                        }
                        if(VerQuaseS(mao)){
                            for(short i = 0; i < 5; i++){
                                if(mao[i][1] == c - 1){
                                    mao[i][0] = restante[0][0];
                                    mao[i][1] = restante[0][1];
                                    trocas++;
                                    break; // break do for
                                }
                            }
                            break; // break do switch
                        }
                    }
                    for(int i = 0; i < 5 && trocas <= 3; i++){
                        if(mao[i][1] != c-1){
                            mao[i][0] = restante[0][0];
                            mao[i][1] = restante[0][1];
                            trocas++;
                        }
                    }


                }break;
            }
        }
    }
    if(!c){
        /*
        4 cartas do mesmo naipe
        → troca 1 (flush)

        4 cartas em sequência
        → troca 1 (sequência)

        3 cartas do mesmo naipe
        → troca 2 (opcional, mas secundário)

        3 cartas em sequência
        → troca 2 (opcional)

        3 cartas altas (A, K, Q, J)
        → mantém e troca 2

        2 cartas altas (A, K / A, Q / K, Q)
        → mantém e troca 3

        Ás sozinho
        → mantém e troca 3

        tudo baixo/desconectado
        → troca 3 que são de naipe diferente
        */
        if(segundo_teste = VerQuaseFlush(mao, 4)){
            for(int i = 0; i< 5 && !trocas; i++)
                if(mao[i][0] != segundo_teste - 1){
                    mao[i][0] = restante[0][0];
                    mao[i][1] = restante[0][1];
                    trocas++;
                }

        }
        else if(segundo_teste = VerQuaseS(mao)){

            for(int i = 0; i< 5; i++){
                if(mao[i][1] > segundo_teste + 3 || (mao[i][1] < segundo_teste - 1 && segundo_teste != 9 )){
                    mao[i][0] = restante[0][0];
                    mao[i][1] = restante[0][1];
                    trocas++;
                }
                else if(mao[i][1] < segundo_teste - 1 && segundo_teste == 9 && mao[i][1] != 0){
                    mao[i][0] = restante[0][0];
                    mao[i][1] = restante[0][1];
                    trocas++;
                }
            }

        }
        else if(segundo_teste = VerQuaseFlush(mao, 3)){
            for(int i = 0; i< 5 && !trocas; i++)
                if(mao[i][0] != segundo_teste - 1){
                    mao[i][0] = restante[0][0];
                    mao[i][1] = restante[0][1];
                    trocas++;
                }
        }
    }
    printf("Cartedor troca %d carta%c\n", trocas, trocas == 1 ? ' ':'s');
}

void Comparar(short mao1[5][2], short mao2[5][2], const char *stringFace[]){
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

    for(short i = 0; i < 9;i++){
        short x = (*funcao[i])(mao1), y = (*funcao[i])(mao2);
        if(x && !y) {
            if(i == 2 || i == 6 || i == 8){
                printf("Cartedor vence com %s de %s", maos[i],stringFace[x-1]);
                return;
            }
            else{
                printf("Cartedor vence com %s", maos[i]);
                return;
            }
        }
        else if(!x && y){
            if(i == 2 || i == 6 || i == 8){
                printf("Jogador vence com %s de %s", maos[i],stringFace[y-1]);
                return;
            }
            else{
                printf("Jogador vence com %s", maos[i]);
                return;
            }
        }
        else if(x && y){
            switch(i){
                case 0:{ // Royal Flush
                    printf("Empate");
                    return;
                }break;

                case 4:{ // Flush
                    i = 10; // Vai direo para o kicker
                }break;

                case 1: // Straight Flush
                case 5:{ // Straight
                    if (x == 42) x = 100;
                    if (y == 42) y = 100;
                    if (x > y){
                        printf("Cartedor vence com o maior %s.", maos[i]);
                        return;
                    }
                    else if (x < y){
                        printf("Jogador vence com o maior %s.", maos[i]);
                        return;
                    }
                    else{
                        i = 10; //vai direto para o kicker
                    }
                }break;

                case 2: // Quadra
                case 6: // Trinca
                case 8:{ // Par
                    if ((x > y && y != 1) || (x == 1 && y != 1)){
                        printf("Cartedor vence com o maior %s, %s.", maos[i],stringFace[x-1]);
                        return;
                    }
                    else if ((x < y && x != 1) || (y == 1 && x != 1)){
                        printf("Jogador vence com o maior %s, %s.", maos[i],stringFace[y-1]);
                        return;
                    }
                    else{
                        i = 10; //vai direto para o kicker
                    }
                }break;

                case 3: // Full House
                case 7:{ // Two par
                    if ((x > y && y != 1) || (x == 1 && y != 1)){
                        printf("Cartedor vence com o maior %s.", maos[i]);
                        return;
                    }
                    else if ((x < y && x != 1) || (y == 1 && x != 1)){
                        printf("Jogador vence com o maior %s.", maos[i]);
                        return;
                    }
                    else{
                        short x1 = VerPar(mao1), y1 = VerPar(mao2);
                        if ((x1 > y1 && y1 != 1) || (x1 == 1 && y1 != 1)){
                            printf("Cartedor vence com o maior %s.", maos[i]);
                            return;
                        }
                        else if ((x1 < y1 && x1 != 1) || (y1 == 1 && x1 != 1)){
                            printf("Jogador vence com o maior %s.", maos[i]);
                            return;
                        }
                        else i = 10; //vai direto para o kicker
                    }
                }break;

            }
        }
    }
    int maior_carta1 = -1, maior_carta2 = -1;
    qsort(mao1, 5, 2*sizeof(short), Troca);
    qsort(mao2, 5, 2*sizeof(short), Troca);

    for(short i = 1; i < 5; i++){
        if(mao1[i][1] == 0){
            for(short j = 0; j < 5; j++ ){
                if(mao1[j][1]!=0){
                    short temp_naipe = mao1[j][0];
                    short temp_face = mao1[j][1];
                    mao1[j][0] = mao1[i][0];
                    mao1[j][1] = mao1[i][1];
                    mao1[i][0] = temp_naipe;
                    mao1[i][1] = temp_face;
                }
            }
        }
    }

    for(short i = 1; i < 5; i++){
        if(mao2[i][1] == 0){
            for(short j = 0; j < 5; j++ ){
                if(mao2[j][1]!=0){
                    short temp_naipe = mao2[j][0];
                    short temp_face = mao2[j][1];
                    mao2[j][0] = mao2[i][0];
                    mao2[j][1] = mao2[i][1];
                    mao2[i][0] = temp_naipe;
                    mao2[i][1] = temp_face;
                }
            }
        }
    }

    for(short i = 0; i < 5; i++){
        if(mao1[i][1] > maior_carta1) maior_carta1 = mao1[i][1];
        if(mao2[i][1] > maior_carta2) maior_carta2 = mao2[i][1];
        if(maior_carta1 != -1 && maior_carta1 == maior_carta2){
            maior_carta1 = -1;
            maior_carta2 = -1;
        }
        if(maior_carta1 != maior_carta2) break;
    }

    if((maior_carta1 > maior_carta2 && maior_carta2 != 0) || (maior_carta1 == 0 && maior_carta2 != 0)) printf("Cartedor vence com a maior carta %s\n", stringFace[maior_carta1]);
    else if((maior_carta1 < maior_carta2 && maior_carta1 != 0) || (maior_carta2 == 0 && maior_carta1 != 0)) printf("Jogador vence com a maior carta %s\n", stringFace[maior_carta2]);
    else if(maior_carta1 == maior_carta2) printf("Empate!");

    return;
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
    for(short i = 0; i < 5; i ++) faces[mao[i][1]]++;
    for(short i = 0; i < 13; i++) if(faces[i]==4) return i+1;
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
    for(short i = 0; i < 5; i ++) faces[mao[i][1]]++;
    for(short i = 0; i < 10; i ++)
        if(faces[i] && faces[i + 1] && faces[i + 2] && faces[i + 3] && faces[(i + 4) % 13]) {
            short soma = 0;
            for(short i = 0; i < 5; i ++) soma+=mao[i][1];
            return soma;
        }
    return 0;
}

short VerTrinca(const short mao[5][2]){
    short faces[13] = {0};
    for(short i = 0; i < 5; i ++) faces[mao[i][1]]++;
    for(short i = 0; i < 13; i++) if(faces[i]==3) return i+1;
    return 0;
}

short VerTwo(const short mao[5][2]){
    short faces[13] = {0};
    bool par1=false;
    for(short i = 0; i < 5; i ++) faces[mao[i][1]]++;
    for(short i = 0; i < 13; i++) {
        if(faces[i]==2 && par1) return i+1;
        else if(faces[i] == 2) par1=true;
    }
    return 0;
}

short VerPar(const short mao[5][2]){
    short faces[13] = {0};
    for(short i = 0; i < 5; i ++) faces[mao[i][1]]++;
    for(short i = 0; i < 13; i++) if(faces[i]==2) return i+1;
    return 0;
}

short VerQuaseS(const short mao[5][2]){
    short faces[13] = {0};
    for(short i = 0; i < 5; i ++) faces[mao[i][1]]++;
    for(short i = 0; i < 10; i ++)
        if(!(!faces[i]) + !(!faces[i + 1]) + !(!faces[i + 2]) + !(!faces[i + 3]) + !(!faces[(i + 4) % 13]) == 4) {
            if(faces[i] == faces[i+1] || faces[i] == faces[i+2]) return i + 1;
            else return i + 2;
        }
    return 0;
}

short VerQuaseS2(const short mao[5][2]){
    short faces[13] = {0};
    for(short i = 0; i < 5; i ++) faces[mao[i][1]]++;
    for(short i = 0; i < 10; i ++)
        if(!(!faces[i]) + !(!faces[i + 1]) + !(!faces[i + 2]) + !(!faces[i + 3]) + !(!faces[(i + 4) % 13]) == 3) {
            for(short j = 0; j < 4;j++){
                if(!faces[i+j]) return i+j+1;
            }
            return (i+4)%13 + 1;
        }
    return 0;
}

short VerQuaseFlush(const short mao[5][2], const short cabeca){
    short naipes[4] = {0};
    for(short i = 0; i < 5; i++) naipes[mao[i][0]]++;
    for(short i = 0; i < 4; i++) {
        if(naipes[i] == cabeca) return i + 1;
    }
    return 0;
}


