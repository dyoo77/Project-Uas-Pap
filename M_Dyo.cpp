#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    INCOME,
    EXPENSE
} TransactionType;

typedef struct {
    char description[100];
    double amount;
    TransactionType type;
} Transaction;

typedef struct {
    Transaction *income;
    Transaction *expenses;
    int incomeCount;
    int expensesCount;
    double balance;
} Finance;

void initializeFinance(Finance *finance) {
    finance->income = (Transaction *)malloc(sizeof(Transaction) * 100);
    finance->expenses = (Transaction *)malloc(sizeof(Transaction) * 100);
    finance->incomeCount = 0;
    finance->expensesCount = 0;
    finance->balance = 0.0;
}

void freeFinance(Finance *finance) {
    free(finance->income);
    free(finance->expenses);
}

void addTransaction(Finance *finance, TransactionType type) {
    Transaction transaction;

    printf("\nMasukkan deskripsi transaksi: ");
    getchar();
    fgets(transaction.description, sizeof(transaction.description), stdin);
    transaction.description[strcspn(transaction.description, "\n")] = 0;

    printf("Masukkan jumlah: ");
    scanf("%lf", &transaction.amount);

    transaction.type = type;

    if (type == INCOME) {
        finance->income[finance->incomeCount++] = transaction;
        finance->balance += transaction.amount;
        printf("\nPendapatan berhasil ditambahkan!\n");
    } else {
        finance->expenses[finance->expensesCount++] = transaction;
        finance->balance -= transaction.amount;
        printf("\nPengeluaran berhasil ditambahkan!\n");
    }
}

void displayFinance(const Finance *finance) {
    printf("\n==== Laporan Keuangan Klub Bola ====");
    printf("\nSaldo Saat Ini: Rp %.2f\n", finance->balance);

    printf("\nPendapatan:\n");
    for (int i = 0; i < finance->incomeCount; i++) {
        printf("%d. %s - Rp %.2f\n", i + 1, finance->income[i].description, finance->income[i].amount);
    }

    printf("\nPengeluaran:\n");
    for (int i = 0; i < finance->expensesCount; i++) {
        printf("%d. %s - Rp %.2f\n", i + 1, finance->expenses[i].description, finance->expenses[i].amount);
    }
    printf("===================================\n");
}

int main() {
    Finance finance;
    initializeFinance(&finance);
    int choice;

    do {
        printf("\n=== Laporan keuangan tim SRIWIJAYA FC ===\n");
        printf("1. Tambahkan Pendapatan Per Bulan\n");
        printf("2. Tambahkan Pengeluaran Per Bulan\n");
        printf("3. Tampilkan Laporan Keuangan\n");
        printf("4. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addTransaction(&finance, INCOME);
                break;
            case 2:
                addTransaction(&finance, EXPENSE);
                break;
            case 3:
                displayFinance(&finance);
                break;
            case 4:
                printf("\nKeluar dari program. Terima kasih!\n");
                break;
            default:
                printf("\nOpsi tidak valid. Silakan coba lagi.\n");
        }
    } while (choice != 4);

    freeFinance(&finance);
    return 0;
}
