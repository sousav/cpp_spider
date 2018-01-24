//
// NetworkEventBridge.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/IndieStudio/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Thu Jun  8 16:30:54 2017 Sousa Victor
// Last update Thu Jun  8 16:47:47 2017 Sousa Victor
//

#ifndef NETWORKEVENTBRIDGE_HPP_
#define NETWORKEVENTBRIDGE_HPP_

#include <utility>
#include <vector>
#include <string>
#include <mutex>
#include <unordered_map>

namespace indie {

    class NetworkEventBridge {

    public:
        NetworkEventBridge();
        ~NetworkEventBridge();

        void addEvent(std::string const &event, std::string const &json);

        void lockEventBuffer();
        void unlockEventBuffer();

    protected:
        // std::vector<std::pair<std::string, sio::message::ptr>> _cmdBuffer;
        std::mutex _mutex;
        std::unordered_map<std::string, int> _operation;

    private:

    };

}

#endif
