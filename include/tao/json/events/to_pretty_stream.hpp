// Copyright (c) 2016-2019 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAO_JSON_EVENTS_TO_PRETTY_STREAM_HPP
#define TAO_JSON_EVENTS_TO_PRETTY_STREAM_HPP

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <ostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "../binary_view.hpp"

#include "../external/itoa.hpp"
#include "../external/ryu.hpp"

#include "../internal/escape.hpp"

namespace tao::json::events
{
   // Events consumer to build a JSON pretty string representation.

   class to_pretty_stream
   {
   protected:
      char buffer[ 32 ];
      std::ostream& os;
      const std::size_t indent;
      const std::string eol;

      std::size_t current_indent = 0;

      bool first = true;
      bool after_key = true;

      void next_line()
      {
         os << eol;
         std::size_t len = current_indent;
         while( len != 0 ) {
            const auto chunk = ( std::min )( indent, sizeof( buffer ) );
            os.write( buffer, chunk );
            len -= chunk;
         }
      }

      void next()
      {
         if( !first ) {
            os.put( ',' );
         }
         if( after_key ) {
            after_key = false;
         }
         else {
            next_line();
         }
      }

   public:
      template< typename S >
      to_pretty_stream( std::ostream& in_os, const std::size_t in_indent, S&& in_eol )
         : buffer(),
           os( in_os ),
           indent( in_indent ),
           eol( std::forward< S >( in_eol ) )
      {
         std::memset( buffer, os.fill(), sizeof( buffer ) );
      }

      to_pretty_stream( std::ostream& in_os, const std::size_t in_indent )
         : to_pretty_stream( in_os, in_indent, "\n" )
      {
      }

      void null()
      {
         next();
         os.write( "null", 4 );
      }

      void boolean( const bool v )
      {
         next();
         if( v ) {
            os.write( "true", 4 );
         }
         else {
            os.write( "false", 5 );
         }
      }

      void number( const std::int64_t v )
      {
         next();
         itoa::i64tos( os, v );
      }

      void number( const std::uint64_t v )
      {
         next();
         itoa::u64tos( os, v );
      }

      void number( const double v )
      {
         next();
         if( !std::isfinite( v ) ) {
            // if this throws, consider using non_finite_to_* transformers
            throw std::runtime_error( "non-finite double value invalid for JSON string representation" );
         }
         ryu::d2s_stream( os, v );
      }

      void string( const std::string_view v )
      {
         next();
         os.put( '"' );
         internal::escape( os, v );
         os.put( '"' );
      }

      void binary( const tao::binary_view /*unused*/ )
      {
         // if this throws, consider using binary_to_* transformers
         throw std::runtime_error( "binary data invalid for JSON string representation" );
      }

      void begin_array( const std::size_t /*unused*/ = 0 )
      {
         next();
         os.put( '[' );
         current_indent += indent;
         first = true;
      }

      void element() noexcept
      {
         first = false;
      }

      void end_array( const std::size_t /*unused*/ = 0 )
      {
         current_indent -= indent;
         if( !first ) {
            next_line();
         }
         os.put( ']' );
      }

      void begin_object( const std::size_t /*unused*/ = 0 )
      {
         next();
         os.put( '{' );
         current_indent += indent;
         first = true;
      }

      void key( const std::string_view v )
      {
         string( v );
         os.write( ": ", 2 );
         first = true;
         after_key = true;
      }

      void member() noexcept
      {
         first = false;
      }

      void end_object( const std::size_t /*unused*/ = 0 )
      {
         current_indent -= indent;
         if( !first ) {
            next_line();
         }
         os.put( '}' );
      }
   };

}  // namespace tao::json::events

#endif
