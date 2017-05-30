// Copyright (c) 2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_JSON_INCLUDE_CBOR_TO_STREAM_HPP
#define TAOCPP_JSON_INCLUDE_CBOR_TO_STREAM_HPP

#include <cstdint>
#include <ostream>
#include <string>

#include "major.hpp"

#include "../internal/temporary.hpp"

namespace tao
{
   namespace json
   {
      namespace cbor
      {
         class to_stream
         {
         private:
            std::ostream& os;

         public:
            explicit to_stream( std::ostream& os ) noexcept
               : os( os )
            {
            }

            void null()
            {
               os.put( char( std::uint8_t( major::OTHER ) + 22 ) );
            }

            void boolean( const bool v )
            {
               os.put( char( std::uint8_t( major::OTHER ) + 20 + std::uint8_t( v ) ) );
            }

            void number( const major m, const std::uint64_t v )
            {
               if( v < 24 ) {
                  os.put( char( std::uint8_t( m ) + v ) );
               }
               else if( v < 256 ) {
                  os.put( char( std::uint8_t( m ) + 24 ) );
                  os.put( char( v ) );
               }
               else if( v < 65536 ) {
                  os.put( char( std::uint8_t( m ) + 25 ) );
                  const std::uint16_t x = json::internal::h_to_be( std::uint16_t( v ) );
                  os.write( reinterpret_cast< const char* >( &x ), sizeof( x ) );
               }
               else if( v < 4294967296ull ) {
                  os.put( char( std::uint8_t( m ) + 26 ) );
                  const std::uint32_t x = json::internal::h_to_be( std::uint32_t( v ) );
                  os.write( reinterpret_cast< const char* >( &x ), sizeof( x ) );
               }
               else {
                  os.put( char( std::uint8_t( m ) + 27 ) );
                  const std::uint64_t x = json::internal::h_to_be( v );
                  os.write( reinterpret_cast< const char* >( &x ), sizeof( x ) );
               }
            }

            void number( const std::int64_t v )
            {
               if( v >= 0 ) {
                  number( major::UNSIGNED, v );
               }
               else {
                  number( major::NEGATIVE, -( v + 1 ) );
               }
            }

            void number( const std::uint64_t v )
            {
               number( major::UNSIGNED, v );
            }

            void number( const double )
            {
               assert( false );  // TODO
            }

            void string( const std::string& v )
            {
               number( major::STRING, v.size() );
               os.write( v.data(), v.size() );
            }

            void begin_array()
            {
               os.put( char( std::uint8_t( major::ARRAY ) + minor_mask ) );
            }

            void begin_array( const std::size_t size )
            {
               number( major::ARRAY, size );
            }

            void element() noexcept
            {
            }

            void end_array()
            {
               os.put( char( 0xff ) );
            }

            void end_array( const std::size_t ) noexcept
            {
            }

            void begin_object()
            {
               os.put( char( std::uint8_t( major::OBJECT ) + minor_mask ) );
            }

            void begin_object( const std::size_t size )
            {
               number( major::OBJECT, size );
            }

            void key( const std::string& v )
            {
               string( v );
            }

            void member() noexcept
            {
            }

            void end_object()
            {
               os.put( char( 0xff ) );
            }

            void end_object( const std::size_t ) noexcept
            {
            }
         };

      }  // namespace cbor

   }  // namespace json

}  // namespace tao

#endif
