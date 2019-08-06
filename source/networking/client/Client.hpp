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
        
        Headers headers;
        
        Client(const cu::Path& base_url);

        void request(const URL&, CoreCompletion);
        void request(const URL&, Method, CoreCompletion);
        
    };
}
