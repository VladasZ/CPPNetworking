
#include "Dog.h"

Dog::Dog(const JSON& json) {
    json["id"].convert(id);
    json["name"].convert(name);
}

JSON Dog::toJson() const {

    JSON json = JSON(JSONStruct());

    json["id"] = id;
    json["name"] = name;

    return json;
}
