/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include "Message.h"
#include "MessageSender.h"
#include "UnregisteredTypeException.h"
#include "SendGuard.h"

namespace rrc {
    template <typename T>
    class Advertiser : private NonCopyable {
    public:
        Advertiser(RootNodePtr rootNode, const std::string& topicName) {
            mTypeId = rootNode->getTypeId<T>();
            if (mTypeId == MetaTable::UNKNOWN_TYPE_ID) {
                throw rrc::UnregisteredTypeException();
            }
            mTopicName = topicName;
            mRootNode = rootNode;
        }

        Advertiser(Advertiser&& other)
                : mRootNode(std::move(other.mRootNode)),
                  mTypeId(other.mTypeId),
                  mTopicName(std::move(other.mTopicName)) { }

        SendGuard<T> createSendGuard() const {
            return SendGuard<T>(mRootNode, mTopicName, mTypeId);
        }

        ~Advertiser() { }

    private:
        RootNodePtr mRootNode;
        TypeId mTypeId;
        std::string mTopicName;
    };
}


