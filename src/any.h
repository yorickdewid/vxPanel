#include <typeinfo>

class any
{
  class internal
  { 
    std::type_info _data_type;
  };

  template <typename T>
  class internal_typed : public internal
  {
    T _data;
  };

  internal *_internal;      
};

template<typename T>
T any_cast(any &a)
{
  any::internal intern = a._internal;
  if (typeid(T) == intern._data_type)
  {
    return ((any::internal_typed<T>*)a._internal)->_data;
  }

  // throw type error
}