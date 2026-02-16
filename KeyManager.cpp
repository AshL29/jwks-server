#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class KeyManager {
public:
    // Generate RSA key pair
    static RSA* generateRSAKey(int bits) {
        RSA *rsa = RSA_generate_key(bits, RSA_F4, nullptr, nullptr);
        return rsa;
    }

    // Convert RSA key to JWKS format
    static json rsaToJWKS(RSA *rsa) {
        json jwks;

        // Get the public key
        BIO *bpPublic = BIO_new(BIO_s_mem());
        PEM_write_bio_RSAPublicKey(bpPublic, rsa);

        // Read the public key into a string
        char *keyBuffer;
        long keyLength = BIO_get_mem_data(bpPublic, &keyBuffer);
        std::string publicKey(keyBuffer, keyLength);

        // Construct JWKS structure
        jwks["kty"] = "RSA";
        jwks["n"] = publicKey; // Normally needs to be base64_url encoded
        jwks["e"] = "AQAB"; // Standard exponent

        BIO_free(bpPublic);
        return jwks;
    }

    // Function to generate and return JWKS
    static json generateJWKS(int bits) {
        RSA *rsa = generateRSAKey(bits);
        json jwks = rsaToJWKS(rsa);
        RSA_free(rsa); // Free RSA key
        return jwks;
    }
};

int main() {
    KeyManager km;
    json jwks = km.generateJWKS(2048);
    std::cout << jwks.dump(4) << std::endl; // Pretty print JWKS
    return 0;
}