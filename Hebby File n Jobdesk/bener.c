#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUK 100

typedef struct {
    char merek[50];
    char ukuran[10];
    char warna[20];
    int banyak;
    float harga;
    char ulasan[100];
} Produk;

Produk daftarProduk[MAX_PRODUK];
int jumlahProduk = 0;

void simpanKeFile() {
    FILE *file = fopen("produk.txt", "w");
    if (file == NULL) {
        printf("Gagal menyimpan data ke file!\n");
        return;
    }

    for (int i = 0; i < jumlahProduk; i++) {
        fprintf(file, "%s %s %s %d %.2f \"%s\"\n",
                daftarProduk[i].merek,
                daftarProduk[i].ukuran,
                daftarProduk[i].warna,
                daftarProduk[i].banyak,
                daftarProduk[i].harga,
                daftarProduk[i].ulasan);
    }

    fclose(file);
}

void muatDariFile() {
    FILE *file = fopen("produk.txt", "r");
    if (file == NULL) {
        return; 
    }

    while (fscanf(file, "%s %s %s %d %f \"%[^\"]\"\n",
                  daftarProduk[jumlahProduk].merek,
                  daftarProduk[jumlahProduk].ukuran,
                  daftarProduk[jumlahProduk].warna,
                  &daftarProduk[jumlahProduk].banyak,
                  &daftarProduk[jumlahProduk].harga,
                  daftarProduk[jumlahProduk].ulasan) == 6) {
        jumlahProduk++;
    }

    fclose(file);
}

void tambahProduk() {
    if (jumlahProduk < MAX_PRODUK) {
        printf("Masukkan Merek Produk: ");
        scanf("%s", daftarProduk[jumlahProduk].merek);
        printf("Masukkan Ukuran Produk: ");
        scanf("%s", daftarProduk[jumlahProduk].ukuran);
        printf("Masukkan Warna Produk: ");
        scanf("%s", daftarProduk[jumlahProduk].warna);
        printf("Masukkan Stok Produk: ");
        scanf("%d", &daftarProduk[jumlahProduk].banyak);
        printf("Masukkan Harga Produk: ");
        scanf("%f", &daftarProduk[jumlahProduk].harga);
        strcpy(daftarProduk[jumlahProduk].ulasan, "-");

        jumlahProduk++;
        printf("Produk berhasil ditambahkan!\n");
    } else {
        printf("Kapasitas produk penuh!\n");
    }
}

void tampilkanProduk() {
    printf("\nDaftar Produk:\n");
    for (int i = 0; i < jumlahProduk; i++) {
        printf("%d. %s | %s | %s | Stok: %d | Harga: %.2f\n", i + 1,
               daftarProduk[i].merek,
               daftarProduk[i].ukuran,
               daftarProduk[i].warna,
               daftarProduk[i].banyak,
               daftarProduk[i].harga);
    }
}

void perbaruiProduk() {
    int idx;
    tampilkanProduk();
    printf("Pilih nomor produk yang akan diperbarui: ");
    scanf("%d", &idx);
    idx--;

    if (idx >= 0 && idx < jumlahProduk) {
        printf("Perbarui Harga Produk: ");
        scanf("%f", &daftarProduk[idx].harga);
        printf("Perbarui Stok Produk: ");
        scanf("%d", &daftarProduk[idx].banyak);
        printf("Produk berhasil diperbarui!\n");
    } else {
        printf("Produk tidak ditemukan.\n");
    }
}

void beriUlasan() {
    int idx;
    tampilkanProduk();
    printf("Pilih nomor produk untuk ulasan: ");
    scanf("%d", &idx);
    idx--;

    if (idx >= 0 && idx < jumlahProduk) {
        printf("Masukkan Ulasan: ");
        scanf(" %[^\n]s", daftarProduk[idx].ulasan);
        printf("Ulasan berhasil ditambahkan!\n");
    } else {
        printf("Produk tidak ditemukan.\n");
    }
}

void tampilkanUlasan() {
    printf("\nUlasan Produk:\n");
    for (int i = 0; i < jumlahProduk; i++) {
        if (strcmp(daftarProduk[i].ulasan, "-") != 0) {
            printf("%d. %s: %s\n", i + 1, daftarProduk[i].merek, daftarProduk[i].ulasan);
        }
    }
}

int main() {
    int pilihan;

    muatDariFile();

    do {
        printf("\n--- MENU PENJUAL ---\n");
        printf("1. Tambah Produk\n");
        printf("2. Tampilkan Produk\n");
        printf("3. Perbarui Produk\n");
        printf("4. Beri Ulasan\n");
        printf("5. Tampilkan Ulasan\n");
        printf("0. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: tambahProduk(); break;
            case 2: tampilkanProduk(); break;
            case 3: perbaruiProduk(); break;
            case 4: beriUlasan(); break;
            case 5: tampilkanUlasan(); break;
            case 0:
                simpanKeFile();
                printf("Data disimpan. Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);

    return 0;
}
