/*!
@file
Defines `boost::hana::suffix`.

Copyright Louis Dionne 2013-2022
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SUFFIX_HPP
#define BOOST_HANA_SUFFIX_HPP

#include <boost/hana/fwd/suffix.hpp>

#include <boost/hana/chain.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/lift.hpp>
#include <boost/hana/prepend.hpp>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs, typename Sfx>
    constexpr auto suffix_t::operator()(Xs&& xs, Sfx&& sfx) const {
        using M = typename hana::tag_of<Xs>::type;
        using Suffix = BOOST_HANA_DISPATCH_IF(suffix_impl<M>,
            hana::MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::suffix(xs, sfx) requires 'xs' to be a MonadPlus");
    #endif

        return Suffix::apply(static_cast<Xs&&>(xs), static_cast<Sfx&&>(sfx));
    }
    //! @endcond

    template <typename M, bool condition>
    struct suffix_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Z>
        static constexpr auto apply(Xs&& xs, Z&& z) {
            return hana::chain(static_cast<Xs&&>(xs),
                hana::partial(hana::prepend, hana::lift<M>(static_cast<Z&&>(z))));
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_SUFFIX_HPP
