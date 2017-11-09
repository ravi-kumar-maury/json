// Copyright (c) 2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#include "test.hpp"

#include <tao/json/external/string_view.hpp>
#include <tao/json/value.hpp>

namespace tao
{
   namespace json
   {
      void unit_test()
      {
         const char* p = "Hello, world!";
         const std::string s = p;
         const tao::string_view sv = p;

         TEST_ASSERT( s == p );
         TEST_ASSERT( p == s );
         TEST_ASSERT( s == s );
         TEST_ASSERT( sv == p );
         TEST_ASSERT( sv == s );
         TEST_ASSERT( p == sv );
         TEST_ASSERT( s == sv );
         TEST_ASSERT( sv == sv );

         TEST_ASSERT( sv.find( '!' ) == 12 );
         TEST_ASSERT( sv.find_first_not_of( "elo, wrd", 1 ) == 12 );

         // the default is copying all string_views
         const value vp = p;
         const value vs = s;
         const value vsv = sv;

         TEST_ASSERT( vp.type() == type::STRING );
         TEST_ASSERT( vs.type() == type::STRING );
         TEST_ASSERT( vsv.type() == type::STRING );

         TEST_ASSERT( vp.as< const char* >() == s );
         TEST_ASSERT( vp.as< tao::string_view >() == s );
         TEST_ASSERT( vp.as< std::string >() == s );
         TEST_ASSERT( vp.as< const std::string& >() == s );

         TEST_ASSERT( vs.as< const char* >() == s );
         TEST_ASSERT( vs.as< tao::string_view >() == s );
         TEST_ASSERT( vs.as< std::string >() == s );
         TEST_ASSERT( vs.as< const std::string& >() == s );

         TEST_ASSERT( vsv.as< const char* >() == s );
         TEST_ASSERT( vsv.as< tao::string_view >() == s );
         TEST_ASSERT( vsv.as< std::string >() == s );
         TEST_ASSERT( vsv.as< const std::string& >() == s );

         // storing a string_view is possible
         value v;
         v.unsafe_assign_string_view( sv );

         TEST_ASSERT( v.type() == type::STRING_VIEW );

         TEST_ASSERT( v.as< tao::string_view >() == s );
         TEST_ASSERT( v.as< std::string >() == s );
      }

   }  // namespace json

}  // namespace tao

#include "main.hpp"
