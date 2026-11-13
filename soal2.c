/*
Nama: Rafa Zahran Ramadhan
NIM: 13224102
Modul: 2 - Dynamic Structures
Soal no: 2 - Peternak Bunga Matahari
Deskripsi: Mencari posisi bunga yang memiliki bunga
lebih tinggi di sisi kiri dan sisi kanannya.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct bunga {
    int urutan, tinggi;
    struct bunga *next, *prev;
} Bunga;

typedef struct bungatidakkena {
    int urutan;
    struct bungatidakkena *prev, *next;
} Hasil;

Bunga *awal = NULL, *akhir = NULL;
void deletenode(int urutan);
void bersihkan(Hasil *bungatidakkena);

int main(void) {
    Bunga *bunga = NULL, *pembanding = NULL;
    Hasil *bungatidakkena = NULL, *akhirhasil = NULL;
    int jumlahbunga = 0, Ntidakkena = 0;
    int tinggi, pemisah;

    /* Baca tinggi sampai akhir satu baris atau EOF. */
    while (scanf("%d", &tinggi) == 1) {
        bunga = malloc(sizeof *bunga);
        if (bunga == NULL) {
            bersihkan(bungatidakkena);
            return 1;
        }
        bunga->urutan = ++jumlahbunga;
        bunga->tinggi = tinggi;
        bunga->prev = akhir;
        bunga->next = NULL;
        if (akhir != NULL) akhir->next = bunga;
        else awal = bunga;
        akhir = bunga;

        do { pemisah = getchar(); }
        while (pemisah == ' ' || pemisah == '\t' ||
               pemisah == '\r');
        if (pemisah == '\n' || pemisah == EOF) break;
        ungetc(pemisah, stdin);
    }
bunga = awal;
    while (bunga != NULL) {
        int kiri = 0, kanan = 0;
        Bunga *berikut = bunga->next;
        pembanding = bunga->prev;
        while (pembanding != NULL) {
            if (bunga->tinggi < pembanding->tinggi) {
                kiri = 1;
                break;
            }
            pembanding = pembanding->prev;
        }
        pembanding = bunga->next;
        while (pembanding != NULL) {
            if (bunga->tinggi < pembanding->tinggi) {
                kanan = 1;
                break;
            }
            pembanding = pembanding->next;
        }
        if (kiri && kanan) {
            Hasil *baru = malloc(sizeof *baru);
            if (baru == NULL) {
                bersihkan(bungatidakkena);
                return 1;
            }
            baru->urutan = bunga->urutan;
            baru->prev = akhirhasil;
            baru->next = NULL;
            if (akhirhasil != NULL) akhirhasil->next = baru;
            else bungatidakkena = baru;
            akhirhasil = baru;
            Ntidakkena++;
            deletenode(bunga->urutan);
        }
        bunga = berikut;
    }

    if (Ntidakkena == 0) printf("NONE");
    else {
        Hasil *hasil = bungatidakkena;
        while (hasil != NULL) {
            printf("%d", hasil->urutan);
            if (hasil->next != NULL) printf(" ");
            hasil = hasil->next;
        }
    }
    printf("\n");
    bersihkan(bungatidakkena);
    return 0;
}
void deletenode(int urutan) {
    Bunga *node = awal;
    while (node != NULL && node->urutan != urutan)
        node = node->next;
    if (node == NULL) return;
    if (node->prev != NULL) node->prev->next = node->next;
    else awal = node->next;
    if (node->next != NULL) node->next->prev = node->prev;
    else akhir = node->prev;
    free(node);
}

void bersihkan(Hasil *bungatidakkena) {
    while (awal != NULL) {
        Bunga *berikut = awal->next;
        free(awal);
        awal = berikut;
    }
    akhir = NULL;
    while (bungatidakkena != NULL) {
        Hasil *berikut = bungatidakkena->next;
        free(bungatidakkena);
        bungatidakkena = berikut;
    }
}
