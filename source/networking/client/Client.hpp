//
//  Client.hpp
//  networking
//
//  Created by Vladas Zakrevskis on 8/6/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <functional>
#include <unordered_map>

#include "Path.hpp"
#include "Response.hpp"
#include "NetworkingTypes.hpp"

namespace net {
    
    class Client {
        
        cu::Path _base_url;
        
    public:

        bool async = false;
        
        Headers headers;
        
        Client(const cu::Path& base_url, bool async = false);

        void request(const URL&, CoreCompletion) const;
        void request(const URL&, Method, CoreCompletion) const;

    private:

        void _dispatch(const URL&, Method, CoreCompletion) const;
        void _request(const URL&, Method, CoreCompletion) const;

    };
}
