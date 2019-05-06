#pragma once
#include <iostream>
#include <cstddef>
#include <vector>

namespace cloud {
    class File {
    private:
        std::string name_;
        std::string type_;
        std::vector<std::byte> BinaryCode_;
    public:
        File1(std::string
        name_ ,
        std::string type_, std::vector<byte>
        BinaryCode)
        :

        name_ (name), type_(type), BinaryCode_(BinaryCode) {}

        std::string getName() const {
            return name_;
        }

        std::string getType() const {
            return type_;
        }

        std::vector<std::byte> getBody() const {
            return BinaryCode_;
        }
    };
}