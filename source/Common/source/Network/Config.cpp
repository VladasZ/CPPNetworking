
#include "Config.h"

using namespace std;
using namespace Rest;

string Config::base_url;
Headers Config::default_headers;

bool Config::has_base_url()
{
	return base_url.length() > 0;
}

void Config::set_authorization_token(const string& token)
{
	default_headers["Authorization"] = "Bearer " + token;
}

bool Config::is_authorized()
{
    return default_headers.find("Authorization") != default_headers.end();
}