/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "aes256.h"
#include <cstring>

#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>

namespace aes256 {

constexpr int AES_BLOCK_SIZE = 16;
constexpr int AES_KEY_SIZE = 32;

DecryptionResult decrypt(const QByteArray &encrypted, const std::string &passwd) {
    unsigned char key[AES_KEY_SIZE], iv[AES_BLOCK_SIZE], dummy[AES_BLOCK_SIZE];

    std::memcpy(iv, encrypted.data(), AES_BLOCK_SIZE);
    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), NULL, (const unsigned char *)passwd.c_str(), passwd.length(), 1,
                   key, dummy);

    auto ctx = EVP_CIPHER_CTX_new();
    if (ctx == nullptr) {
        throw DecryptionException();
    }

    EVP_DecryptInit(ctx, EVP_aes_256_cbc(), key, iv);

    int firstLength = 0;
    int finalLength = 0;

    BufferPtr decryptedMessage(new unsigned char[encrypted.length()]);

    if (!EVP_DecryptUpdate(ctx, decryptedMessage.get(), &firstLength,
                           (const unsigned char *)(encrypted.data() + AES_BLOCK_SIZE), encrypted.length() - AES_BLOCK_SIZE)) {
        EVP_CIPHER_CTX_cleanup(ctx);
        printf("EVP Error: couldn't update decrypt with text!\n");
        throw DecryptionException();
    }

    if (!EVP_DecryptFinal(ctx, decryptedMessage.get() + firstLength, &finalLength)) {
        EVP_CIPHER_CTX_cleanup(ctx);
        printf("EVP Error: couldn't finalize decryption!\n");
        throw DecryptionException();
    }

    EVP_CIPHER_CTX_cleanup(ctx);
    return DecryptionResult(decryptedMessage, firstLength + finalLength);
}

} // namespace aes256
