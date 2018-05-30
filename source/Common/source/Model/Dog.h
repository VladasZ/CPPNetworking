#pragma once

#include <string>

#include "Mappable.h"

using namespace Net;

class Dog : public Mappable<Dog> {
public:

    int id = 0;
    std::string name = "Bobik";

    Dog() = default;
    Dog(const JSON& json);
    JSON toJson() const override;
};
