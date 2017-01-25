/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


namespace rrc {
    namespace detail {
        template<class L>
        class MetaFrontImplementation;

        template<template<class...> class L, class T, class... U>
        class MetaFrontImplementation<L<T, U...>> {
        public:
            using Type = T;
        };
    }
    /**
     * @brief Gets the front element from the list.
     * Example of using: Front<List<float, int>>
     * @tparam L List to get element from
     */
    template<class L> using MetaFront = typename detail::MetaFrontImplementation<L>::Type;
}