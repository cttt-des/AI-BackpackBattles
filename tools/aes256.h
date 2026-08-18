#ifndef AES256_H
#define AES256_H
#include <stdint.h>

typedef struct { uint8_t RoundKey[240]; } AES_ctx;

void AES_init_ctx(AES_ctx* ctx, const uint8_t* key);
/* decrypt a single 16-byte block in place (AES-256) */
void AES_ECB_decrypt_block(const AES_ctx* ctx, uint8_t* block);

/* AES-128 variants (16-byte key) */
void AES128_init_ctx(AES_ctx* ctx, const uint8_t* key);
void AES128_ECB_decrypt_block(const AES_ctx* ctx, uint8_t* block);

#endif
