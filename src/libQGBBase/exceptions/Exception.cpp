/**
 * \file Exception.cpp
 *
 *  \date Jul 19, 2010
 *  \author tuleu
 */

#include "Exception.h"


  Exception::Exception() throw(){

  }

  Exception::~Exception() throw(){
  }

  Exception::Exception(const Exception & exc)
  : std::exception(exc){
    d_os<<exc.d_os.str();
  }


  const char* Exception::what() const throw(){
    return d_os.str().c_str();
  }

  std::ostringstream & Exception::stream() throw(){
    return d_os;
  }
