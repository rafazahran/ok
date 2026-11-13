#include <stdio.h>
#include <stdlib.h>


struct bunga{
int urutan;
int tinggi;
struct bunga *next;
struct bunga *prev;
};


struct pembanding{
int urutan;
int tinggi;
struct pembanding *next;
struct pembanding *prev;
};


struct bungatidakkena{
int urutan;
struct bungatidakkena *prev;
struct bungatidakkena *next;
};
   
struct bunga *awalbunga = NULL;


void deletenode(int urutan);


int main(){
struct bunga *bunga, *akhirbunga = NULL;
struct pembanding *pembanding, *akhirpembanding = NULL;
struct bungatidakkena *bungatidakkena = NULL, *awalhasil = NULL;
int jumlahbunga=0;
int Ntidakkena=0;
int pemisah;


/* Input dan pembentukan kedua linked list. */
while (1) {
bunga = malloc(sizeof *bunga);
pembanding = malloc(sizeof *pembanding);


bunga->urutan = jumlahbunga + 1;
pembanding->urutan = bunga->urutan;
scanf("%d", &bunga->tinggi);
pembanding->tinggi = bunga->tinggi;


bunga->prev = akhirbunga;
bunga->next = NULL;
if (akhirbunga != NULL) akhirbunga->next = bunga;
else awalbunga = bunga;
akhirbunga = bunga;


pembanding->prev = akhirpembanding;
pembanding->next = NULL;
if (akhirpembanding != NULL) akhirpembanding->next = pembanding;
akhirpembanding = pembanding;
jumlahbunga++;


do{
pemisah = getchar();
} while (pemisah == ' ' || pemisah == '\t' || pemisah == '\r');
if (pemisah == '\n' || pemisah == EOF) break;
ungetc(pemisah, stdin);
}


/* Bunga maju, pembanding ditelusuri dari belakang. */
bunga = awalbunga;
for (int i = 0; i < jumlahbunga; i++) {
int kiri = 0, kanan = 0;
struct bunga *berikut = bunga->next;
pembanding = akhirpembanding;


for (int j = 0; j < jumlahbunga; j++) {
if (bunga->tinggi < pembanding->tinggi) {
if (pembanding->urutan < bunga->urutan) kiri = 1;
if (pembanding->urutan > bunga->urutan) kanan = 1;
}
pembanding = pembanding->prev;
}


if (kiri && kanan) {
struct bungatidakkena *baru = malloc(sizeof *baru);
baru->urutan = bunga->urutan;
baru->prev = bungatidakkena;
baru->next = NULL;
if (bungatidakkena != NULL) bungatidakkena->next = baru;
else awalhasil = baru;
bungatidakkena = baru;
Ntidakkena++;
deletenode(bunga->urutan);
}
bunga = berikut;
}


bungatidakkena = awalhasil;
if (bungatidakkena ==NULL) printf("NONE");
else {
for (int i = 0; i< Ntidakkena;i++) {
printf("%d", bungatidakkena->urutan);
if (bungatidakkena->next !=NULL) printf(" ");
bungatidakkena = bungatidakkena->next;
}
}
printf("\n");
return 0;
}


void deletenode(int urutan){
struct bunga *bunga = awalbunga;
while (bunga->urutan != urutan) bunga = bunga->next;


if (bunga->prev != NULL) bunga->prev->next = bunga->next;
else awalbunga = bunga->next;
if (bunga->next != NULL) bunga->next->prev = bunga->prev;
free(bunga);
}
