/**
 *  @autor tekatod
 *  @date 3/27/17
 */
#pragma once


#include <map>
#include "core.h"

namespace rrc {
    class topic_callbacks_protector {
    public:
        topic_callbacks_protector(rrc::core& core);

        void insert(std::pair<std::string, topic_callback>&& named_callback);

        void insert_and_register(std::pair<std::string, topic_callback>&& named_callback,
                                 result_callback result = result_callback());

        void remove_and_unregister(std::string &name, result_callback result = result_callback());

        void remove_and_unregister_all(result_callback result = result_callback());

        void remove_listeners(std::string& name);

        void remove_listener(const topic_callback& listener);

    private:
        rrc::core& m_core;
        std::multimap<std::string, topic_callback> m_callbacks;
    };
}