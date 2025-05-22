void lihatRiwayatDanUlasan(int id_pembeli) {
    FILE *file = fopen(FILE_TRANSAKSI, "r");
    if (file == NULL) {
        printf("Belum ada riwayat pembelian.\n");
        return;
    }

    Transaksi daftar[100];
    int total = 0;

    printf("\n=== Riwayat Pembelian ===\n");
    printf("No | Nama Sepatu           | Total   | Tanggal     | Rating | Ulasan\n");
    printf("----+------------------------+---------+-------------+--------+----------------\n");

    while (fscanf(file, "%d %d %d %49s %f %19s %d %99[^\n]",
                  &daftar[total].id_transaksi,
                  &daftar[total].id_pembeli,
                  &daftar[total].id_sepatu,
                  daftar[total].nama_sepatu,
                  &daftar[total].jumlah,
                  daftar[total].tanggal,
                  &daftar[total].rating,
                  daftar[total].ulasan) == 8) {
        if (daftar[total].id_pembeli == id_pembeli) {
            for (char *p = daftar[total].nama_sepatu; *p; p++) if (*p == '_') *p = ' ';
            printf("%-2d | %-22s | $%-6.2f | %-11s | %-6d | %s\n",
                   total + 1,
                   daftar[total].nama_sepatu,
                   daftar[total].jumlah,
                   daftar[total].tanggal,
                   daftar[total].rating,
                   daftar[total].rating > 0 ? daftar[total].ulasan : "-");
            total++;
        }
    }
    fclose(file);

    if (total == 0) {
        printf("Belum ada transaksi.\n");
        return;
    }

    // Tanya apakah ingin menambahkan ulasan
    char jawab;
    printf("\nApakah Anda ingin memberikan ulasan? (y/n): ");
    scanf(" %c", &jawab);
    getchar(); // buang newline

    if (tolower(jawab) != 'y') return;

    int pilih;
    printf("Masukkan nomor transaksi untuk diberi ulasan: ");
    scanf("%d", &pilih);
    getchar(); // buang newline

    if (pilih < 1 || pilih > total) {
        printf("Pilihan tidak valid.\n");
        return;
    }

    if (daftar[pilih - 1].rating > 0) {
        printf("Transaksi ini sudah memiliki ulasan.\n");
        return;
    }

    int rating;
    char ulasan[100];

    printf("Masukkan rating (1–5): ");
    scanf("%d", &rating);
    getchar();

    if (rating < 1 || rating > 5) {
        printf("Rating harus antara 1 dan 5.\n");
        return;
    }

    printf("Masukkan ulasan: ");
    fgets(ulasan, sizeof(ulasan), stdin);
    strtok(ulasan, "\n");

    // Tulis ulang semua data transaksi
    FILE *lama = fopen(FILE_TRANSAKSI, "r");
    FILE *baru = fopen("transaksi_temp.txt", "w");
    Transaksi temp;
    int nomor = 0;

    while (fscanf(lama, "%d %d %d %49s %f %19s %d %99[^\n]",
                  &temp.id_transaksi, &temp.id_pembeli, &temp.id_sepatu,
                  temp.nama_sepatu, &temp.jumlah, temp.tanggal,
                  &temp.rating, temp.ulasan) == 8) {
        nomor++;

        if (nomor == pilih && temp.id_pembeli == id_pembeli && temp.rating == 0) {
            temp.rating = rating;
            strcpy(temp.ulasan, ulasan);
        }

        fprintf(baru, "%d %d %d %s %.2f %s %d %s\n",
                temp.id_transaksi, temp.id_pembeli, temp.id_sepatu,
                temp.nama_sepatu, temp.jumlah, temp.tanggal,
                temp.rating, temp.ulasan);
    }

    fclose(lama);
    fclose(baru);
    remove(FILE_TRANSAKSI);
    rename("transaksi_temp.txt", FILE_TRANSAKSI);

    printf("Ulasan berhasil disimpan.\n");
}