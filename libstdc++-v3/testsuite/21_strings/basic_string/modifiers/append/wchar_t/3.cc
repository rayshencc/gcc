// 2004-25-10  Paolo Carlini  <pcarlini@suse.de>

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

// 21.3.5 string modifiers

// { dg-options "-DITERATIONS=14" { target simulator } }

#ifndef ITERATIONS
#define ITERATIONS 18
#endif

#include <string>
#include <testsuite_hooks.h>

// Upon reallocation (basic_string::reserve) we were copying from
// deallocated memory.
void
test03()
{
  using namespace std;
 
  const wchar_t * source = L"Kesto";

  for (unsigned i = 0; i < 10; ++i)
    {
      wstring one(source);
      wstring two(source);
      for (unsigned j = 0; j < ITERATIONS; ++j)
	{
	  VERIFY( one == two );
	  one.append(one);
	  one += L'x';
	  two.append(two.c_str(), two.size());
	  two += L'x';
	}
    }
}

int main()
{ 
  test03();
  return 0;
}
