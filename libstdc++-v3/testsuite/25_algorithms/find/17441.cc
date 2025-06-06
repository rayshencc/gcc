// Copyright (C) 2004-2025 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

// 25.3.1 algorithms, find()

#include <algorithm>

using namespace std;

template<typename InputIterator, typename Tp>
  InputIterator
  find(InputIterator first, InputIterator,
       const Tp&, input_iterator_tag)
  { return first; }

// libstdc++/17441
void test01()
{
  input_iterator_tag a;
  int i;
  find(&i, &i, 1, a);
}

int main()
{
  test01();
  return 0;
}
