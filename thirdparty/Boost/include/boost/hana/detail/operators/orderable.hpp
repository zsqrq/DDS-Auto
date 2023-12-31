/*!
@file
Defines operators for Orderables.

Copyright Louis Dionne 2013-2022
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_ORDERABLE_HPP
#define BOOST_HANA_DETAIL_OPERATORS_ORDERABLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/greater.hpp>
#include <boost/hana/fwd/greater_equal.hpp>
#include <boost/hana/fwd/less.hpp>
#include <boost/hana/fwd/less_equal.hpp>

#include <type_traits>


namespace boost { namespace hana { namespace detail {
    template <typename Tag>
    struct orderable_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator<(X&& x, Y&& y)
        { return hana::less(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator>(X&& x, Y&& y)
        { return hana::greater(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator<=(X&& x, Y&& y)
        { return hana::less_equal(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator>=(X&& x, Y&& y)
        { return hana::greater_equal(static_cast<X&&>(x), static_cast<Y&&>(y)); }
    } // end namespace operators
} }} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_OPERATORS_ORDERABLE_HPP
