#include <stdio.h>
#include <string.h>

int main() {
    const int MAX = 100;
    const int MAX_DAYS = 14;
    const int FINE_PER_DAY = 5000;

    char ticketCode[100][20];
    char bookCode[100][20];
    int borrowDays[100];

    int ticketCount = 0;
    int choice;

    do {
        printf("\n================ HE THONG QUAN LY MUON TRA SACH (LOGISTICS) ================\n");
        printf("1. Them moi phieu muon sach (Create)\n");
        printf("2. Hien thi danh sach phieu muon & Tien phat qua han (Read)\n");
        printf("3. Cap nhat so ngay muon sach (Update)\n");
        printf("4. Xac nhan tra sach / Xoa phieu muon (Delete)\n");
        printf("5. Thoat chuong trinh\n");
        printf("===========================================================================\n");
        printf("Lua chon cua ban (1-5): ");
        scanf("%d", &choice);

        while (getchar() != '\n');

        switch (choice) {

            case 1: {
                if (ticketCount >= MAX) {
                    printf("Bo nho danh sach da day, khong the them moi!\n");
                    break;
                }

                char newTicketCode[20];
                int duplicate = 0;

                printf("\n--- THEM MOI PHIEU MUON ---\n");
                printf("Nhap ma phieu: ");
                scanf("%19s", newTicketCode);

                while (getchar() != '\n');

                for (int i = 0; i < ticketCount; i++) {
                    if (strcmp(ticketCode[i], newTicketCode) == 0) {
                        duplicate = 1;
                        break;
                    }
                }

                if (duplicate) {
                    printf("Ma phieu da ton tai trong he thong!\n");
                    break;
                }

                strcpy(ticketCode[ticketCount], newTicketCode);

                printf("Nhap ma sach: ");
                scanf("%19s", bookCode[ticketCount]);

                while (getchar() != '\n');

                do {
                    printf("Nhap so ngay muon: ");
                    scanf("%d", &borrowDays[ticketCount]);

                    while (getchar() != '\n');

                    if (borrowDays[ticketCount] <= 0) {
                        printf("So ngay muon phai lon hon 0! Vui long nhap lai.\n");
                    }

                } while (borrowDays[ticketCount] <= 0);

                ticketCount++;

                printf("Them moi phieu muon thanh cong!\n");

                break;
            }

            case 2: {
                if (ticketCount == 0) {
                    printf("Danh sach phieu muon hien dang rong!\n");
                    break;
                }

                printf("\n=============================== DANH SACH PHIEU MUON ===============================\n");
                printf("%-4s | %-10s | %-12s | %-14s | %-15s | %-15s\n",
                       "STT",
                       "Ma Phieu",
                       "Ma Sach",
                       "So Ngay Muon",
                       "Trang Thai",
                       "Tien Phat (VND)");

                printf("------------------------------------------------------------------------------------\n");

                for (int i = 0; i < ticketCount; i++) {
                    int overdueDays = 0;
                    int fine = 0;

                    if (borrowDays[i] > MAX_DAYS) {
                        overdueDays = borrowDays[i] - MAX_DAYS;
                        fine = overdueDays * FINE_PER_DAY;

                        printf("%-4d | %-10s | %-12s | %-14d | %-15s | %-15d\n",
                               i + 1,
                               ticketCode[i],
                               bookCode[i],
                               borrowDays[i],
                               "QUA HAN",
                               fine);
                    } else {
                        printf("%-4d | %-10s | %-12s | %-14d | %-15s | %-15d\n",
                               i + 1,
                               ticketCode[i],
                               bookCode[i],
                               borrowDays[i],
                               "DUNG HAN",
                               0);
                    }
                }

                printf("------------------------------------------------------------------------------------\n");

                break;
            }

            case 3: {
                char searchCode[20];
                int pos = -1;
                int newBorrowDays;

                printf("\n--- CAP NHAT SO NGAY MUON ---\n");
                printf("Nhap ma phieu can cap nhat: ");
                scanf("%19s", searchCode);

                while (getchar() != '\n');

                for (int i = 0; i < ticketCount; i++) {
                    if (strcmp(ticketCode[i], searchCode) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("Khong tim thay ma phieu trong he thong!\n");
                } else {
                    printf("So ngay muon hien tai cua phieu %s la: %d\n",
                           ticketCode[pos],
                           borrowDays[pos]);

                    do {
                        printf("Nhap so ngay muon moi: ");
                        scanf("%d", &newBorrowDays);

                        while (getchar() != '\n');

                        if (newBorrowDays <= 0) {
                            printf("So ngay muon phai lon hon 0! Vui long nhap lai.\n");
                        }

                    } while (newBorrowDays <= 0);

                    borrowDays[pos] = newBorrowDays;

                    printf("Cap nhat so ngay muon thanh cong!\n");
                }

                break;
            }

            case 4: {
                char searchCode[20];
                int pos = -1;

                printf("\n--- XAC NHAN TRA SACH / XOA PHIEU MUON ---\n");
                printf("Nhap ma phieu xac nhan tra/xoa: ");
                scanf("%19s", searchCode);

                while (getchar() != '\n');

                for (int i = 0; i < ticketCount; i++) {
                    if (strcmp(ticketCode[i], searchCode) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("Khong tim thay ma phieu can xoa!\n");
                } else {
                    for (int i = pos; i < ticketCount - 1; i++) {
                        strcpy(ticketCode[i], ticketCode[i + 1]);
                        strcpy(bookCode[i], bookCode[i + 1]);
                        borrowDays[i] = borrowDays[i + 1];
                    }

                    ticketCount--;

                    printf("Xac nhan tra sach va xoa phieu muon thanh cong!\n");
                }

                break;
            }

            case 5:
                printf("\nCam on ban da su dung he thong!\n");
                printf("Tam biet!\n");
                break;

            default:
                printf("Lua chon khong hop le, vui long chon lai!\n");
        }

    } while (choice != 5);

    return 0;
}