//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "aes256.h"
#include "cryptoexception.h"
#include <cstring>
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>

namespace Crypto::aes256 {

constexpr int AES_BLOCK_SIZE = 16;
constexpr int AES_KEY_SIZE = 32;

using ConstCharPtr = const unsigned char *;
using CharPtr = unsigned char *;

static EVP_CIPHER_CTX *createContext() {
    auto ctx = EVP_CIPHER_CTX_new();
    if (ctx == nullptr) {
        throw CryptoException("EVP Error: failed to create cipher context");
    }
    return ctx;
}

static void cleanupAndThrow(EVP_CIPHER_CTX *ctx) {
    EVP_CIPHER_CTX_cleanup(ctx);
    throw CryptoException(ERR_error_string(ERR_get_error(), nullptr));
}

std::vector<char> decrypt(const std::span<char> &encrypted, const std::string &passwd) {
    unsigned char key[AES_KEY_SIZE], iv[AES_BLOCK_SIZE], dummy[AES_BLOCK_SIZE];

    std::memcpy(iv, encrypted.data(), AES_BLOCK_SIZE);
    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), NULL, reinterpret_cast<ConstCharPtr>(passwd.c_str()),
                   passwd.length(), 1, key, dummy);

    auto ctx = createContext();
    EVP_DecryptInit(ctx, EVP_aes_256_cbc(), key, iv);

    int firstLength = 0;
    int finalLength = 0;

    std::vector<char> decrypted;
    decrypted.resize(encrypted.size());

    if (!EVP_DecryptUpdate(ctx, reinterpret_cast<CharPtr>(decrypted.data()), &firstLength,
                           reinterpret_cast<ConstCharPtr>(std::next(encrypted.data(), AES_BLOCK_SIZE)),
                           encrypted.size() - AES_BLOCK_SIZE)) {
        cleanupAndThrow(ctx);
    }

    if (!EVP_DecryptFinal_ex(ctx, reinterpret_cast<CharPtr>(std::next(decrypted.data(), firstLength)), &finalLength)) {
        cleanupAndThrow(ctx);
    }

    EVP_CIPHER_CTX_cleanup(ctx);
    decrypted.resize(firstLength + finalLength);
    return decrypted;
}

std::vector<char> encrypt(const std::span<char> &decrypted, const std::string &passwd) {
    unsigned char key[AES_KEY_SIZE], iv[AES_BLOCK_SIZE];

    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), NULL, reinterpret_cast<ConstCharPtr>(passwd.c_str()),
                   passwd.length(), 1, key, iv);

    auto ctx = createContext();

    int firstLength = 0;
    int finalLength = 0;

    std::vector<char> encrypted;
    encrypted.resize(decrypted.size() + 2 * AES_BLOCK_SIZE);

    EVP_EncryptInit(ctx, EVP_aes_256_cbc(), key, iv);

    std::memcpy(encrypted.data(), iv, AES_BLOCK_SIZE);

    if (!EVP_EncryptUpdate(ctx, reinterpret_cast<CharPtr>(std::next(encrypted.data(), AES_BLOCK_SIZE)), &firstLength,
                           reinterpret_cast<ConstCharPtr>(decrypted.data()), decrypted.size())) {
        cleanupAndThrow(ctx);
    }

    if (!EVP_EncryptFinal_ex(ctx, reinterpret_cast<CharPtr>(std::next(encrypted.data(), AES_BLOCK_SIZE + firstLength)),
                             &finalLength)) {
        cleanupAndThrow(ctx);
    }

    EVP_CIPHER_CTX_cleanup(ctx);
    encrypted.resize(AES_BLOCK_SIZE + firstLength + finalLength);
    return encrypted;
}

} // namespace Crypto::aes256
