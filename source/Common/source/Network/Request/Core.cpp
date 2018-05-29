
#include <memory>

#include "Poco/StreamCopier.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include "Poco/SharedPtr.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/Net/KeyConsoleHandler.h"
#include "Poco/Net/ConsoleCertificateHandler.h"
#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/URIStreamOpener.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/StringPartSource.h"
#include "Poco/Net/FilePartSource.h"

#include "Core.h"
#include "Config.h"

using namespace Net;
using namespace Poco;
using namespace Poco::Net;
using namespace std;

using Poco::URIStreamOpener;

using RequestSetup = function<void(HTTPClientSession& session, HTTPRequest& request)>;

static bool is_https(const string& url) {
	return url.substr(0, 5) == "https";
}

static string append_url(const string& url) {
   return Config::has_base_url() ?
          Config::base_url + "/" + url :
          url;
}

Core& Core::get_instance() {
	static Core instance;
	return instance;
}

template<class SessionType>
void _request(
    const string& url, 
    const HTTP::Method& method, 
    const Core::Completion& completion,
    const RequestSetup& setup_request) {

	Response response;
    response.request_url = url;

	try {

		const URI uri(url);

		SessionType session(uri.getHost(), uri.getPort());
		HTTPRequest request(method, uri.toString(), HTTPMessage::HTTP_1_1);

        response.requestHeaders = Config::default_headers;

		for (auto& header : Config::default_headers)
			request.add(header.first, header.second);

        setup_request(session, request);

		response.method = request.getMethod();

		HTTPResponse httpResponse;
		istream& responseStream = session.receiveResponse(httpResponse);

        for (auto& header : httpResponse)
            response.headers[header.first] = header.second;

        response.body = make_shared<string>(string(istreambuf_iterator<char>(responseStream), {}));
		response.response_code = httpResponse.getStatus();
		response.error = httpResponse.getReason();

		if (response.error == "OK")
			response.error = "";
	}
	catch (const Exception& exception) {
		response.error = exception.displayText();
	}

	completion(response);
}

void Core::http_request(const string& url, const HTTP::Method& method, const string& body, Completion completion) const {
    const auto full_url = append_url(url);

    const auto request_setup = [body](HTTPClientSession& session, HTTPRequest& request) {
        if (body.length() > 0) {
            request.setMethod(HTTP::POST);
            request.setContentLength(body.length());
            ostream& os = session.sendRequest(request);
            os << body;
        }
        else
            session.sendRequest(request);
    };

	if (is_https(full_url))
		_request<HTTPSClientSession>(full_url, method, completion, request_setup);
	else
		_request<HTTPClientSession>(full_url, method, completion, request_setup);
}

void Core::upload_request(const std::string& url, Poco::Net::HTMLForm& form, Completion completion) const  {
    const auto full_url = append_url(url);

    const auto request_setup = [&](HTTPClientSession& session, HTTPRequest& request) {
        form.prepareSubmit(request);
        form.write(session.sendRequest(request));
    };

    if (is_https(full_url))
        _request<HTTPSClientSession>(full_url, HTTP::POST, completion, request_setup);
    else
        _request<HTTPClientSession>(full_url, HTTP::POST, completion, request_setup);
}

Core::Core() {
	Poco::Net::initializeSSL();

	SharedPtr<InvalidCertificateHandler> ptrCert = new ConsoleCertificateHandler(false);
	Context::Ptr ptrContext = new Context(Poco::Net::Context::TLSV1_2_CLIENT_USE, "");

	SSLManager::instance().initializeClient(0, ptrCert, ptrContext);
}

Core::~Core() {
	Poco::Net::uninitializeSSL();
}
