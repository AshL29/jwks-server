#ifndef KEYMANAGER_HPP
#define KEYMANAGER_HPP

#include <string>
#include <map>
#include <chrono>
#include <nlohmann/json.hpp>

class KeyManager {
public:
    struct Key {
        std::string kid;
        std::string private_key;
        std::string public_key;
        std::chrono::system_clock::time_point expiry;
    };

    KeyManager();
    ~KeyManager();

    Key generateKey();
    nlohmann::json getKeyAsJson(const Key &key);
    void addKey(const Key &key);
    Key getKey(const std::string &kid);

private:
    std::map<std::string, Key> keys;
};

#endif // KEYMANAGER_HPP
