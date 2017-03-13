/**
 * Copyright 2016 Arseniy Ivin <arssivka@yandex.ru>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @autor arssivka
 *  @date 11/5/16
 */

#pragma once


#include "topic_holder.h"
#include "mechanism.h"

namespace rrc {
    template <class Q, class K, class M>
    class advertising_mechanism : protected mechanism<topic_holder<K, M>, Q, 2> {
    public:
        enum {
            CHANGE_LISTENERS_PRIORITY,
            SEND_MESSAGE_PRIORITY
        };

        typedef K key_type;
        typedef M message_type;
        typedef Q queue_type;
        typedef mechanism<topic_holder<key_type, message_type>, queue_type, 2> mechanism_type;
        typedef typename mechanism_type::base_type base_type;
        typedef typename base_type::callback_type callback_type;


        advertising_mechanism(abstract_launcher& launcher)
                : mechanism_type(launcher) {}

        /**
         * @brief Send a message
         * @param topic_key Name of the topic for the message
         * @param message Pointer to the message, that needs to be sent
         */
        void send_message(key_type topic_key, message_type message) {
            this->enqueue_task(
                    SEND_MESSAGE_PRIORITY,
                    &base_type::send_message,
                    std::move(topic_key),
                    std::move(message)
            );
        }

        /**
         * @brief Registers listener
         * @param topic_key Name of the topic for the listener
         * @param callback_ptr Pointer to the callback that needs to be registered
         */
        void add_listener(key_type topic_key,
                          std::shared_ptr<callback_type> callback_ptr) {
            this->enqueue_task(
                    CHANGE_LISTENERS_PRIORITY,
                    &base_type::add_listener,
                    std::move(topic_key),
                    std::move(callback_ptr)
            );
        }

        // TODO Tests and docs
        void remove_listener(key_type topic_key,
                             std::shared_ptr<callback_type> callback_ptr) {
            this->enqueue_task(
                    CHANGE_LISTENERS_PRIORITY,
                    &base_type::remove_listener,
                    std::move(topic_key),
                    std::move(callback_ptr)
            );
        }

        /**
         * @brief Returns set of avaliable topic names
         * @return Set of topic names
         */
        std::vector<key_type> keys() const {
            return this->call(&base_type::keys);
        }

    };
}

