#ifndef AXIOM_ENUMPP_HPP
#define AXIOM_ENUMPP_HPP

#include <type_traits>

#include "enum_pp_detail.hpp"
#include "exception.hpp"

#define AXIOM_ENUMPP(enum_name, ...) \
  AXIOM_X_ENUMPP(enum_name, __VA_ARGS__)

namespace Axiom
{

struct BadConversion : virtual Exception {};

template <typename T>
typename std::enable_if<std::is_enum<T>::value, std::string>::type const & get_name();

template <typename T, typename IntType>
typename std::enable_if<std::is_enum<T>::value, bool>::type is_valid(IntType value);

template <typename T>
typename std::enable_if<std::is_enum<T>::value, std::string>::type const & to_string(T value);

template <typename T>
typename std::enable_if<std::is_enum<T>::value, T>::type from_string(std::string const & str);

template <typename T>
typename std::enable_if<std::is_enum<T>::value, typename Detail::ValueSetLink<T>::ValueSet>::type const & get_value_set();

template <typename T>
typename std::enable_if<std::is_enum<T>::value, typename Detail::StringMapLink<T>::ToStringMap>::type const & get_to_string_map();

template <typename T>
typename std::enable_if<std::is_enum<T>::value, typename Detail::StringMapLink<T>::FromStringMap>::type const & get_from_string_map();

//------------------------------------------------------------------------------------------------
//              Implementation
//------------------------------------------------------------------------------------------------

template <typename T>
typename std::enable_if<std::is_enum<T>::value, std::string>::type const & get_name()
{
  return Detail::NameLink<T>::get_name();
}

template <typename T, typename IntType>
typename std::enable_if<std::is_enum<T>::value, bool>::type is_valid(IntType value)
{
  return get_value_set<T>().find(static_cast<T>(value)) != get_value_set<T>().end();
}

template <typename T>
typename std::enable_if<std::is_enum<T>::value, std::string>::type const & to_string(T value)
{
  auto && it = get_to_string_map<T>().find(value);
  if (it == get_to_string_map<T>().end())
  {
    throw make_exception<BadConversion>("cannot convert invalid value: " + to_string(value) + " of enum: " + get_name<T>() + " to string");
  }
  return it->second;
}

template <typename T>
typename std::enable_if<std::is_enum<T>::value, T>::type from_string(std::string const & str)
{
  auto && it = get_from_string_map<T>().find(str);
  if (it == get_from_string_map<T>().end())
  {
    throw make_exception<BadConversion>("cannot convert invalid string: \"" + str + "\" to enum value for enum: " + get_name<T>());
  }
  return it->second;
}

template <typename T>
typename std::enable_if<std::is_enum<T>::value, typename Detail::ValueSetLink<T>::ValueSet>::type const & get_value_set()
{
  return Detail::ValueSetLink<T>::get_value_set();
}

template <typename T>
typename std::enable_if<std::is_enum<T>::value, typename Detail::StringMapLink<T>::ToStringMap>::type const & get_to_string_map()
{
  return Detail::StringMapLink<T>::get_to_string_map();
}

template <typename T>
typename std::enable_if<std::is_enum<T>::value, typename Detail::StringMapLink<T>::FromStringMap>::type const & get_from_string_map()
{
  return Detail::StringMapLink<T>::get_from_string_map();
}

} //end of namespace Axiom

#endif
