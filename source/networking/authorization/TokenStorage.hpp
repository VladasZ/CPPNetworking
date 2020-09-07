
#pragma once

#include <string>
#include <unordered_map>

#include "Result.hpp"

using Token       = std::string;
using TokenResult = cu::Result<Token>;

template<class T>
class TokenStorage {

private:

    static inline std::unordered_map<size_t, std::string> _tokens;

public:

    static TokenResult generate_and_store(const T& object) {
        return _tokens[object.id] = object.generate_token();
    }

    static cu::Result<size_t> get(const Token& token) {
		for (auto [id, stored_token] : _tokens) {
			if (stored_token == token) {
                return id;
            }
		}
        return cu::Result<mapping::ID>();
    }

    static bool is_valid(const T&object, const Token& token) {
        const auto id = object.id;
        if (_tokens.find(id) == _tokens.end()) {
            return false;
        }
        return _tokens[id] == token;
    }

    static void remove(const T& object) {

    }

};
