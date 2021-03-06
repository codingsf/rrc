/**
 *  @autor arssivka
 *  @date 8/25/16
 */

#pragma once


#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <typeinfo>
#include <algorithm>
#include <typeindex>
#include <google/protobuf/message_lite.h>
#include "MessageFactory.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    typedef unsigned int TypeId;

    class MetaTable {
    public:
        static const TypeId UNKNOWN_TYPE_ID;

        MetaTable() = default;

        template <class T>
        TypeId getTypeId() const {
            using Type = typename std::remove_reference<T>::type;
            static_assert(std::is_base_of<pb::MessageLite, Type>::value,
                          "Type must be derived from google::protobuf::MessageLite");
            std::type_index typeIndex = typeid(Type);
            auto found = mTypeInfoHash.find(typeIndex);
            return (found != mTypeInfoHash.end()) ? found->second : UNKNOWN_TYPE_ID;
        }

        template <class T>
        bool registerTypeId(TypeId tid) {
            using Type = typename std::remove_reference<T>::type;
            static_assert(std::is_base_of<pb::MessageLite, Type>::value,
                          "Type must be derived from google::protobuf::MessageLite");
            if (this->isIdReserved(tid)) return false;
            std::type_index typeIndex = typeid(T);
            mMessageFactoryHash.insert({tid, std::make_unique<MessageFactory<T>>()});
            mTypeInfoHash.insert({typeIndex, tid});
            return true;
        }

        MessageFactoryPtr getMessageFactory(TypeId typeId);

        bool freeTypeId(TypeId typeId);

        bool isIdReserved(TypeId tid);

    private:
        std::unordered_map<std::type_index, TypeId> mTypeInfoHash;
        std::unordered_map<TypeId, MessageFactoryPtr> mMessageFactoryHash;

    };
}


