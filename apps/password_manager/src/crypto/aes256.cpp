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

using ConstCharPtr = const unsigned char *;
using CharPtr = unsigned char *;

void decrypt(const QByteArray &encrypted, const QString &passwd, QByteArray &decrypted) {
    unsigned char key[AES_KEY_SIZE], iv[AES_BLOCK_SIZE], dummy[AES_BLOCK_SIZE];

    std::memcpy(iv, encrypted.data(), AES_BLOCK_SIZE);
    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), NULL, reinterpret_cast<ConstCharPtr>(passwd.toStdString().c_str()),
                   passwd.length(), 1, key, dummy);

    auto ctx = EVP_CIPHER_CTX_new();
    if (ctx == nullptr) {
        throw DecryptionException("EVP Error: failed to create cipher context");
    }

    EVP_DecryptInit(ctx, EVP_aes_256_cbc(), key, iv);

    int firstLength = 0;
    int finalLength = 0;

    decrypted.resize(encrypted.length());

    if (!EVP_DecryptUpdate(ctx, reinterpret_cast<CharPtr>(decrypted.data()), &firstLength,
                           reinterpret_cast<ConstCharPtr>(encrypted.data() + AES_BLOCK_SIZE),
                           encrypted.length() - AES_BLOCK_SIZE)) {
        EVP_CIPHER_CTX_cleanup(ctx);
        throw DecryptionException("EVP Error: couldn't update decrypt with text");
    }

    if (!EVP_DecryptFinal(ctx, reinterpret_cast<CharPtr>(decrypted.data() + firstLength), &finalLength)) {
        EVP_CIPHER_CTX_cleanup(ctx);
        throw DecryptionException("EVP Error: couldn't finalize decryption");
    }

    EVP_CIPHER_CTX_cleanup(ctx);
    decrypted.resize(firstLength + finalLength);
}

} // namespace aes256
