/*!
@file
Defines `boost::hana::Product`.

Copyright Louis Dionne 2013-2022
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_PRODUCT_HPP
#define BOOST_HANA_CONCEPT_PRODUCT_HPP

#include <boost/hana/fwd/concept/product.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/second.hpp>


namespace boost { namespace hana {
    template <typename P>
    struct Product
        : hana::integral_constant<bool,
            !is_default<first_impl<typename tag_of<P>::type>>::value &&
            !is_default<second_impl<typename tag_of<P>::type>>::value
        >
    { };
}} // end namespace boost::hana

#endif // !BOOST_HANA_CONCEPT_PRODUCT_HPP
