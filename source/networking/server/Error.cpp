//
// Created by Vladas Zakrevskis on 2/09/2019.
//

#include "Error.hpp"


Error::Error(const std::string& error) : error(error) {

}

Error::Error(const std::string& error, const std::string message) : error(error), message(message) {

}

Error::operator std::string() const {
    return error;
}

Error Error::failed_to_parse_json(const std::string& message) {
    return Error("Failed to parse json", message);
}

Error Error::invalid_input(const std::string& message) {
    return Error("Invalid input", message);
}

Error Error::database_error(const std::string& message) {
    return Error("Database error", message);
}

Error Error::invalid_credientals(const std::string& message) {
    return Error("Invalid credientals", message);
}
