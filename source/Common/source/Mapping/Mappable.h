#pragma once

#include <vector>
#include <memory>
#include <functional>

#include "Poco\Dynamic\Var.h"
#include "Poco\Dynamic\Struct.h"
#include "Poco\Net\HTMLForm.h"

namespace Net {

    static const std::string no_url = "no_url";

	using JSON = Poco::Dynamic::Var;
	using JSONStruct = Poco::Dynamic::Struct<std::string>;

	template <class T> struct Mapper;
    template <class T> class ObjectResponse;
    template <class T> class ArrayResponse;

	template<class T>
	class Mappable {

	public:

        using Ptr = std::shared_ptr<T>;

		using Array = std::vector<T>;
        using ArrayPtr = std::shared_ptr<Array>;

		using Mapper = Mapper<T>;

        using ObjectResponse = ObjectResponse<T>;
        using ArrayResponse = ArrayResponse<T>;

        using ArrayCompletion = std::function<void(const ArrayResponse&)>;
        using ObjectCompletion = std::function<void(const ObjectResponse&)>;

        static void get_all(const ArrayCompletion& completion) {
            Mapper::_request_array(get_all_url, "", [completion](const ArrayResponse& response) {
                completion(response);
            });
        }

        template <class Parameter = int>
        static void get(const Parameter& parameter, const ObjectCompletion& completion) {
            Mapper::_request_object(get_url + std::to_string(parameter), "", [completion](const ObjectResponse& response) {
                completion(response);
            });
        }

        template <>
        static void get<std::string>(const std::string& parameter, const ObjectCompletion& completion) {
            Mapper::_request_object(get_url + parameter, "", [completion](const ObjectResponse& response) {
                completion(response);
            });
        }

		static ArrayPtr map_to_array(const JSON& json) {
            ArrayPtr array = std::make_shared<Array>();
			std::transform(json.begin(), json.end(), std::back_inserter(*array), [](const auto& var) { return T(var); });
			return array;
		}

        virtual std::string toString() { return toJson().toString(); }

    protected:
        Mappable() = default;
        Mappable(const JSON& json) { }
        virtual JSON toJson() const { return JSON(JSONStruct()); }
        virtual void to_form(Poco::Net::HTMLForm& form) const { }
    private:
        static const std::string get_all_url;
        static const std::string get_url;
        static const std::string post_url;
	};
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Net::Mappable<T>& obj)
{
    return os << obj.toString();
}