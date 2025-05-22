#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define FILE_NAME "users.txt"

typedef struct {
    char username[50];
    char password[50];
    char role[10]; 
} User;

void clearInputBuffer() {
    while (getchar() != '\n');
}

void saveUser(User user) {
    FILE *fp = fopen(FILE_NAME, "a");
    if (fp == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }
    fprintf(fp, "%s %s %s\n", user.username, user.password, user.role);
    fclose(fp);
}

int login(char *username, char *password, char *role) {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("File pengguna tidak ditemukan.\n");
        return 0;
    }

    User user;
    while (fscanf(fp, "%s %s %s", user.username, user.password, user.role) != EOF) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            strcpy(role, user.role);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void registerUser() {
    User user;
    int roleChoice;

    printf("=== Registrasi Akun ===\n");
    printf("Masukkan username: ");
    scanf("%s", user.username);
    printf("Masukkan password: ");
    scanf("%s", user.password);
    printf("Daftar sebagai:\n1. Pembeli\n2. Penjual\nPilihan: ");
    scanf("%d", &roleChoice);

    if (roleChoice == 1) strcpy(user.role, "pembeli");
    else strcpy(user.role, "penjual");

    saveUser(user);
    printf("Registrasi berhasil sebagai %s!\n", user.role);
}

void loginUser() {
    char username[50], password[50], role[10];
    printf("=== Login Akun ===\n");
    printf("Masukkan username: ");
    scanf("%s", username);
    printf("Masukkan password: ");
    scanf("%s", password);

    if (login(username, password, role)) {
        printf("Login berhasil! Selamat datang, %s (%s)\n", username, role);
    } else {
        printf("Kredensial salah. Silakan coba lagi.\n");
    }
    exit(0);
}

int main() {
    int pilihan;
    do {
        printf("\n=== Selamat Datang di DShoes ===\n");
        printf("1. Login\n2. Registrasi\n3. Keluar\nPilihan: ");
        scanf("%d", &pilihan);
        clearInputBuffer();

        switch (pilihan) {
            case 1:
                loginUser();
                break;
            case 2:
                registerUser();
                break;
            case 3:
                printf("Terima kasih telah menggunakan DShoes!\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
        } while (pilihan != 3);
       return 0;
    }