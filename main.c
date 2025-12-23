#include <stdio.h>
#include <string.h>

struct yardim {
    char birim[10];
    float toplam;
};

void ekle(struct yardim dizi[], int *sayac, char *birim, float miktar);
void yazdir(struct yardim dizi[], int adet);

int main() {
    struct yardim kayitlar[31];
    int kayitSayisi = 0;
    float tempMiktar;
    char tempBirim[10];

    FILE *dosya = fopen("yardim.txt", "r");
    if (dosya == NULL) {
        return 1;
    }

    while (fscanf(dosya, "%f %s", &tempMiktar, tempBirim) != EOF) {
        ekle(kayitlar, &kayitSayisi, tempBirim, tempMiktar);
    }
    fclose(dosya);

    yazdir(kayitlar, kayitSayisi);

    return 0;
}

void ekle(struct yardim dizi[], int *sayac, char *birim, float miktar) {
    int i;
    int bulundu = 0;

    for (i = 0; i < *sayac; i++) {
        if (strcmp(dizi[i].birim, birim) == 0) {
            dizi[i].toplam += miktar;
            bulundu = 1;
            break;
        }
    }

    if (bulundu == 0 && *sayac < 31) {
        strcpy(dizi[*sayac].birim, birim);
        dizi[*sayac].toplam = miktar;
        (*sayac)++;
    }
}

void yazdir(struct yardim dizi[], int adet) {
    struct yardim gecici;
    int i, j;

    for (i = 0; i < adet - 1; i++) {
        for (j = 0; j < adet - 1 - i; j++) {
            if (dizi[j].toplam < dizi[j + 1].toplam) {
                gecici = dizi[j];
                dizi[j] = dizi[j + 1];
                dizi[j + 1] = gecici;
            }
        }
    }

    FILE *cikti = fopen("toplam.txt", "w");
    if (cikti == NULL) {
        return;
    }

    for (i = 0; i < adet; i++) {
        fprintf(cikti, "%s %.2f\n", dizi[i].birim, dizi[i].toplam);
    }

    fclose(cikti);
}