#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int id;
    char nama[50];
    char kategori[30];
    float harga;
    int stok;
} Sepatu;


typedef struct {
    int id_pembeli;
    float saldo;
} SaldoPembeli;


typedef struct {
    int id_transaksi;
    int id_pembeli;
    int id_sepatu;
    char nama_sepatu[50];
    float jumlah;
    char tanggal[20];
} Transaksi;


void tampilkanMenuPembeli();
void lihatKatalogSepatu();
void topUpSaldo();
void beliSepatu();
void bersihkanBufferInput();
int dapatkanIdTransaksiBerikutnya();
void simpanTransaksi(int id_pembeli, int id_sepatu, const char* nama_sepatu, float jumlah);


#define FILE_SEPATU "sepatu.txt"
#define FILE_SALDO "saldo.txt"
#define FILE_TRANSAKSI "transaksi.txt"

int main() {
    int pilihan;
    int id_pembeli = 1001; 
    
    do {
        tampilkanMenuPembeli();
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);
        bersihkanBufferInput();
        
        switch(pilihan) {
            case 1:
                lihatKatalogSepatu();
                break;
            case 2:
                topUpSaldo();
                break;
            case 3:
                beliSepatu();
                break;
            case 0:
                printf("Kembali ke menu utama...\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
        
        if (pilihan != 0) {
            printf("\nTekan Enter untuk melanjutkan...");
            getchar();
        }
    } while (pilihan != 0);
    
    return 0;
}

void tampilkanMenuPembeli() {
    system("cls || clear");
    printf("=================================\n");
    printf("       DShoes - Menu Pembeli     \n");
    printf("=================================\n");
    printf("1. Lihat Katalog Sepatu\n");
    printf("2. Top Up Saldo\n");
    printf("3. Beli Sepatu\n");
    printf("0. Keluar\n");
    printf("=================================\n");
}

void lihatKatalogSepatu() {
    FILE *file = fopen(FILE_SEPATU, "r");
    if (file == NULL) {
    
        file = fopen(FILE_SEPATU, "w");
        

        fprintf(file, "1 Nike_Air_Max Running 1200000 10\n");
        fprintf(file, "2 Adidas_Ultraboost Running 1500000 8\n");
        fprintf(file, "3 Nike_Revolution Casual 800000 15\n");
        fprintf(file, "4 Adidas_Superstar Sneakers 900000 12\n");
        fclose(file);
        
    
        file = fopen(FILE_SEPATU, "r");
        if (file == NULL) {
            printf("Gagal membuka katalog sepatu.\n");
            return;
        }
    }

    printf("\n=== Katalog Sepatu ===\n");
    printf("ID  | Nama                 | Kategori       | Harga    | Stok\n");
    printf("----+----------------------+----------------+----------+-------\n");
    
    Sepatu sepatu;
    while (fscanf(file, "%d %49s %29s %f %d", 
                 &sepatu.id, sepatu.nama, sepatu.kategori, &sepatu.harga, &sepatu.stok) == 5) {

        for (char *p = sepatu.nama; *p; p++) if (*p == '_') *p = ' ';
        for (char *p = sepatu.kategori; *p; p++) if (*p == '_') *p = ' ';
        
        printf("%-3d | %-20s | %-14s | $%-7.2f | %-3d\n", 
               sepatu.id, sepatu.nama, sepatu.kategori, sepatu.harga, sepatu.stok);
    }
    
    fclose(file);
}

void topUpSaldo() {
    int id_pembeli = 1001; 
    float jumlah;
    
    printf("\n=== Top Up Saldo ===\n");
    
    
    FILE *file = fopen(FILE_SALDO, "r");
    SaldoPembeli saldo = {0, 0.0};
    
    if (file != NULL) {
        while (fscanf(file, "%d %f", &saldo.id_pembeli, &saldo.saldo) == 2) {
            if (saldo.id_pembeli == id_pembeli) {
                break;
            }
        }
        fclose(file);
    }
    
    printf("Saldo saat ini: $%.2f\n", saldo.saldo);
    printf("Masukkan jumlah top up: $");
    scanf("%f", &jumlah);
    bersihkanBufferInput();
    
    if (jumlah <= 0) {
        printf("Jumlah tidak valid. Harap masukkan nilai positif.\n");
        return;
    }
    
    
    saldo.id_pembeli = id_pembeli;
    saldo.saldo += jumlah;
    
    
    FILE *fileSementara = fopen("saldo_sementara.txt", "w");
    FILE *fileAsli = fopen(FILE_SALDO, "r");
    
    int ditemukan = 0;
    if (fileAsli != NULL) {
        SaldoPembeli temp;
        while (fscanf(fileAsli, "%d %f", &temp.id_pembeli, &temp.saldo) == 2) {
            if (temp.id_pembeli == id_pembeli) {
                fprintf(fileSementara, "%d %.2f\n", id_pembeli, saldo.saldo);
                ditemukan = 1;
            } else {
                fprintf(fileSementara, "%d %.2f\n", temp.id_pembeli, temp.saldo);
            }
        }
        fclose(fileAsli);
    }
    
    if (!ditemukan) {
        fprintf(fileSementara, "%d %.2f\n", id_pembeli, saldo.saldo);
    }
    
    fclose(fileSementara);
    
    
    remove(FILE_SALDO);
    rename("saldo_sementara.txt", FILE_SALDO);
    
    printf("Top up berhasil. Saldo baru: $%.2f\n", saldo.saldo);
}

void beliSepatu() {
    int id_pembeli = 1001;
    int id_sepatu;
    int jumlah;
    Sepatu sepatu_terpilih = {0};
    SaldoPembeli saldo = {0, 0.0};
    
    printf("\n=== Pembelian Sepatu ===\n");
    
    
    lihatKatalogSepatu();
    
    
    printf("\nMasukkan ID sepatu yang ingin dibeli: ");
    scanf("%d", &id_sepatu);
    bersihkanBufferInput();
    
    
    FILE *fileSepatu = fopen(FILE_SEPATU, "r");
    if (fileSepatu == NULL) {
        printf("Gagal mengakses katalog sepatu.\n");
        return;
    }
    
    int sepatu_ditemukan = 0;
    Sepatu sepatu;
    while (fscanf(fileSepatu, "%d %49s %29s %f %d", 
                 &sepatu.id, sepatu.nama, sepatu.kategori, &sepatu.harga, &sepatu.stok) == 5) {
        if (sepatu.id == id_sepatu) {
            sepatu_terpilih = sepatu;
            sepatu_ditemukan = 1;
            break;
        }
    }
    fclose(fileSepatu);
    
    if (!sepatu_ditemukan) {
        printf("Sepatu dengan ID %d tidak ditemukan.\n", id_sepatu);
        return;
    }
    
    
    for (char *p = sepatu_terpilih.nama; *p; p++) if (*p == '_') *p = ' ';
    for (char *p = sepatu_terpilih.kategori; *p; p++) if (*p == '_') *p = ' ';
    
    printf("Terpilih: %s (%s) - $%.2f\n", sepatu_terpilih.nama, sepatu_terpilih.kategori, sepatu_terpilih.harga);
    
    
    printf("Masukkan jumlah (tersedia: %d): ", sepatu_terpilih.stok);
    scanf("%d", &jumlah);
    bersihkanBufferInput();
    
    if (jumlah <= 0) {
        printf("Jumlah tidak valid.\n");
        return;
    }
    
    if (jumlah > sepatu_terpilih.stok) {
        printf("Stok tidak mencukupi.\n");
        return;
    }
    
    
    FILE *fileSaldo = fopen(FILE_SALDO, "r");
    if (fileSaldo == NULL) {
        printf("Gagal mengakses informasi saldo.\n");
        return;
    }
    
    int saldo_ditemukan = 0;
    while (fscanf(fileSaldo, "%d %f", &saldo.id_pembeli, &saldo.saldo) == 2) {
        if (saldo.id_pembeli == id_pembeli) {
            saldo_ditemukan = 1;
            break;
        }
    }
    fclose(fileSaldo);
    
    if (!saldo_ditemukan) {
        printf("Saldo pembeli tidak ditemukan.\n");
        return;
    }
    
    float total_harga = sepatu_terpilih.harga * jumlah;
    if (total_harga > saldo.saldo) {
        printf("Saldo tidak mencukupi. Total harga: $%.2f, Saldo Anda: $%.2f\n", total_harga, saldo.saldo);
        return;
    }
    
    
    printf("\nRingkasan Pembelian:\n");
    printf("Barang: %s (%s)\n", sepatu_terpilih.nama, sepatu_terpilih.kategori);
    printf("Jumlah: %d\n", jumlah);
    printf("Harga Satuan: $%.2f\n", sepatu_terpilih.harga);
    printf("Total Harga: $%.2f\n", total_harga);
    printf("Saldo Saat Ini: $%.2f\n", saldo.saldo);
    printf("Saldo Setelah Pembelian: $%.2f\n", saldo.saldo - total_harga);
    
    printf("\nKonfirmasi pembelian? (Y/N): ");
    char konfirmasi;
    scanf(" %c", &konfirmasi);
    bersihkanBufferInput();
    
    if (toupper(konfirmasi) != 'Y') {
        printf("Pembelian dibatalkan.\n");
        return;
    }
    
    
    FILE *fileSepatuSementara = fopen("sepatu_sementara.txt", "w");
    fileSepatu = fopen(FILE_SEPATU, "r");
    if (fileSepatu == NULL || fileSepatuSementara == NULL) {
        printf("Gagal memperbarui stok sepatu.\n");
        return;
    }
    
    while (fscanf(fileSepatu, "%d %49s %29s %f %d", 
                 &sepatu.id, sepatu.nama, sepatu.kategori, &sepatu.harga, &sepatu.stok) == 5) {
        if (sepatu.id == id_sepatu) {
            sepatu.stok -= jumlah;
        }
        fprintf(fileSepatuSementara, "%d %s %s %.2f %d\n", 
               sepatu.id, sepatu.nama, sepatu.kategori, sepatu.harga, sepatu.stok);
    }
    fclose(fileSepatu);
    fclose(fileSepatuSementara);
    
    remove(FILE_SEPATU);
    rename("sepatu_sementara.txt", FILE_SEPATU);
    

    saldo.saldo -= total_harga;
    
    FILE *fileSaldoSementara = fopen("saldo_sementara.txt", "w");
    fileSaldo = fopen(FILE_SALDO, "r");
    if (fileSaldo == NULL || fileSaldoSementara == NULL) {
        printf("Gagal memperbarui saldo.\n");
        return;
    }
    
    SaldoPembeli tempSaldo;
    while (fscanf(fileSaldo, "%d %f", &tempSaldo.id_pembeli, &tempSaldo.saldo) == 2) {
        if (tempSaldo.id_pembeli == id_pembeli) {
            fprintf(fileSaldoSementara, "%d %.2f\n", id_pembeli, saldo.saldo);
        } else {
            fprintf(fileSaldoSementara, "%d %.2f\n", tempSaldo.id_pembeli, tempSaldo.saldo);
        }
    }
    fclose(fileSaldo);
    fclose(fileSaldoSementara);
    
    remove(FILE_SALDO);
    rename("saldo_sementara.txt", FILE_SALDO);
    
    
    simpanTransaksi(id_pembeli, id_sepatu, sepatu_terpilih.nama, total_harga);
    
    printf("\nPembelian berhasil!\n");
    printf("Saldo baru: $%.2f\n", saldo.saldo);
}

void simpanTransaksi(int id_pembeli, int id_sepatu, const char* nama_sepatu, float jumlah) {
    FILE *file = fopen(FILE_TRANSAKSI, "a");
    if (file == NULL) {
        printf("Gagal mencatat transaksi.\n");
        return;
    }
    
    int id_transaksi = dapatkanIdTransaksiBerikutnya();
    
    
    char tanggal[20] = "2023-11-15"; 
    

    char nama_sepatu_disimpan[50];
    strcpy(nama_sepatu_disimpan, nama_sepatu);
    for (char *p = nama_sepatu_disimpan; *p; p++) {
        if (*p == ' ') *p = '_';
    }
    
    fprintf(file, "%d %d %d %s %.2f %s\n", 
           id_transaksi, id_pembeli, id_sepatu, nama_sepatu_disimpan, jumlah, tanggal);
    fclose(file);
}

int dapatkanIdTransaksiBerikutnya() {
    FILE *file = fopen(FILE_TRANSAKSI, "r");
    if (file == NULL) {
        return 1;
    }
    
    int id_tertinggi = 0;
    Transaksi transaksi;
    while (fscanf(file, "%d %d %d %49s %f %19s", 
                 &transaksi.id_transaksi, &transaksi.id_pembeli, 
                 &transaksi.id_sepatu, transaksi.nama_sepatu, 
                 &transaksi.jumlah, transaksi.tanggal) == 6) {
        if (transaksi.id_transaksi > id_tertinggi) {
            id_tertinggi = transaksi.id_transaksi;
        }
    }
    fclose(file);
    
    return id_tertinggi + 1;
}

void bersihkanBufferInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}