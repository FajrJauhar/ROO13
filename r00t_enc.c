#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char filename[100];
    printf("Enter the name of the .txt file to encrypt: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    char special[] = {'$','^','@','!','&','*','%'};
    char *spec[] = {"A1","A2","A3","A4","A5","A6","A7"};

    char buffer[1000];
    char encrypted[3000];
    int j = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (islower(buffer[i])) {
                encrypted[j++] = (buffer[i] - 'a' + 13) % 26 + 'a';
            }
            else if (isupper(buffer[i])) {
                encrypted[j++] = (buffer[i] - 'A' + 13) % 26 + 'A';
            }
            else if (isdigit(buffer[i])) {
                encrypted[j++] = ((buffer[i] - '0' + 13) % 10) + '0';
            }
            else {
                int found = 0;
                for (int k = 0; k < sizeof(special)/sizeof(special[0]); k++) {
                    if (buffer[i] == special[k]) {
                        encrypted[j++] = spec[k][0];
                        encrypted[j++] = spec[k][1];
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    encrypted[j++] = buffer[i];
                }
            }

            // Prevent overflow
            if (j >= sizeof(encrypted) - 2) break;
        }
    }
    encrypted[j] = '\0';
    fclose(fp);

    // Write back to file
    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error writing to file");
        return 1;
    }

    fputs(encrypted, fp);
    fclose(fp);

    printf("File encrypted successfully.\n");
    return 0;
}
