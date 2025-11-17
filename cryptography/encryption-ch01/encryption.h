#ifndef ENCRYPTION
#define ENCRYPTION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Caesar encryption works as follows:
// you shift each character by shift characters left,
// spaces are not included. Easy to deciphr. 
char *encrypt_caesar(char *string, const int shift);
char *decrypt_caesar(char *string, const int shift);
// Vigenre encryption works as follows:
// instead of a single number for shift (mode), it's
// using a key that consist of characters that represent
// shift, for instance key = "ABC" - shift by 0, 1, 2.
// spaces are not included.
char *vigenre_encrypt(char *string, char const *key);
char *vigenre_decrypt(char *string, char const *key);
// One-time pad encyption works as follow:
// Key must be the same length as the plaintext. It's
// efficient for short plaintext, since the length for
// message and key are the same. One function to
// encrypt and decrypt. Each encryption, use different
// key, becuase if attacker gets 2 ciphertext, both
// with the same length, he can get the initial key.
// C ^ C = P ^ P => (C ^ C) ^ (P ^ P) = K
// C - ciphertext, P - plaintext, K - key
char *one_time_pad_encrypt_decrypt(char const *plaintext, char const *key);

#endif
