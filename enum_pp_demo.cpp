#include <iostream>

#include "enum_pp.hpp"

#if true //change to false to test nested enums
  AXIOM_ENUMPP((ShadeOfGrey,uint8_t), (Black,0),(AlmostBlack),(White,255));
  typedef ShadeOfGrey TestEnum;
#else
  struct SomeStruct
  {
    AXIOM_ENUMPP((ShadeOfGrey,uint8_t), (Black,0),(AlmostBlack),(White,255));
  };

  typedef SomeStruct::ShadeOfGrey TestEnum;
#endif

template <typename T>
void foo(T my_tag)
{
  std::cout << "name of enum: " << Axiom::get_name<T>() << std::endl;
  
  std::cout << "using value 'AlmostBlack' to retrieve string: " << Axiom::to_string(my_tag) << std::endl;
  std::cout << "using string \"AlmostBlack\" to retrieve value: " << static_cast<int>(Axiom::from_string<T>("AlmostBlack")) << std::endl;
  
  for (auto&& it : Axiom::get_to_string_map<T>())
  {
    std::cout << "value: " << static_cast<int>(it.first) << " name: " << it.second << std::endl;
  }
  
  try
  {
    Axiom::from_string<T>("not a valid enum value");
  }
  catch(Axiom::Exception const & e)
  {
    std::cout << "caught expected exception: " << e.what() << std::endl;
  }
}

int main()
{
  foo(TestEnum::AlmostBlack);
}

