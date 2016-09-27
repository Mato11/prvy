#include <stdio.h>


void vymen_riadky (float *matica, int p_stlpcov, int r1, int r2){
    float swap[p_stlpcov];
    for (int j=0; j < p_stlpcov; j++) {                     // alokacia swap
        swap[j] = *((matica + r1*p_stlpcov) + j);
    }
    for (int j=0; j < p_stlpcov; j++) {                     // r2 za r1
        *((matica + r1*p_stlpcov) + j) = *((matica + r2*p_stlpcov) + j);
    }
    for (int j=0; j < p_stlpcov; j++) {                     // swap do r2
        *((matica + r2*p_stlpcov) + j) = swap[j];
    }
}

void vypis_maticu (float *matica, int p_riadkov, int p_stlpcov){
    printf("\n");
    for (int i=0; i<p_riadkov; i++) {
        for (int j=0; j<p_stlpcov; j++) {
            printf("%f ", *((matica + i*p_stlpcov)+ j) );
        }
        printf("\n");
    }
    printf("\n");
}

void zadaj_maticu (float *matica, int p_riadkov, int p_stlpcov){
    printf("Zadaj elementy po riadkoch\n");
    for (int i=0; i < p_riadkov; i++) {
        for (int j=0; j < p_stlpcov; j++) {
            scanf("%f", &*((matica + i*p_stlpcov)+ j) );                    // nacitavanie prvkov po riadkoch
        }
        printf("riadok\n");
    }
}

void gauss (float *matica, int p_riadkov, int p_stlpcov){
    
    for (int i=0; i < p_riadkov; i++) {
        for (int j= (p_stlpcov-1); j >= 0; j--){
            for (int m=i; m < p_riadkov; m++) {
                if ((*((matica + i*p_stlpcov + i))) == 0 && (*((matica + (i+m)*p_stlpcov + i))) != 0) {
                    vymen_riadky((float *)matica, p_stlpcov, i, (i+m));
                    break;
                }
            }
            if ( (*((matica + i*p_stlpcov + i))) != 0 ) {
                *((matica + i*p_stlpcov) + j) /= (*((matica + i*p_stlpcov + i)));          //vydeli riadok diagonalnym prvkom
            }
        }
        //vypis_maticu((float *)matica, p_riadkov, p_stlpcov);

        for (int k = i; (k+1) < p_riadkov; k++) {                           // nuluje pod diagonalov
            float nasobok = (*((matica + (k+1)*p_stlpcov) + i));
            for (int l = (p_stlpcov - 1) ; l >= 0; l--) {
                *((matica + (k+1)*p_stlpcov) + l) -= (nasobok * (*((matica + i*p_stlpcov) + l)));     // odcita riadok od zvysnych pod nim
            }
            //vypis_maticu((float *)matica, p_riadkov, p_stlpcov);
        }
        //vypis_maticu((float *)matica, p_riadkov, p_stlpcov);
    }
    
    //vypis_maticu((float *)matica, p_riadkov, p_stlpcov);
    
    for (int i = (p_riadkov - 1); i > 0; i--) {                                                 //nuluje nad diagonalov
        for (int k = i; k > 0; k--) {
            float nasobok = (*((matica + (k-1)*p_stlpcov) + i));
            for (int j = 0; j < p_stlpcov ; j++) {
                *((matica + (k-1)*p_stlpcov) + j) -= (nasobok * (*((matica + i*p_stlpcov) + j)));
            }
        }
        //vypis_maticu((float *)matica, p_riadkov, p_stlpcov);
    }
}

void kopia_matice(float *M1, float *M2, int p_riadkov, int p_stlpcov){
    for (int i = 0; i < p_riadkov; i++) {
        for (int j = 0; j < p_stlpcov; j++) {
            *((M2 + i*p_stlpcov) + j) = *((M1 + i*p_stlpcov) + j);
        }
    }
}

void skuska (float *Vypocitana, float *Povodna, int p_riadkov, int p_stlpcov){
    for (int i = 0; i < p_riadkov; i++) {
        float Lava_Strana = 0;
        for (int j = 0; j < p_stlpcov; j++) {
            Lava_Strana += ((*((Povodna + i*p_stlpcov) + j)) * (*((Vypocitana + j*p_stlpcov) + (p_stlpcov - 1))));
        }
        printf("%f = %f\n", Lava_Strana, *((Povodna + i*p_stlpcov) + (p_stlpcov-1)));
    }
}

int main(){
    int r,c;
    
    printf("Zadaj pocet riadkov\n");
    scanf("%d", &r);
    
    printf("Zadaj pocet stlpcov\n");
    scanf("%d", &c);
    
    float A[r][c];
    float Povodna[r][c];
    
    zadaj_maticu((float *)A, r, c);
    kopia_matice((float *)A, (float *)Povodna, r, c);
    
    gauss((float *)A, r, c);
    
    printf("Zadana matica\n");
    vypis_maticu((float *)Povodna, r, c);
    
    printf("Vypocitana matica\n");
    vypis_maticu((float *)A, r, c);
    
    if (c == (r+1)) {
        printf("Skuska\n");
        skuska((float *)A, (float *)Povodna, r, c);
    }
    
    
    
    return 0;
}
