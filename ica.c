#include <stdio.h>
void tambahUlasan() {
    int pilih;
    char ulasan[100];
    int rating;

    printf("\n=== Tambah Ulasan ===\n");
    lihatRiwayat();

    printf("Pilih nomor transaksi: ");
    scanf("%d", &pilih);
    if (pilih < 1 || pilih > jumlahTransaksi || transaksi[pilih - 1].sudahUlas) {
        printf("❌ Pilihan tidak valid atau sudah diulas.\n");
        return;
    }

    printf("Masukkan rating (1–5): ");
    scanf("%d", &rating);
    getchar(); // buang newline

    printf("Masukkan ulasan: ");
    fgets(ulasan, sizeof(ulasan), stdin);
    strtok(ulasan, "\n");

    transaksi[pilih - 1].rating = rating;
    strcpy(transaksi[pilih - 1].ulasan, ulasan);
    transaksi[pilih - 1].sudahUlas = 1;

    simpanData();
    printf("✅ Ulasan berhasil disimpan.\n");
}

