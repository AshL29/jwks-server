#include <iostream>
#include <string>
#include <jwt-cpp/jwt.h>

class JWTHandler {
public:
    JWTHandler(const std::string& secret) : secretKey(secret) {}

    std::string sign(const std::string& payload) {
        auto token = jwt::create()
            .set_payload(payload)
            .set_issuer("your_issuer_here")
            .sign(jwt::algorithm::hs256{ secretKey });
        
        return token;
    }

    bool verify(const std::string& token) {
        try {
            auto decoded = jwt::decode(token);
            auto verifier = jwt::verify()
                .allow_algorithm(jwt::algorithm::hs256{ secretKey })
                .with_issuer("your_issuer_here");
            verifier.verify(decoded);
            return true;
        } catch (...) {
            return false;
        }
    }

private:
    std::string secretKey;
};
