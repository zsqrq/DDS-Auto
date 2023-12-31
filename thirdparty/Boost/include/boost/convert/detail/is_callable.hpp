// Copyright (c) 2009-2020 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_IS_CALLABLE_HPP
#define BOOST_CONVERT_IS_CALLABLE_HPP

#include <boost/convert/detail/has_member.hpp>

namespace boost { namespace cnv { namespace detail
{
    using yes_type = ::boost::type_traits::yes_type;
    using  no_type = ::boost::type_traits:: no_type;

    struct not_found {};
    struct void_return_substitute {};

    // The overloaded comma operator only kicks in for U != void essentially short-circuiting
    // itself ineffective. Otherwise, when U=void, the standard op,() kicks in and returns
    // 'void_return_substitute'.
    template<typename U> U const& operator, (U const&, void_return_substitute);
    template<typename U> U&       operator, (U&,       void_return_substitute);

    template <typename src, typename dst> struct match_const { using type = dst; };
    template <typename src, typename dst> struct match_const<src const, dst> { using type = dst const; };

    template<typename T, typename return_type>
    struct redirect
    {
        static no_type  test (...);
        static yes_type test (return_type);
    };

    template<typename T>
    struct redirect<T, void>
    {
        static yes_type test (...);
        static no_type  test (not_found);
    };
}}}

// No-args case needs to be implemented differently and has not been implemented yet.
//        template <typename R>
//        struct check<true, R ()>

// C1. Need to find some unique/ugly names so that they do not clash if this macro is
//     used inside some other template class;
// C2. Body of the function is not actually used anywhere.
//     However, Intel C++ compiler treats it as an error. So, we provide the body.

#define BOOST_DECLARE_IS_CALLABLE(__trait_name__, __member_name__)                          \
                                                                                            \
template <typename __boost_is_callable_T__, typename __boost_is_callable_signature__>       \
class __trait_name__                                                                        \
{                                                                                           \
    using class_type = __boost_is_callable_T__; /*C1*/                                      \
    using  signature = __boost_is_callable_signature__; /*C1*/                              \
    using  not_found = boost::cnv::detail::not_found;                                       \
                                                                                            \
    BOOST_DECLARE_HAS_MEMBER(has_member, __member_name__);                                  \
                                                                                            \
    struct mixin : class_type                                                               \
    {                                                                                       \
        using class_type::__member_name__;                                                  \
        not_found __member_name__(...) const { return not_found(); /*C2*/}                  \
    };                                                                                      \
    using mixin_ptr = typename boost::cnv::detail::match_const<class_type, mixin>::type*;   \
                                                                                            \
    template <bool has, typename F> struct check { static bool const value = false; };      \
                                                                                            \
    template <typename Arg1, typename R>                                                    \
    struct check<true, R (Arg1)>                                                            \
    {                                                                                       \
        using a1 = typename boost::decay<Arg1>::type*;                                      \
                                                                                            \
        static bool BOOST_CONSTEXPR_OR_CONST value =                                                       \
            sizeof(boost::type_traits::yes_type) ==                                         \
            sizeof(boost::cnv::detail::redirect<class_type, R>::test(                       \
                (mixin_ptr(0)->__member_name__(*a1(0)),                                     \
                boost::cnv::detail::void_return_substitute())));                            \
    };                                                                                      \
    template <typename Arg1, typename Arg2, typename R>                                     \
    struct check<true, R (Arg1, Arg2)>                                                      \
    {                                                                                       \
        using a1 = typename boost::decay<Arg1>::type*;                                      \
        using a2 = typename boost::decay<Arg2>::type*;                                      \
                                                                                            \
        static bool BOOST_CONSTEXPR_OR_CONST value =                                                       \
            sizeof(boost::type_traits::yes_type) ==                                         \
            sizeof(boost::cnv::detail::redirect<class_type, R>::test(                       \
                (mixin_ptr(0)->__member_name__(*a1(0), *a2(0)),                             \
                boost::cnv::detail::void_return_substitute())));                            \
    };                                                                                      \
                                                                                            \
    public:                                                                                 \
                                                                                            \
    /* Check the existence of __member_name__ first, then the signature. */                 \
    static bool BOOST_CONSTEXPR_OR_CONST value = check<has_member<class_type>::value, signature>::value;   \
}

#endif // BOOST_CONVERT_IS_CALLABLE_HPP
