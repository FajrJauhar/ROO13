#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char special[] = {'$','^','@','!','&','*','%'};
char *spec[] = {"A1","A2","A3","A4","A5","A6","A7"};

// ROO13 Decryption
void decrypt_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("File open failed for decryption");
        return;
    }

    char input[5000], decrypted[5000];
    size_t i = 0, j = 0;

    while ((input[i++] = fgetc(fp)) != EOF);
    input[--i] = '\0';
    fclose(fp);

    for (i = 0; i < strlen(input); i++) {
        if (islower(input[i])) {
            decrypted[j++] = (input[i] - 'a' + 13) % 26 + 'a';
        }
        else if (isupper(input[i])) {
            decrypted[j++] = (input[i] - 'A' + 13) % 26 + 'A';
        }
        else if (isdigit(input[i])) {
            decrypted[j++] = ((input[i] - '0' + 13) % 10) + '0';
        }
        else {
            // Try to decode special mappings (A1, A2...)
            if (isalpha(input[i]) && isdigit(input[i + 1])) {
                for (int k = 0; k < sizeof(special)/sizeof(special[0]); k++) {
                    if (input[i] == spec[k][0] && input[i + 1] == spec[k][1]) {
                        decrypted[j++] = special[k];
                        i++; // Skip the next digit
                        goto next;
                    }
                }
            }
            decrypted[j++] = input[i];
            next: ;
        }
    }
    decrypted[j] = '\0';

    fp = fopen(filename, "w");
    fputs(decrypted, fp);
    fclose(fp);

    printf("[+] Decryption complete. File ready for editing.\n");
}

// ROO13 Encryption
void encrypt_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("File open failed for encryption");
        return;
    }

    char input[5000], encrypted[10000];
    size_t i = 0, j = 0;

    while ((input[i++] = fgetc(fp)) != EOF);
    input[--i] = '\0';
    fclose(fp);

    for (i = 0; i < strlen(input); i++) {
        if (islower(input[i])) {
            encrypted[j++] = (input[i] - 'a' + 13) % 26 + 'a';
        }
        else if (isupper(input[i])) {
            encrypted[j++] = (input[i] - 'A' + 13) % 26 + 'A';
        }
        else if (isdigit(input[i])) {
            encrypted[j++] = ((input[i] - '0' + 13) % 10) + '0';
        }
        else {
            int found = 0;
            for (int k = 0; k < sizeof(special)/sizeof(special[0]); k++) {
                if (input[i] == special[k]) {
                    encrypted[j++] = spec[k][0];
                    encrypted[j++] = spec[k][1];
                    found = 1;
                    break;
                }
            }
            if (!found) {
                encrypted[j++] = input[i];
            }
        }
    }

    encrypted[j] = '\0';
    fp = fopen(filename, "w");
    fputs(encrypted, fp);
    fclose(fp);

    printf("[+] Re-encryption complete.\n");
}

int main() {
    int choice;
    char filename[100];

    printf("Enter the encrypted .txt filename: ");
    scanf("%s", filename);

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Decrypt and Edit\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            decrypt_file(filename);

            // Open nano editor
            char command[200];
            snprintf(command, sizeof(command), "nano %s", filename);
            system(command);

            encrypt_file(filename);
            break;

        case 2:
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
