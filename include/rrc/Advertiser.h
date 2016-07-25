/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include "ID.h"
#include "Message.h"

namespace rrc {
    template <typename MessageType>
    class Advertiser {
    public:
        Advertiser(const ID& id, const std::string& topic);

        bool isConnected() const;

        void send(Message<MessageType> msg, bool updateTimestamp = true);
    private:
    };
}


