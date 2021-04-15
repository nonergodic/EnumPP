#ifndef AXIOM_DETAIL_ENUMPP_HPP
#define AXIOM_DETAIL_ENUMPP_HPP

#include <string>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/expand.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#include "boost/assert.hpp"
#include "boost/container/flat_set.hpp"
#include <boost/unordered_map.hpp>

namespace Axiom
{
namespace Detail
{

template <typename T>
class NameLink
{
public:
  static std::string const & get_name()
  {
    //assertion fails if T was not defined by our custom macro
    BOOST_ASSERT(name_);
    return *name_;
  }

  static void assign(std::string const & name)
  {
    name_ = &name;
  }

private:
  static std::string const * name_;
};

template <typename T>
std::string const * NameLink<T>::name_ = nullptr;

template <typename T>
struct NameLinkAssigner
{
  static bool invoke_assign()
  {
    NameLink<typename T::Type>::assign(T::get_name());
    return true;
  }

  static bool const invoke_assign_helper_;
};

template <typename T>
bool const NameLinkAssigner<T>::invoke_assign_helper_ = NameLinkAssigner<T>::invoke_assign();

template <typename T>
class ValueSetLink
{
public:
  typedef boost::container::flat_set<T> ValueSet;

  static ValueSet const & get_value_set()
  {
    BOOST_ASSERT(value_set_);
    return *value_set_;
  }

  static void assign(ValueSet const & value_set)
  {
    value_set_ = &value_set;
  }

private:
  static ValueSet const * value_set_;
};

template <typename T>
typename ValueSetLink<T>::ValueSet const * ValueSetLink<T>::value_set_ = nullptr;

template <typename T>
struct ValueSetLinkAssigner
{
  static bool invoke_assign()
  {
    ValueSetLink<typename T::Type>::assign(T::get_value_set());
    return true;
  }

  static bool const invoke_assign_helper_;
};

template <typename T>
bool const ValueSetLinkAssigner<T>::invoke_assign_helper_ = ValueSetLinkAssigner<T>::invoke_assign();

template <typename T>
class StringMapLink
{
public:
  typedef boost::unordered_map<T, std::string> ToStringMap;
  typedef boost::unordered_map<std::string, T> FromStringMap;

  static ToStringMap const & get_to_string_map()
  {
    //assertion fails if T was not defined by our custom macro
    BOOST_ASSERT(to_string_map_);
    return *to_string_map_;
  }

  static FromStringMap const & get_from_string_map()
  {
    //assertion fails if T was not defined by our custom macro
    BOOST_ASSERT(from_string_map_);
    return *from_string_map_;
  }

  static void assign(ToStringMap const & to_string_map, FromStringMap const & from_string_map)
  {
    to_string_map_ = &to_string_map;
    from_string_map_ = &from_string_map;
  }

private:
  static ToStringMap const * to_string_map_;
  static FromStringMap const * from_string_map_;
};

template <typename T>
typename StringMapLink<T>::ToStringMap const * StringMapLink<T>::to_string_map_ = nullptr;

template <typename T>
typename StringMapLink<T>::FromStringMap const * StringMapLink<T>::from_string_map_ = nullptr;

template <typename T>
struct StringMapLinkAssigner
{
  static bool invoke_assign()
  {
    StringMapLink<typename T::Type>::assign(T::get_to_string_map(), T::get_from_string_map());
    return true;
  }

  static bool const invoke_assign_helper_;
};

template <typename T>
bool const StringMapLinkAssigner<T>::invoke_assign_helper_ = StringMapLinkAssigner<T>::invoke_assign();

} //end of namespace Detail

} //end of namespace Axiom

#define AXIOM_X_ENUMPP__NAME_VALUE_1(elem) \
  BOOST_PP_TUPLE_ELEM(0,elem)

#define AXIOM_X_ENUMPP__NAME_VALUE_2(elem) \
  BOOST_PP_TUPLE_ELEM(0,elem) = BOOST_PP_TUPLE_ELEM(1,elem)

#define AXIOM_X_ENUMPP__NAME_VALUE_SEQ(s,data,elem) \
  BOOST_PP_EXPAND(BOOST_PP_CAT(AXIOM_X_ENUMPP__NAME_VALUE_,BOOST_PP_TUPLE_SIZE(elem))(elem))

#define AXIOM_X_ENUMPP__NAME_ONLY_SEQ(s,data,elem) \
  BOOST_PP_TUPLE_ELEM(0,elem)

#define AXIOM_X_ENUMPP__TO_SEQ(seq_type, ...)                                        \
  BOOST_PP_SEQ_TRANSFORM( BOOST_PP_CAT(BOOST_PP_CAT(AXIOM_X_ENUMPP__,seq_type),_SEQ) \
                        , 0                                                             \
                        , BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)                         \
                        )

#define AXIOM_X_ENUMPP__VALUE_SET(r, enum_name, elem) \
  value_set.insert(enum_name::elem);

#define AXIOM_X_ENUMPP__TO_STRING_MAPPING(r, enum_name, elem) \
  to_string_map[enum_name::elem] = BOOST_PP_STRINGIZE(elem);

#define AXIOM_X_ENUMPP__FROM_STRING_MAPPING(r, enum_name, elem) \
  from_string_map[BOOST_PP_STRINGIZE(elem)] = enum_name::elem;

#ifdef _MSC_VER
  #define AXIOM_X_ENUMPP__DO_NOT_OPTIMIZE_AWAY __declspec(dllexport)
#else
  #define AXIOM_X_ENUMPP__DO_NOT_OPTIMIZE_AWAY
#endif

#define AXIOM_X_ENUMPP__NAME_TYPE_1(name_type) \
  BOOST_PP_TUPLE_ELEM(0,name_type)

#define AXIOM_X_ENUMPP__NAME_TYPE_2(name_type) \
  BOOST_PP_TUPLE_ELEM(0,name_type) : BOOST_PP_TUPLE_ELEM(1,name_type)

#define AXIOM_X_ENUMPP__NAME_TYPE_DECLARATION(name_type) \
  BOOST_PP_EXPAND(BOOST_PP_CAT(AXIOM_X_ENUMPP__NAME_TYPE_,BOOST_PP_TUPLE_SIZE(name_type))(name_type))

#define AXIOM_X_ENUMPP(name_type, ...)                                                        \
  enum class AXIOM_X_ENUMPP__NAME_TYPE_DECLARATION(name_type)                                 \
  {                                                                                           \
    BOOST_PP_SEQ_ENUM(AXIOM_X_ENUMPP__TO_SEQ(NAME_VALUE, __VA_ARGS__))                        \
  };                                                                                          \
                                                                                              \
  struct BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(0,name_type),EnumPP)                                \
  {                                                                                           \
    typedef BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(0,name_type),EnumPP) Self;                       \
    typedef BOOST_PP_TUPLE_ELEM(0,name_type) Type;                                            \
                                                                                              \
    static std::string const & get_name()                                                   \
    {                                                                                         \
      static std::string const name = BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(0,name_type)); \
      return name;                                                                            \
    }                                                                                         \
                                                                                              \
    typedef Axiom::Detail::ValueSetLink<Type>::ValueSet ValueSet;                             \
    static ValueSet const & get_value_set()                                                   \
    {                                                                                         \
      struct LocalScope                                                                       \
      {                                                                                       \
        static ValueSet init()                                                                \
        {                                                                                     \
          ValueSet value_set;                                                                 \
                                                                                              \
          BOOST_PP_SEQ_FOR_EACH( AXIOM_X_ENUMPP__VALUE_SET                                    \
                               , BOOST_PP_TUPLE_ELEM(0,name_type)                             \
                               , AXIOM_X_ENUMPP__TO_SEQ(NAME_ONLY, __VA_ARGS__)               \
                               )                                                              \
                                                                                              \
          return value_set;                                                                   \
        }                                                                                     \
      };                                                                                      \
      static ValueSet const value_set = LocalScope::init();                                   \
      return value_set;                                                                       \
    }                                                                                         \
                                                                                              \
    typedef Axiom::Detail::StringMapLink<Type>::ToStringMap ToStringMap;                      \
    static ToStringMap const& get_to_string_map()                                             \
    {                                                                                         \
      struct LocalScope                                                                       \
      {                                                                                       \
        static ToStringMap init()                                                             \
        {                                                                                     \
          ToStringMap to_string_map;                                                          \
                                                                                              \
          BOOST_PP_SEQ_FOR_EACH( AXIOM_X_ENUMPP__TO_STRING_MAPPING                            \
                               , BOOST_PP_TUPLE_ELEM(0,name_type)                             \
                               , AXIOM_X_ENUMPP__TO_SEQ(NAME_ONLY, __VA_ARGS__)               \
                               )                                                              \
                                                                                              \
          return to_string_map;                                                               \
        }                                                                                     \
      };                                                                                      \
      static ToStringMap const to_string_map = LocalScope::init();                            \
      return to_string_map;                                                                   \
    }                                                                                         \
                                                                                              \
    typedef Axiom::Detail::StringMapLink<Type>::FromStringMap FromStringMap;                  \
    static FromStringMap const& get_from_string_map()                                         \
    {                                                                                         \
      struct LocalScope                                                                       \
      {                                                                                       \
        static FromStringMap init()                                                           \
        {                                                                                     \
          FromStringMap from_string_map;                                                      \
                                                                                              \
          BOOST_PP_SEQ_FOR_EACH( AXIOM_X_ENUMPP__FROM_STRING_MAPPING                          \
                               , BOOST_PP_TUPLE_ELEM(0,name_type)                             \
                               , AXIOM_X_ENUMPP__TO_SEQ(NAME_ONLY, __VA_ARGS__)               \
                               )                                                              \
                                                                                              \
          return from_string_map;                                                             \
        }                                                                                     \
      };                                                                                      \
      static FromStringMap const from_string_map = LocalScope::init();                        \
      return from_string_map;                                                                 \
    }                                                                                         \
                                                                                              \
  private:                                                                                    \
    AXIOM_X_ENUMPP__DO_NOT_OPTIMIZE_AWAY                                                      \
    bool never_called_but_force_initialization()                                              \
    {                                                                                         \
      return Axiom::Detail::NameLinkAssigner<Self>::invoke_assign_helper_                     \
          && Axiom::Detail::ValueSetLinkAssigner<Self>::invoke_assign_helper_                 \
          && Axiom::Detail::StringMapLinkAssigner<Self>::invoke_assign_helper_;               \
    }                                                                                         \
  }

#endif
