// { dg-do compile }
// 2001-06-21  Benjamin Kosnik  <bkoz@redhat.com>

// Copyright (C) 2001-2025 Free Software Foundation, Inc.
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

// 24.4.2.1 Template class back_insert_iterator

#include <iterator>
#include <list>

// Check data member 'container' accessible.
class test_dm : public std::back_insert_iterator<std::list<int> >
{
  container_type l;
  container_type* p;
public:
  test_dm():  std::back_insert_iterator<std::list<int> >(l), p(container) { }
};
