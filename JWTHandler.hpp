#ifndef JWTHandler_hpp
#define JWTHandler_hpp

#include <string>
#include <jwt-cpp/jwt.h>

class JWTHandler {
public:
    JWTHandler(const std::string& secret);
    std::string createToken(const std::string& payload);
    bool verifyToken(const std::string& token);

private:
    std::string secret;
};

#endif // JWTHandler_hpp
