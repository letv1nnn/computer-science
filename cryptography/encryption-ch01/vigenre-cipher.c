#include "encryption.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: <program> \"string to encrypt\" \"key\"\n");
        return 1;
    }
    char *string = argv[1], *key = argv[2];

    printf("Plaintext: %s\n", string);
    char *encrypted = vigenre_encrypt(string, key);
    printf("Ciphertext: %s\n", encrypted);
    char *decrypted = vigenre_decrypt(encrypted, key);
    printf("Decripted: %s\n", decrypted);

    free(encrypted);
    free(decrypted);
    return 0;
}

char *vigenre_encrypt(char *string, char const *key) {
    const int length = strlen(string), key_length = strlen(key);
    char *encrypted = (char *)malloc((length + 1) * sizeof(char));
    if (!encrypted) {
        perror("memory allocation failed");
        return NULL;
    }
    int mode[key_length];
    for (int i = 0; i < key_length; ++i) {
        if (isalpha(key[i])) {
            if (isupper(key[i])) mode[i] = key[i] - 'A';
            else mode[i] = key[i] - 'a'; 
        }   
    }

    int idx = 0, key_idx = 0;
    for (int i = 0; i < length; ++i) {
        if (key_idx == key_length) key_idx = 0;
        if (isalpha(string[i])) {
            if (isupper(string[i])) encrypted[idx++] = (string[i] + mode[key_idx] - 65) % 26 + 65;
            else encrypted[idx++] = (string[i] + mode[key_idx] - 97) % 26 + 97;
            ++key_idx;
        } else if (isdigit(string[i])) {
            encrypted[idx++] = (string[i] - '0'+ (mode[key_idx] % 10)) % 10 + '0';
            ++key_idx;
        }
    }
    encrypted = (char *)realloc(encrypted, (idx + 1) * sizeof(char));
    if (!encrypted) {
        perror("memory reallocation failed");
        return NULL;
    }
    encrypted[idx] = '\0';
    return encrypted;
}

char *vigenre_decrypt(char *string, char const *key) {
    const int length = strlen(string), key_length = strlen(key);
    char *decrypted = (char *)malloc((length + 1) * sizeof(char));
    if (!decrypted) {
        perror("memory allocation failed");
        return NULL;
    }
    int mode[key_length];
    for (int i = 0; i < key_length; ++i) {
        if (isalpha(key[i])) {
            if (isupper(key[i])) mode[i] = key[i] - 'A';
            else mode[i] = key[i] - 'a'; 
        }   
    }
    int i = 0;
    for (int key_idx = 0; i < length; ++i) {
        if (key_idx == key_length) key_idx = 0;
        if (isalpha(string[i])) {
            if (isupper(string[i])) decrypted[i] = (string[i] - mode[key_idx] - 65 + 26) % 26 + 65;
            else decrypted[i] = (string[i] - mode[key_idx] - 97 + 26) % 26 + 97;
            ++key_idx;
        } else if (isdigit(string[i])) {
            decrypted[i] = (string[i] - '0' - (mode[key_idx] % 10) + 10) % 10 + '0';
            ++key_idx;
        }
    }
    decrypted[i] = '\0';
    return decrypted;
}
