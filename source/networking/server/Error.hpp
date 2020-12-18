//
// Created by Vladas Zakrevskis on 2/09/2019.
//

#pragma once

#include <string>


class Error {

public:

	std::string error;

	Error() = default;
	Error(const std::string&);

	operator std::string() const;

};
