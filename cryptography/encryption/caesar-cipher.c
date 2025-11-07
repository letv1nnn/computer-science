#include "encryption.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        perror("Usage: <program> \"string to encrypt@$%&\" \"shift\"");
        return 1;
    }

    char *string = argv[1], shift = atoi(argv[2]);
    
    char *encrypted = encrypt_caesar(string, shift);
    printf("Encrypted: %s\n", encrypted);
   
    printf("Attempts to decrypt %s:\n", encrypted); 
    for (int shift = 0; shift < 26; ++shift) {
        char *decrypted = decrypt_caesar(encrypted, shift);
        printf("Decrypted: %s\n", decrypted);
        free(decrypted);
    }
    
    free(encrypted);
    return 0;
}

char *encrypt_caesar(char *string, const int shift) {
    const int length = strlen(string);
    char *encrypted = (char *)malloc((length + 1) * sizeof(char));;
    if (!encrypted) {
        perror("memory allocation failed");
        return NULL;
    }
    int idx = 0;
    for (int i = 0; i < length; ++i) {
        if (isalpha(string[i])) {
            if (isupper(string[i])) encrypted[idx++] = (string[i] + shift - 65) % 26 + 65;
            else encrypted[idx++] = (string[i] + shift - 97) % 26 + 97;
        } else if (isdigit(string[i])) {
            encrypted[idx++] = (string[i] + shift - 48) % 10 + 48;
        }
    }
    char *tmp = (char *)realloc(encrypted, (idx + 1) * sizeof(char));
    if (!tmp) {
        perror("memory reallocation failed");
        return NULL;
    }
    encrypted = tmp;
    encrypted[idx] = '\0';
    return encrypted; 
}

char *decrypt_caesar(char *string, const int shift) {
    const int length = strlen(string);
    char *decrypted = (char *)malloc((length + 1) * sizeof(char));
    if (!decrypted) {
        perror("memory allocation failed");
        return NULL;
    }
    int i;
    for (i = 0; i < length; ++i) {
        if (isalpha(string[i])) {
            if (isupper(string[i])) decrypted[i] = (string[i] - shift - 65 + 26) % 26 + 65;
            else decrypted[i] = (string[i] - shift - 97 + 26) % 26 + 97;
        } else if (isdigit(string[i])) {
            decrypted[i] = (string[i] - shift - 48 + 10) % 10 + 48;
        }
    }
    decrypted[i] = '\0';
    return decrypted;
}
