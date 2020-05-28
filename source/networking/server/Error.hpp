//
// Created by Vladas Zakrevskis on 2/09/2019.
//

#pragma once

#include <string>

class Error {

public:

	std::string error;
	std::string message;

	Error() = default;
	Error(const std::string&);
	Error(const std::string& error, const std::string message);

	operator std::string() const;

	static Error failed_to_parse_json(const std::string& message);
	static Error invalid_input(const std::string& message);
	static Error database_error(const std::string& message);
	static Error invalid_credientals(const std::string& message);
};
