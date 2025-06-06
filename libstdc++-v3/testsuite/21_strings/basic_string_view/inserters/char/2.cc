
// Copyright (C) 2013-2025 Free Software Foundation, Inc.
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

// inserters

// NB: This file is predicated on sstreams, ostreams
// working, not to mention other major details like char_traits, and
// all of the string_view class.

// { dg-do run { target c++17 } }
// { dg-require-fileio "" }

#include <string_view>
#include <string>
#include <fstream>
#include <iostream>
#include <testsuite_hooks.h>

// testing basic_filebuf::xsputn via stress testing with large string_views
// based on a bug report libstdc++ 9
// mode == out
void
test05(std::size_t size)
{
  bool test = true;

  const char filename[] = "inserters_extractors-2.txt";
  const char fillc = 'f';
  std::ofstream ofs(filename);
  std::string str(size, fillc);
  std::string_view strv{str};

  // sanity checks
  VERIFY( str.size() == size );
  VERIFY( ofs.good() );

  // stress test
  ofs << str << std::endl;
  if (!ofs.good()) 
    test = false;

  ofs << str << std::endl;
  if (!ofs.good()) 
    test = false;

  VERIFY( str.size() == size );
  VERIFY( ofs.good() );

  ofs.close();

  // sanity check on the written file
  std::ifstream ifs(filename);
  std::size_t count = 0;
  char c;
  while (count <= (2 * size) + 4)
    {
      ifs >> c;
      if (ifs.good() && c == fillc)
	{
	  ++count;
	  c = '0';
	}
      else 
	break;
    }

  VERIFY( count == 2 * size );
}

int
main()
{
  test05(1); 
  test05(1000); 
  test05(10000);

  return 0;
}
