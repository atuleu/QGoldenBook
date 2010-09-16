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
 * \file Prototype.h
 *
 *  \date Sept 16, 2010
 *  \author Alexandre Tuleu
 */

#ifndef QGOLDENBOOK_PROTOTYPE_H_
#define QGOLDENBOOK_PROTOTYPE_H_

#include <memory>

#define IS_A_PROTOTYPE_IMPLEMENTATION(ClassName,BaseClassName) public :\
  virtual std::auto_ptr<BaseClassName> clone() const { \
    return std::auto_ptr<BaseClassName>(new ClassName(*this));\
  }


/**
 * Prototype design pattern templated implementation.
 */
template <typename T> class Prototype {
public:
  Prototype();
  virtual ~Prototype();

  virtual std::auto_ptr<T> clone() const =0;
};

template <typename T>
inline Prototype<T>::Prototype(){
}

template <typename T>
inline Prototype<T>::~Prototype(){
}


#endif // QGOLDENBOOK_PROTOTYPE_H_
