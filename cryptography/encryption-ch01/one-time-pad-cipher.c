#include "encryption.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: <program> \"MESSAGE\" \"KEY\"");
        return 1;
    }

    printf("Initial message: %s\n", argv[1]);

    char *encrypted = one_time_pad_encrypt_decrypt(argv[1], argv[2]);
    if (!encrypted) return 1;
    printf("Encrypted message: ");
    for (int i = 0; i < strlen(argv[1]); ++i)
        printf("%02X", (unsigned char)encrypted[i]);
    printf("\n");

    char *decrypted = one_time_pad_encrypt_decrypt(encrypted, argv[2]);
    if (!decrypted) {
        free(encrypted);
        return 1;
    }
    printf("Decrypted message: %s\n", decrypted);
    
    free(encrypted);
    free(decrypted);
    return 0;
}

char *one_time_pad_encrypt_decrypt(char const *plaintext, char const *key) {
    int msg_length = strlen(plaintext), key_length = strlen(key);
    if (msg_length != key_length) {
        printf("The KEY must be the same length as the MESSAGE\n");
        return NULL;
    }
    char *encrypted = (char *)malloc((msg_length + 1) * sizeof(char));
    if (!encrypted) {
        perror("memory allocation failed");
        return NULL;
    }
    int i;
    for (i = 0; i < msg_length; ++i)
        encrypted[i] = plaintext[i] ^ key[i];
    encrypted[i] = '\0';
    return encrypted;
}

