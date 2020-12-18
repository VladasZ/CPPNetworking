//
// Created by Vladas Zakrevskis on 2/09/2019.
//

#include "Error.hpp"


Error::Error(const std::string& error) : error(error) {

}

Error::operator std::string() const {
    return error;
}
