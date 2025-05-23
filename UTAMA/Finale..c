#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAKS_PENGGUNA 100
#define MAKS_PRODUK 100
#define MAKS_TRANSAKSI 100
#define MAKS_ULASAN 100
#define PANJANG_STRING_MAKS 50

// Struktur data untuk Pengguna
typedef struct {
    char nama_pengguna[PANJANG_STRING_MAKS];
    char kata_sandi[PANJANG_STRING_MAKS];
    float saldo;
    int adalah_penjual;
    int aktif;
} Pengguna;

// Struktur data untuk Produk
typedef struct {
    char merek[PANJANG_STRING_MAKS];
    int ukuran;
    float harga;
    char warna[PANJANG_STRING_MAKS];
    int stok;
    char penjual[PANJANG_STRING_MAKS];
    int aktif;
} Produk;

// Struktur data untuk Transaksi
typedef struct {
    char pembeli[PANJANG_STRING_MAKS];
    char merek_produk[PANJANG_STRING_MAKS];
    int ukuran_produk;
    char warna_produk[PANJANG_STRING_MAKS];
    float jumlah;
    time_t waktu;
} Transaksi;

// Struktur data untuk Ulasan
typedef struct {
    char pembeli[PANJANG_STRING_MAKS];
    char merek_produk[PANJANG_STRING_MAKS];
    char komentar[PANJANG_STRING_MAKS * 2];
    int peringkat;
    time_t waktu;
} Ulasan;

// Variabel global
Pengguna pengguna[MAKS_PENGGUNA];
Produk produk[MAKS_PRODUK];
Transaksi transaksi[MAKS_TRANSAKSI];
Ulasan ulasan[MAKS_ULASAN];
int jumlah_pengguna = 0;
int jumlah_produk = 0;
int jumlah_transaksi = 0;
int jumlah_ulasan = 0;
Pengguna *pengguna_saat_ini = NULL;

// Fungsi utilitas
void bersihkan_buffer_masukan() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void ubah_ke_huruf_kecil(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void cetak_judul(const char *judul) {
    printf("\n=== %s ===\n", judul);
}

void tekan_enter_untuk_lanjut() {
    printf("\nTekan Enter untuk melanjutkan...");
    bersihkan_buffer_masukan();
    getchar();
}

// Fungsi manajemen data
// Jobdesk: All team members (data storage foundation)
// Feature: Penyimpanan data berbasis file
void muat_data() {
    // Implementasi loading data dari file (disederhanakan)
    // Dalam implementasi nyata, ini akan membaca dari file
    printf("Memuat data...\n");
    
    // Contoh data dummy untuk testing
    if (jumlah_pengguna == 0) {
        strcpy(pengguna[0].nama_pengguna, "penjual1");
        strcpy(pengguna[0].kata_sandi, "pass1");
        pengguna[0].saldo = 0;
        pengguna[0].adalah_penjual = 1;
        pengguna[0].aktif = 1;
        
        strcpy(pengguna[1].nama_pengguna, "pembeli1");
        strcpy(pengguna[1].kata_sandi, "pass1");
        pengguna[1].saldo = 1000;
        pengguna[1].adalah_penjual = 0;
        pengguna[1].aktif = 1;
        
        jumlah_pengguna = 2;
    }
    
    if (jumlah_produk == 0) {
        strcpy(produk[0].merek, "Nike");
        produk[0].ukuran = 42;
        produk[0].harga = 500;
        strcpy(produk[0].warna, "Hitam");
        produk[0].stok = 10;
        strcpy(produk[0].penjual, "penjual1");
        produk[0].aktif = 1;
        
        jumlah_produk = 1;
    }
}

// Jobdesk: All team members (data storage foundation)
// Feature: Penyimpanan data berbasis file
void simpan_data() {
    // Implementasi penyimpanan data ke file (disederhanakan)
    printf("Menyimpan data...\n");
}

// Fungsi autentikasi
// Jobdesk: Aufa (Registrasi User)
// Feature: Multi-role user (Pembeli/Penjual)
int daftar_pengguna(int adalah_penjual) {
    if (jumlah_pengguna >= MAKS_PENGGUNA) {
        printf("Batas maksimum pengguna tercapai.\n");
        return 0;
    }
    
    Pengguna pengguna_baru;
    pengguna_baru.adalah_penjual = adalah_penjual;
    pengguna_baru.saldo = 0;
    pengguna_baru.aktif = 1;
    
    printf("Masukkan nama pengguna: ");
    scanf("%49s", pengguna_baru.nama_pengguna);
    bersihkan_buffer_masukan();
    
    // Cek nama pengguna sudah ada
    for (int i = 0; i < jumlah_pengguna; i++) {
        if (strcmp(pengguna[i].nama_pengguna, pengguna_baru.nama_pengguna) == 0) {
            printf("Nama pengguna sudah ada.\n");
            return 0;
        }
    }
    
    printf("Masukkan kata sandi: ");
    scanf("%49s", pengguna_baru.kata_sandi);
    bersihkan_buffer_masukan();
    
    pengguna[jumlah_pengguna++] = pengguna_baru;
    printf("Pendaftaran berhasil!\n");
    
    simpan_data();
    return 1;
}

// Jobdesk: Bara (Login)
// Feature: Multi-role user (Pembeli/Penjual)
int masuk_pengguna() {
    char nama_pengguna[PANJANG_STRING_MAKS];
    char kata_sandi[PANJANG_STRING_MAKS];
    int percobaan = 0;
    const int batas_percobaan = 3;
    
    while (percobaan < batas_percobaan) {
        printf("Masukkan nama pengguna: ");
        scanf("%49s", nama_pengguna);
        bersihkan_buffer_masukan();
        
        printf("Masukkan kata sandi: ");
        scanf("%49s", kata_sandi);
        bersihkan_buffer_masukan();
        
        for (int i = 0; i < jumlah_pengguna; i++) {
            if (strcmp(pengguna[i].nama_pengguna, nama_pengguna) == 0 && 
                strcmp(pengguna[i].kata_sandi, kata_sandi) == 0 &&
                pengguna[i].aktif) {
                pengguna_saat_ini = &pengguna[i];
                printf("Masuk berhasil! Selamat datang, %s.\n", nama_pengguna);
                return 1;
            }
        }
        
        percobaan++;
        int sisa_percobaan = batas_percobaan - percobaan;
        if (sisa_percobaan > 0) {
            printf("Nama pengguna atau kata sandi salah. Sisa percobaan: %d.\n", sisa_percobaan);
        } else {
            printf("Anda telah melebihi batas percobaan masuk. Kembali ke menu utama.\n");
            return 0;
        }
    }
    
    return 0;
}

// Jobdesk: Bara (Login)
// Feature: Multi-role user (Pembeli/Penjual)
void keluar() {
    pengguna_saat_ini = NULL;
    printf("Keluar berhasil.\n");
}

// Jobdesk: Bara (Ganti Password)
// Feature: Multi-role user (Pembeli/Penjual)
void ganti_kata_sandi() {
    if (!pengguna_saat_ini) {
        printf("Anda harus masuk untuk mengganti kata sandi.\n");
        return;
    }
    
    char kata_sandi_lama[PANJANG_STRING_MAKS];
    char kata_sandi_baru[PANJANG_STRING_MAKS];
    
    printf("Masukkan kata sandi lama: ");
    scanf("%49s", kata_sandi_lama);
    bersihkan_buffer_masukan();
    
    if (strcmp(pengguna_saat_ini->kata_sandi, kata_sandi_lama) != 0) {
        printf("Kata sandi lama salah.\n");
        return;
    }
    
    printf("Masukkan kata sandi baru: ");
    scanf("%49s", kata_sandi_baru);
    bersihkan_buffer_masukan();
    
    strcpy(pengguna_saat_ini->kata_sandi, kata_sandi_baru);
    printf("Kata sandi berhasil diganti.\n");
    
    simpan_data();
}

// Fungsi pembeli
// Jobdesk: Alif (Katalog)
// Feature: Multi-role user (Pembeli), Manajemen produk lengkap
void lihat_katalog() {
    cetak_judul("KATALOG PRODUK");
    
    if (jumlah_produk == 0) {
        printf("Tidak ada produk yang tersedia.\n");
        return;
    }
    
    printf("%-20s %-10s %-10s %-15s %-10s %-15s\n", 
           "Merek", "Ukuran", "Harga", "Warna", "Stok", "Penjual");
    printf("----------------------------------------------------------------\n");
    
    for (int i = 0; i < jumlah_produk; i++) {
        if (produk[i].aktif) {
            printf("%-20s %-10d %-10.2f %-15s %-10d %-15s\n", 
                   produk[i].merek, produk[i].ukuran, produk[i].harga, 
                   produk[i].warna, produk[i].stok, produk[i].penjual);
        }
    }
}

// Jobdesk: Alif (Top Up)
// Feature: Sistem transaksi dengan saldo
void isi_saldo() {
    if (!pengguna_saat_ini || pengguna_saat_ini->adalah_penjual) {
        printf("Hanya pembeli yang dapat mengisi saldo.\n");
        return;
    }
    
    float jumlah;
    printf("Masukkan jumlah untuk mengisi saldo: ");
    scanf("%f", &jumlah);
    bersihkan_buffer_masukan();
    
    if (jumlah <= 0) {
        printf("Jumlah harus positif.\n");
        return;
    }
    
    pengguna_saat_ini->saldo += jumlah;
    printf("Pengisian saldo berhasil. Saldo baru: %.2f\n", pengguna_saat_ini->saldo);
    
    simpan_data();
}

// Jobdesk: Alif (Pembelian)
// Feature: Sistem transaksi dengan saldo
void beli_sepatu() {
    if (!pengguna_saat_ini || pengguna_saat_ini->adalah_penjual) {
        printf("Hanya pembeli yang dapat membeli sepatu.\n");
        return;
    }
    
    lihat_katalog();
    
    char merek[PANJANG_STRING_MAKS];
    int ukuran;
    char warna[PANJANG_STRING_MAKS];
    
    printf("\nMasukkan merek sepatu untuk dibeli: ");
    scanf("%49s", merek);
    bersihkan_buffer_masukan();
    
    printf("Masukkan ukuran: ");
    scanf("%d", &ukuran);
    bersihkan_buffer_masukan();
    
    printf("Masukkan warna: ");
    scanf("%49s", warna);
    bersihkan_buffer_masukan();
    
    // Cari produk
    int indeks_produk = -1;
    for (int i = 0; i < jumlah_produk; i++) {
        if (produk[i].aktif && 
            strcasecmp(produk[i].merek, merek) == 0 &&
            produk[i].ukuran == ukuran &&
            strcasecmp(produk[i].warna, warna) == 0) {
            indeks_produk = i;
            break;
        }
    }
    
    if (indeks_produk == -1) {
        printf("Produk tidak ditemukan.\n");
        return;
    }
    
    if (produk[indeks_produk].stok <= 0) {
        printf("Produk kehabisan stok.\n");
        return;
    }
    
    if (pengguna_saat_ini->saldo < produk[indeks_produk].harga) {
        printf("Saldo tidak cukup. Silakan isi saldo terlebih dahulu.\n");
        return;
    }
    
    // Proses pembelian
    pengguna_saat_ini->saldo -= produk[indeks_produk].harga;
    
    // Tambahkan ke saldo penjual
    for (int i = 0; i < jumlah_pengguna; i++) {
        if (strcmp(pengguna[i].nama_pengguna, produk[indeks_produk].penjual) == 0) {
            pengguna[i].saldo += produk[indeks_produk].harga;
            break;
        }
    }
    
    produk[indeks_produk].stok--;
    
    // Catat transaksi
    if (jumlah_transaksi < MAKS_TRANSAKSI) {
        strcpy(transaksi[jumlah_transaksi].pembeli, pengguna_saat_ini->nama_pengguna);
        strcpy(transaksi[jumlah_transaksi].merek_produk, produk[indeks_produk].merek);
        transaksi[jumlah_transaksi].ukuran_produk = produk[indeks_produk].ukuran;
        strcpy(transaksi[jumlah_transaksi].warna_produk, produk[indeks_produk].warna);
        transaksi[jumlah_transaksi].jumlah = produk[indeks_produk].harga;
        transaksi[jumlah_transaksi].waktu = time(NULL);
        jumlah_transaksi++;
    }
    
    printf("Pembelian berhasil! Saldo tersisa: %.2f\n", pengguna_saat_ini->saldo);
    
    simpan_data();
}

// Jobdesk: Ica (Riwayat Transaksi)
// Feature: Sistem transaksi dengan saldo
void lihat_riwayat_pembelian() {
    if (!pengguna_saat_ini || pengguna_saat_ini->adalah_penjual) {
        printf("Hanya pembeli yang dapat melihat riwayat pembelian.\n");
        return;
    }
    
    cetak_judul("RIWAYAT PEMBELIAN");
    
    int ditemukan = 0;
    for (int i = 0; i < jumlah_transaksi; i++) {
        if (strcmp(transaksi[i].pembeli, pengguna_saat_ini->nama_pengguna) == 0) {
            ditemukan = 1;
            char waktu_str[20];
            strftime(waktu_str, 20, "%Y-%m-%d %H:%M:%S", localtime(&transaksi[i].waktu));
            
            printf("Tanggal: %s\n", waktu_str);
            printf("Produk: %s (Ukuran: %d, Warna: %s)\n", 
                   transaksi[i].merek_produk, transaksi[i].ukuran_produk, transaksi[i].warna_produk);
            printf("Jumlah: %.2f\n\n", transaksi[i].jumlah);
        }
    }
    
    if (!ditemukan) {
        printf("Tidak ada riwayat pembelian ditemukan.\n");
    }
}

// Jobdesk: Ica (Ulasan)
// Feature: Ulasan dan rating produk
void tambah_ulasan() {
    if (!pengguna_saat_ini || pengguna_saat_ini->adalah_penjual) {
        printf("Hanya pembeli yang dapat menambah ulasan.\n");
        return;
    }
    
    // Cek apakah pembeli pernah membeli produk
    int punya_pembelian = 0;
    for (int i = 0; i < jumlah_transaksi; i++) {
        if (strcmp(transaksi[i].pembeli, pengguna_saat_ini->nama_pengguna) == 0) {
            punya_pembelian = 1;
            break;
        }
    }
    
    if (!punya_pembelian) {
        printf("Anda belum melakukan pembelian.\n");
        return;
    }
    
    lihat_riwayat_pembelian();
    
    char merek[PANJANG_STRING_MAKS];
    int ukuran;
    char warna[PANJANG_STRING_MAKS];
    
    printf("\nMasukkan merek sepatu untuk diulas: ");
    scanf("%49s", merek);
    bersihkan_buffer_masukan();
    
    printf("Masukkan ukuran: ");
    scanf("%d", &ukuran);
    bersihkan_buffer_masukan();
    
    printf("Masukkan warna: ");
    scanf("%49s", warna);
    bersihkan_buffer_masukan();
    
    // Cek apakah pembeli pernah membeli produk ini
    int telah_membeli = 0;
    for (int i = 0; i < jumlah_transaksi; i++) {
        if (strcmp(transaksi[i].pembeli, pengguna_saat_ini->nama_pengguna) == 0 &&
            strcasecmp(transaksi[i].merek_produk, merek) == 0 &&
            transaksi[i].ukuran_produk == ukuran &&
            strcasecmp(transaksi[i].warna_produk, warna) == 0) {
            telah_membeli = 1;
            break;
        }
    }
    
    if (!telah_membeli) {
        printf("Anda belum membeli produk ini.\n");
        return;
    }
    
    // Cek apakah sudah ada ulasan untuk produk ini
    for (int i = 0; i < jumlah_ulasan; i++) {
        if (strcmp(ulasan[i].pembeli, pengguna_saat_ini->nama_pengguna) == 0 &&
            strcasecmp(ulasan[i].merek_produk, merek) == 0) {
            printf("Anda sudah mengulas produk ini.\n");
            return;
        }
    }
    
    if (jumlah_ulasan >= MAKS_ULASAN) {
        printf("Batas maksimum ulasan tercapai.\n");
        return;
    }
    
    Ulasan ulasan_baru;
    strcpy(ulasan_baru.pembeli, pengguna_saat_ini->nama_pengguna);
    strcpy(ulasan_baru.merek_produk, merek);
    ulasan_baru.waktu = time(NULL);
    
    printf("Masukkan peringkat (1-5): ");
    scanf("%d", &ulasan_baru.peringkat);
    bersihkan_buffer_masukan();
    
    if (ulasan_baru.peringkat < 1 || ulasan_baru.peringkat > 5) {
        printf("Peringkat harus antara 1 dan 5.\n");
        return;
    }
    
    printf("Masukkan komentar ulasan Anda: ");
    fgets(ulasan_baru.komentar, PANJANG_STRING_MAKS * 2, stdin);
    ulasan_baru.komentar[strcspn(ulasan_baru.komentar, "\n")] = 0; // Hapus newline
    
    ulasan[jumlah_ulasan++] = ulasan_baru;
    printf("Ulasan berhasil ditambahkan!\n");
    
    simpan_data();
}

// Fungsi penjual
// Jobdesk: Hebby (Kelola Produk)
// Feature: Manajemen produk lengkap
void tambah_produk() {
    if (!pengguna_saat_ini || !pengguna_saat_ini->adalah_penjual) {
        printf("Hanya penjual yang dapat menambah produk.\n");
        return;
    }
    
    if (jumlah_produk >= MAKS_PRODUK) {
        printf("Batas maksimum produk tercapai.\n");
        return;
    }
    
    Produk produk_baru;
    strcpy(produk_baru.penjual, pengguna_saat_ini->nama_pengguna);
    produk_baru.aktif = 1;
    
    printf("Masukkan merek: ");
    scanf("%49s", produk_baru.merek);
    bersihkan_buffer_masukan();
    
    printf("Masukkan ukuran: ");
    scanf("%d", &produk_baru.ukuran);
    bersihkan_buffer_masukan();
    
    printf("Masukkan harga: ");
    scanf("%f", &produk_baru.harga);
    bersihkan_buffer_masukan();
    
    printf("Masukkan warna: ");
    scanf("%49s", produk_baru.warna);
    bersihkan_buffer_masukan();
    
    printf("Masukkan jumlah stok: ");
    scanf("%d", &produk_baru.stok);
    bersihkan_buffer_masukan();
    
    produk[jumlah_produk++] = produk_baru;
    printf("Produk berhasil ditambahkan!\n");
    
    simpan_data();
}

// Jobdesk: Lia (Laporan Penjualan)
// Feature: Laporan penjualan untuk penjual
void lihat_saldo_penjualan() {
    if (!pengguna_saat_ini || !pengguna_saat_ini->adalah_penjual) {
        printf("Hanya penjual yang dapat melihat saldo penjualan.\n");
        return;
    }
    
    cetak_judul("SALDO PENJUALAN");
    printf("Saldo Anda saat ini: %.2f\n", pengguna_saat_ini->saldo);
    
    // Tampilkan riwayat penjualan
    printf("\nRiwayat Penjualan:\n");
    int ditemukan = 0;
    for (int i = 0; i < jumlah_transaksi; i++) {
        for (int j = 0; j < jumlah_produk; j++) {
            if (strcmp(produk[j].penjual, pengguna_saat_ini->nama_pengguna) == 0 &&
                strcmp(transaksi[i].merek_produk, produk[j].merek) == 0 &&
                transaksi[i].ukuran_produk == produk[j].ukuran &&
                strcmp(transaksi[i].warna_produk, produk[j].warna) == 0) {
                ditemukan = 1;
                char waktu_str[20];
                strftime(waktu_str, 20, "%Y-%m-%d %H:%M:%S", localtime(&transaksi[i].waktu));
                
                printf("Tanggal: %s\n", waktu_str);
                printf("Produk: %s (Ukuran: %d, Warna: %s)\n", 
                       transaksi[i].merek_produk, transaksi[i].ukuran_produk, transaksi[i].warna_produk);
                printf("Jumlah: %.2f\n", transaksi[i].jumlah);
                printf("Dijual ke: %s\n\n", transaksi[i].pembeli);
            }
        }
    }
    
    if (!ditemukan) {
        printf("Tidak ada riwayat penjualan ditemukan.\n");
    }
}

// Jobdesk: Hebby (Kelola Produk)
// Feature: Manajemen produk lengkap
void kelola_produk() {
    if (!pengguna_saat_ini || !pengguna_saat_ini->adalah_penjual) {
        printf("Hanya penjual yang dapat mengelola produk.\n");
        return;
    }
    
    cetak_judul("KELOLA PRODUK");
    
    printf("Produk Anda:\n");
    int ditemukan = 0;
    for (int i = 0; i < jumlah_produk; i++) {
        if (produk[i].aktif && strcmp(produk[i].penjual, pengguna_saat_ini->nama_pengguna) == 0) {
            ditemukan = 1;
            printf("%d. %s (Ukuran: %d, Warna: %s) - Harga: %.2f - Stok: %d\n", 
                   i+1, produk[i].merek, produk[i].ukuran, 
                   produk[i].warna, produk[i].harga, produk[i].stok);
        }
    }
    
    if (!ditemukan) {
        printf("Anda tidak memiliki produk yang terdaftar.\n");
        return;
    }
    
    printf("\n1. Perbarui produk\n2. Hapus produk\n3. Kembali\n");
    printf("Pilih opsi: ");
    int opsi;
    scanf("%d", &opsi);
    bersihkan_buffer_masukan();
    
    if (opsi == 1) {
        printf("Masukkan nomor produk untuk diperbarui: ");
        int nomor_produk;
        scanf("%d", &nomor_produk);
        bersihkan_buffer_masukan();
        
        if (nomor_produk < 1 || nomor_produk > jumlah_produk) {
            printf("Nomor produk tidak valid.\n");
            return;
        }
        
        // Cari produk yang dimiliki penjual ini
        int indeks_aktual = -1;
        int hitung = 0;
        for (int i = 0; i < jumlah_produk; i++) {
            if (produk[i].aktif && strcmp(produk[i].penjual, pengguna_saat_ini->nama_pengguna) == 0) {
                hitung++;
                if (hitung == nomor_produk) {
                    indeks_aktual = i;
                    break;
                }
            }
        }
        
        if (indeks_aktual == -1) {
            printf("Pemilihan produk tidak valid.\n");
            return;
        }
        
        printf("Masukkan harga baru (saat ini: %.2f): ", produk[indeks_aktual].harga);
        scanf("%f", &produk[indeks_aktual].harga);
        bersihkan_buffer_masukan();
        
        printf("Masukkan stok baru (saat ini: %d): ", produk[indeks_aktual].stok);
        scanf("%d", &produk[indeks_aktual].stok);
        bersihkan_buffer_masukan();
        
        printf("Produk berhasil diperbarui!\n");
        simpan_data();
    } else if (opsi == 2) {
        printf("Masukkan nomor produk untuk dihapus: ");
        int nomor_produk;
        scanf("%d", &nomor_produk);
        bersihkan_buffer_masukan();
        
        if (nomor_produk < 1 || nomor_produk > jumlah_produk) {
            printf("Nomor produk tidak valid.\n");
            return;
        }
        
        // Cari produk yang dimiliki penjual ini
        int indeks_aktual = -1;
        int hitung = 0;
        for (int i = 0; i < jumlah_produk; i++) {
            if (produk[i].aktif && strcmp(produk[i].penjual, pengguna_saat_ini->nama_pengguna) == 0) {
                hitung++;
                if (hitung == nomor_produk) {
                    indeks_aktual = i;
                    break;
                }
            }
        }
        
        if (indeks_aktual == -1) {
            printf("Pemilihan produk tidak valid.\n");
            return;
        }
        
        produk[indeks_aktual].aktif = 0;
        printf("Produk berhasil dihapus!\n");
        simpan_data();
    }
}

// Jobdesk: Hebby (Kelola Produk - extended functionality)
// Feature: Manajemen produk lengkap
void lihat_akun_pembeli() {
    if (!pengguna_saat_ini || !pengguna_saat_ini->adalah_penjual) {
        printf("Hanya penjual yang dapat melihat akun pembeli.\n");
        return;
    }
    
    cetak_judul("AKUN PEMBELI");
    
    int ditemukan = 0;
    for (int i = 0; i < jumlah_pengguna; i++) {
        if (!pengguna[i].adalah_penjual && pengguna[i].aktif) {
            ditemukan = 1;
            printf("Nama Pengguna: %s\n", pengguna[i].nama_pengguna);
            printf("Saldo: %.2f\n\n", pengguna[i].saldo);
        }
    }
    
    if (!ditemukan) {
        printf("Tidak ada akun pembeli ditemukan.\n");
    }
}

// Jobdesk: Hebby (Kelola Produk - extended functionality)
// Feature: Manajemen produk lengkap
void hapus_akun_pembeli() {
    if (!pengguna_saat_ini || !pengguna_saat_ini->adalah_penjual) {
        printf("Hanya penjual yang dapat menghapus akun pembeli.\n");
        return;
    }
    
    lihat_akun_pembeli();
    
    char nama_pengguna[PANJANG_STRING_MAKS];
    printf("\nMasukkan nama pengguna untuk dihapus (atau 'batal' untuk membatalkan): ");
    scanf("%49s", nama_pengguna);
    bersihkan_buffer_masukan();
    
    if (strcasecmp(nama_pengguna, "batal") == 0) {
        return;
    }
    
    for (int i = 0; i < jumlah_pengguna; i++) {
        if (!pengguna[i].adalah_penjual && strcmp(pengguna[i].nama_pengguna, nama_pengguna) == 0 && pengguna[i].aktif) {
            pengguna[i].aktif = 0;
            printf("Akun pembeli berhasil dihapus.\n");
            simpan_data();
            return;
        }
    }
    
    printf("Akun pembeli tidak ditemukan atau tidak valid.\n");
}

// Jobdesk: Ica (Ulasan - extended functionality for seller)
// Feature: Ulasan dan rating produk
void lihat_ulasan_produk() {
    if (!pengguna_saat_ini || !pengguna_saat_ini->adalah_penjual) {
        printf("Hanya penjual yang dapat melihat ulasan produk.\n");
        return;
    }
    
    cetak_judul("ULASAN PRODUK");
    
    // Tampilkan produk yang dijual oleh penjual ini
    printf("Produk Anda:\n");
    int produk_ditemukan = 0;
    for (int i = 0; i < jumlah_produk; i++) {
        if (produk[i].aktif && strcmp(produk[i].penjual, pengguna_saat_ini->nama_pengguna) == 0) {
            produk_ditemukan = 1;
            printf("- %s (Ukuran: %d, Warna: %s)\n", 
                   produk[i].merek, produk[i].ukuran, produk[i].warna);
        }
    }
    
    if (!produk_ditemukan) {
        printf("Anda tidak memiliki produk yang terdaftar.\n");
        return;
    }
    
    char merek[PANJANG_STRING_MAKS];
    printf("\nMasukkan merek produk untuk melihat ulasan: ");
    scanf("%49s", merek);
    bersihkan_buffer_masukan();
    
    // Cek apakah produk milik penjual ini
    int adalah_produk_sendiri = 0;
    for (int i = 0; i < jumlah_produk; i++) {
        if (produk[i].aktif && 
            strcmp(produk[i].penjual, pengguna_saat_ini->nama_pengguna) == 0 &&
            strcasecmp(produk[i].merek, merek) == 0) {
            adalah_produk_sendiri = 1;
            break;
        }
    }
    
    if (!adalah_produk_sendiri) {
        printf("Anda tidak memiliki produk ini atau produk tidak ada.\n");
        return;
    }
    
    // Tampilkan ulasan untuk produk ini
    int ulasan_ditemukan = 0;
    for (int i = 0; i < jumlah_ulasan; i++) {
        if (strcasecmp(ulasan[i].merek_produk, merek) == 0) {
            ulasan_ditemukan = 1;
            char waktu_str[20];
            strftime(waktu_str, 20, "%Y-%m-%d %H:%M:%S", localtime(&ulasan[i].waktu));
            
            printf("\nUlasan oleh: %s\n", ulasan[i].pembeli);
            printf("Tanggal: %s\n", waktu_str);
            printf("Peringkat: %d/5\n", ulasan[i].peringkat);
            printf("Komentar: %s\n", ulasan[i].komentar);
        }
    }
    
    if (!ulasan_ditemukan) {
        printf("Tidak ada ulasan ditemukan untuk produk ini.\n");
    }
}

// Menu utama
// Jobdesk: All team members (integrating all features)
// Feature: Multi-role user (Pembeli/Penjual)
void menu_pembeli() {
    int pilihan;
    do {
        cetak_judul("MENU PEMBELI");
        printf("1. Lihat Katalog Sepatu\n");
        printf("2. Isi Saldo\n");
        printf("3. Beli Sepatu\n");
        printf("4. Lihat Riwayat Pembelian\n");
        printf("5. Tambah Ulasan Produk\n");
        printf("6. Ganti Kata Sandi\n");
        printf("7. Keluar\n");
        printf("Pilih opsi: ");
        
        scanf("%d", &pilihan);
        bersihkan_buffer_masukan();
        
        switch (pilihan) {
            case 1: lihat_katalog(); break;
            case 2: isi_saldo(); break;
            case 3: beli_sepatu(); break;
            case 4: lihat_riwayat_pembelian(); break;
            case 5: tambah_ulasan(); break;
            case 6: ganti_kata_sandi(); break;
            case 7: keluar(); break;
            default: printf("Opsi tidak valid.\n");
        }
        
        if (pilihan != 7) {
            tekan_enter_untuk_lanjut();
        }
    } while (pilihan != 7);
}

// Jobdesk: All team members (integrating all features)
// Feature: Multi-role user (Pembeli/Penjual)
void menu_penjual() {
    int pilihan;
    do {
        cetak_judul("MENU PENJUAL");
        printf("1. Tambah Produk\n");
        printf("2. Lihat Saldo Penjualan\n");
        printf("3. Kelola Produk\n");
        printf("4. Lihat Akun Pembeli\n");
        printf("5. Hapus Akun Pembeli\n");
        printf("6. Lihat Ulasan Produk\n");
        printf("7. Ganti Kata Sandi\n");
        printf("8. Keluar\n");
        printf("Pilih opsi: ");
        
        scanf("%d", &pilihan);
        bersihkan_buffer_masukan();
        
        switch (pilihan) {
            case 1: tambah_produk(); break;
            case 2: lihat_saldo_penjualan(); break;
            case 3: kelola_produk(); break;
            case 4: lihat_akun_pembeli(); break;
            case 5: hapus_akun_pembeli(); break;
            case 6: lihat_ulasan_produk(); break;
            case 7: ganti_kata_sandi(); break;
            case 8: keluar(); break;
            default: printf("Opsi tidak valid.\n");
        }
        
        if (pilihan != 8) {
            tekan_enter_untuk_lanjut();
        }
    } while (pilihan != 8);
}

// Jobdesk: All team members (integrating all features)
// Feature: Multi-role user (Pembeli/Penjual)
void menu_utama() {
    int pilihan;
    do {
        cetak_judul("MENU UTAMA");
        printf("1. Daftar sebagai Pembeli\n");
        printf("2. Daftar sebagai Penjual\n");
        printf("3. Masuk\n");
        printf("4. Keluar\n");
        printf("Pilih opsi: ");
        
        scanf("%d", &pilihan);
        bersihkan_buffer_masukan();
        
        switch (pilihan) {
            case 1: 
                daftar_pengguna(0); 
                tekan_enter_untuk_lanjut();
                break;
            case 2: 
                daftar_pengguna(1); 
                tekan_enter_untuk_lanjut();
                break;
            case 3: 
                if (masuk_pengguna()) {
                    if (pengguna_saat_ini->adalah_penjual) {
                        menu_penjual();
                    } else {
                        menu_pembeli();
                    }
                } else {
                    tekan_enter_untuk_lanjut();
                }
                break;
            case 4: 
                printf("Keluar...\n"); 
                break;
            default: 
                printf("Opsi tidak valid.\n");
                tekan_enter_untuk_lanjut();
        }
    } while (pilihan != 4);
}

// Jobdesk: All team members (program entry point)
// Feature: Penyimpanan data berbasis file, Multi-role user
int main() {
    muat_data();
    menu_utama();
    simpan_data();
    return 0;
}