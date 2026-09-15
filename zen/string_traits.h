// *****************************************************************************
// * This file is part of the FreeFileSync project. It is distributed under    *
// * GNU General Public License: https://www.gnu.org/licenses/gpl-3.0          *
// * Copyright (C) Zenju (zenju AT freefilesync DOT org) - All Rights Reserved *
// *****************************************************************************
#pragma once

#include <cstring> //strlen
#include <string_view>
#include "type_traits.h"

//uniform access to string-like types, both classes and character arrays
namespace zen
{
/*  isStringLike<>:
        isStringLike<const wchar_t*> //equals "true"
        isStringLike<const int*>     //equals "false"

    GetCharTypeT<>:
        GetCharTypeT<std::wstring> //equals wchar_t
        GetCharTypeT<wchar_t[5]>   //equals wchar_t

    strSize():
        strSize(str);   //equals str.size()
        strSize(array); //equals cStringSize(array)

    strBegin():         -> not null-terminated! -> may be nullptr if length is 0!
        std::wstring str(L"dummy");
        char array[] = "dummy";
        strBegin(str);   //returns str.c_str()
        strBegin(array); //returns &array[0]                              */



//---------------------- implementation ----------------------
namespace impl
{
enum class StringType
{
    class_,
    view,
    cstr,
};

template <class S, StringType st>
class GetCharTypeImpl;


template <class S>
class GetCharTypeImpl<S, StringType::class_>
{
    static char    conversionType(const char*);
    static wchar_t conversionType(const wchar_t*);
    //static char8_t  conversionType(const char8_t*);
    //static char16_t conversionType(const char16_t*);
    //static char32_t conversionType(const char32_t*);
    static void    conversionType(...);

public:
    using Type = decltype(conversionType(std::declval<S>().c_str()));
    //using Type = typename S::value_type;
    /*DON'T use S::value_type:
        1. support Glib::ustring: value_type is "unsigned int" but c_str() returns "const char*"
        2. wxString, wxWidgets v2.9, has some questionable string design: wxString::c_str() returns a proxy (wxCStrData) which
           is implicitly convertible to *both* "const char*" and "const wchar_t*" while wxString::value_type is a wrapper around an unsigned int
    */
};

template <class Char>
constexpr bool isSupportedCharType =
    std::is_same_v<Char, char> ||
    std::is_same_v<Char, wchar_t>;
//std::is_same_v<Char, char8_t>  ||
//std::is_same_v<Char, char16_t> ||
//std::is_same_v<Char, char32_t>;


template <class Elem, class Traits>
class GetCharTypeImpl<std::basic_string_view<Elem, Traits>, StringType::view>
{
    using Char = std::remove_cv_t<Elem>; //handle std::basic_string_view<const char>

public:
    using Type = std::conditional_t<isSupportedCharType<Char>, Char, void>;
};


template <class S>
class GetCharTypeImpl<S, StringType::cstr>
{
    using NonArrayType = std::remove_extent_t <S>;
    using NonPtrType   = std::remove_pointer_t<NonArrayType>;
    using Char         = std::remove_cv_t     <NonPtrType>; //handle "const char* const"

public:
    using Type = std::conditional_t<isSupportedCharType<Char>, Char, void>;
};


ZEN_INIT_DETECT_MEMBER_TYPE(value_type)
ZEN_INIT_DETECT_MEMBER(c_str) //we don't know the exact declaration of the member attribute and it may be in a base class!
ZEN_INIT_DETECT_MEMBER(size)  //

template <class T>                  constexpr bool isStringViewImpl = false;
template <class Elem, class Traits> constexpr bool isStringViewImpl<std::basic_string_view<Elem, Traits>> = true;


template <class S>
class StringTraits
{
    using CleanType = std::remove_cvref_t<S>;

public:
    static constexpr bool isStringClass = hasMemberType_value_type<CleanType> &&
                                          hasMember_c_str         <CleanType> &&
                                          hasMember_size          <CleanType>;

    static constexpr bool isStringView = isStringViewImpl<CleanType>;

    using CharType = typename GetCharTypeImpl<CleanType,
          isStringClass ? StringType::class_ :
          isStringView  ? StringType::view :
          StringType::cstr>::Type;
};
}


template <class T>
using GetCharTypeT = typename impl::StringTraits<T>::CharType;

template <class T>
constexpr bool isStringLike = !std::is_same_v<GetCharTypeT<T>, void>;


namespace impl
{
template <class S, typename = std::enable_if_t<StringTraits<S>::isStringClass>> inline
const GetCharTypeT<S>* strBegin(const S& str) { return str.c_str(); }

template <class S, typename = std::enable_if_t<StringTraits<S>::isStringView>> inline
const GetCharTypeT<S>* strBegin(S ref) { return ref.data(); }

inline const char*    strBegin(const char*    str) { return str; }
inline const wchar_t* strBegin(const wchar_t* str) { return str; }

inline const char*    strBegin(const char&    ch)  { return &ch; }
inline const wchar_t* strBegin(const wchar_t& ch)  { return &ch; }
inline const char*    strBegin(   char&&) = delete;
inline const wchar_t* strBegin(wchar_t&&) = delete;


template <class S, typename = std::enable_if_t<StringTraits<S>::isStringClass>> inline
size_t strSize(const S& str) { return str.size(); }

template <class S, typename = std::enable_if_t<StringTraits<S>::isStringView>> inline
size_t strSize(S ref) { return ref.size(); }

#if 0
template <class Char> inline
size_t cStringSize(const Char* str)
{
    size_t len = 0;
    while (*str++ != 0)
        ++len;
    return len;
}
#endif
//no significant perf difference for "comparison" test case between cStringSize/wcslen:
inline size_t strSize(const char*    str) { return std::strlen(str); }
inline size_t strSize(const wchar_t* str) { return std::wcslen(str); }
inline size_t strSize(char)               { return 1; }
inline size_t strSize(wchar_t)            { return 1; }
}


template <class S> inline
auto strBegin(S&& str)
{
    static_assert(isStringLike<S>);
    return impl::strBegin(std::forward<S>(str));
}


template <class S> inline
size_t strSize(S&& str)
{
    static_assert(isStringLike<S>);
    return impl::strSize(std::forward<S>(str));
}
}
