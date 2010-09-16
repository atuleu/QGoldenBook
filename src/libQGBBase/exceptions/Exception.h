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
 * \file Exception.h
 *
 *  \date Jul 19, 2010
 *  \author tuleu
 */

#ifndef QGOLDENBOOK_EXCEPTION_H_
#define QGOLDENBOOK_QUAD_EXCEPTION_H_

#include <exception>
#include <iostream>
#include <sstream>

#define THROW_EXCEPTION(ExceptionName,reason){\
  ExceptionName e;\
  e.stream()<<reason<<std::endl;\
  throw e;\
}


class Exception;
/**
 * Base Exception class. All exception thrown by libamarsi-bench derived from this
 * class.
 *
 * They are built on a std::ostringstream if you want to built your own excpetion,
 * you can iteratively construct the error message by calling stream().
 */
class Exception : public std::exception {
public:
  Exception() throw();
  virtual ~Exception() throw();
  Exception(const Exception & exc);

  /**
   * Implementation of the what() method for all Exception
   * @return
   */
  virtual const char* what() const throw();

  /**
   *
   * @return a reference to the intern stream of the exception
   *         (stream displayed by what() ).
   */
  std::ostringstream & stream() throw();

private :
  std::ostringstream d_os;
};



#endif // LIBAMARSI_QUAD_EXCEPTION_H_
