// Copyright (c) 2016 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_JSON_INCLUDE_SAX_DISCARD_HH
#define TAOCPP_JSON_INCLUDE_SAX_DISCARD_HH

#include <cstdint>
#include <string>

namespace tao
{
   namespace json
   {
      namespace sax
      {
         // SAX consumer does nothing
         struct discard
         {
            void null() {}

            void boolean( const bool ) {}

            void number( const std::int64_t ) {}
            void number( const std::uint64_t ) {}
            void number( const double ) {}

            void string( const std::string & ) {}

            // array
            void begin_array() {}
            void element() {}
            void end_array() {}

            // object
            void begin_object() {}
            void key( const std::string & ) {}
            void member() {}
            void end_object() {}
         };

      } // sax

   } // json

} // tao

#endif
