#pragma once

#include <map>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>

#include "Log.hpp"
#include "JsonMapper.hpp"
#include "ExceptionCatch.hpp"

using Headers = std::map<std::string, std::string>;


template<class T, auto& _json_mapper>
class BaseRequest : public Poco::Net::HTTPRequestHandler {

protected:

    using JSONMapper = cu::remove_all_t<decltype(_json_mapper)>;
    static_assert(mapping::is_json_mapper_v<JSONMapper>);

    static constexpr auto json_mapper = _json_mapper;

public:

    using ResponseObject = T;

    Poco::Net::HTTPServerResponse* _response;

protected:

	std::string token;

    std::string body;
    mapping::JSON json;
	Headers request_headers;
    ResponseObject request_object;

public:

    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override {

        if (_parse_request(request, response)) {
            return;
        }

        if constexpr (JSONMapper::template exists<T>()) {
			try {
				request_object = json_mapper.template parse_json<T>(json);
			}
			catch (...) {
				response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_ACCEPTABLE);
                Log << cu::what();
				respond_error("Failed to parse JSON: " + cu::what());
				return;
			}
        }

		try {
			handle();
		}
		catch (...) {
            Log << cu::what();
			respond_error("Request handler error: " + cu::what());
		}
    }

    virtual void handle() = 0;

protected:

    void respond_error(const std::string& error) {
        _response->send() << mapping::JSON {{ "error" , error }};
    }

    virtual std::string name() const = 0;

	virtual std::vector<std::string> required_header_keys() const {
		return { };
	}

    virtual std::vector<std::string> required_json_keys() const {
        return { };
    }

    virtual bool needs_json_body() const {
        return !required_json_keys().empty();
    }

    virtual bool needs_file() const {
        return false;
    }

    std::ostream& send() {
        return _response->send();
    }

    void set_status(Poco::Net::HTTPServerResponse::HTTPStatus status) {
        _response->setStatusAndReason(status);
    }

private:

    bool _parse_request(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)  {

        _response = &response;

        std::istream& stream = request.stream();

        if (needs_file()) {

        }

        body = { std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>() };

        for (auto [key, value] : request) {
            request_headers[key] = value;
            if (key == "Authorization") {
                token = value;
            }
        }

        for (auto key : required_header_keys()) {
            if (request_headers.find(key) == request_headers.end()) {
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_ACCEPTABLE);
                respond_error("Request validation error: " + name() + " must contain " + key + " header field");
                return true;
            }
        }

        if (!needs_json_body()) {
            return false;
        }

        try {

            json = mapping::JSON::parse(body);
            Log << json.dump();

            for (auto key : required_json_keys()) {
                if (!json.contains(key)) {
                    response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_ACCEPTABLE);
                    respond_error("Model validation error: " +  name() + " must contain " + key + " JSON field");
                    return true;
                }
            }

        }
        catch(...) {
			response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_ACCEPTABLE);
            respond_error("Failed to parse JSON: " + cu::what());
            return true;
        }

        return false;
    }

};
