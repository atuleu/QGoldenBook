/*
 * Copyright (c) 2010 Alexandre Tuleu
 *
 * This file is part of QGoldenBook
 *
 * QGoldenBook is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QGoldenBook is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libamarsi-quad.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
/**
 * \file Factory.h
 *
 *  \date Jul 15, 2010
 *  \author tuleu
 */

#ifndef LIBAMARSI_QUAD_FACTORY_H_
#define LIBAMARSI_QUAD_FACTORY_H_



#include <map>
#include <memory>
#include <string>

#include <libQGBBase/exceptions/Exception.h>

/**
 * Key is ALready registered in the Factory
 */
class AlreadyRegisteredKeyAllFatory : public Exception {
public :
  AlreadyRegisteredKeyAllFatory() throw(){}
  virtual ~AlreadyRegisteredKeyAllFatory() throw(){}
};
/**
 * Key is not registered in teh Factory
 */
class UnregisteredKeyAllFactory : public Exception {
public :
  UnregisteredKeyAllFactory() throw(){}
  virtual ~UnregisteredKeyAllFactory() throw(){}
};


/**
 * Factory design pattern templated implementation.
 *
 *
 */
template<typename Object, typename Key = std::string >
class Factory {
public :

  //============================================================================
  // EXCEPTIONS
  //============================================================================
  class AlreadyRegisteredKey : public AlreadyRegisteredKeyAllFatory{
  public :
    AlreadyRegisteredKey(const Key & key,
                         const Object *e) throw();
    virtual ~AlreadyRegisteredKey() throw();

    const Key & key() const throw();

  private :
     Key d_key;
  };

  class UnregisteredKey : public UnregisteredKeyAllFactory{
  public :
    UnregisteredKey(const Key & key) throw();
    virtual ~UnregisteredKey() throw();

    const Key & key() const throw();
  private :
     Key d_key;
  };
  //============================================================================
  // CLASS DEFINITION
  //============================================================================
  static bool registerObject(const Key & key, const Object & object);
  static bool isRegistered(const Key & key);

  static std::auto_ptr<Object> create(const Key & key);

private :
  typedef std::map<Key,Object*> SetOfClass;
  static SetOfClass s_registeredClasses;
};

//==============================================================================
// CLASS IMPLEMENTATION
//==============================================================================

template <typename Object, typename Key>
inline bool Factory<Object,Key>::registerObject(const Key & key,
                                                const Object & object){

  if(isRegistered(key))
    throw AlreadyRegisteredKey(key,s_registeredClasses[key]);
  s_registeredClasses.insert(std::make_pair(key,object.clone().release()));
  return true;
}

template <typename Object, typename Key>
inline std::auto_ptr<Object> Factory<Object,Key>::create(const Key & key){
  typename SetOfClass::const_iterator fi = s_registeredClasses.find(key);
  if(fi==s_registeredClasses.end()){
    throw UnregisteredKey(key);
  }
  return fi->second->clone();
}

template <typename Object, typename Key>
inline bool Factory<Object,Key>::isRegistered(const Key & key){
  typename SetOfClass::const_iterator fi = s_registeredClasses.find(key);
  return fi != s_registeredClasses.end();
}


template <typename Object, typename Key>
typename Factory<Object,Key>::SetOfClass Factory<Object,Key>::s_registeredClasses;




//==============================================================================
// EXCEPTION IMPLEMENTATION
//==============================================================================

template <typename Object, typename Key>
Factory<Object,Key>::AlreadyRegisteredKey
  ::AlreadyRegisteredKey(const Key & key, const Object* e) throw()
    : d_key(key){
  stream()<<"[AlreadyRegisteredKey] Key '"
          <<key<<"' is already registered with object "<<e<<"."<<std::endl;
}

template <typename Object, typename Key>
Factory<Object,Key>::AlreadyRegisteredKey::~AlreadyRegisteredKey() throw(){

}

template <typename Object, typename Key>
const Key & Factory<Object,Key>::AlreadyRegisteredKey::key() const throw(){
    return d_key;
}

template <typename Object, typename Key>
Factory<Object,Key>::UnregisteredKey::UnregisteredKey(const Key & key) throw()
  : d_key(key){
  stream()<<"[UnregisteredKey] : Key '"<<key<<"' is not registered in the factory"
          <<std::endl;
}

template <typename Object, typename Key>
Factory<Object,Key>::UnregisteredKey::~UnregisteredKey() throw(){

}
template <typename Object, typename Key>
const Key & Factory<Object,Key>::UnregisteredKey::key() const throw(){
  return d_key;
}

#endif // LIBAMARSI_QUAD_FACTORY_H_
