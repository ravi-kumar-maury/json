// Copyright (c) 2016-2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_JSON_INCLUDE_PAIR_HPP
#define TAOCPP_JSON_INCLUDE_PAIR_HPP

#include <string>
#include <type_traits>
#include <utility>

namespace tao
{
   namespace json
   {
      namespace internal
      {
         class data_holder;

         template< typename B, template< typename... > class Traits >
         class proxy;

      }  // namespace internal

      template< template< typename... > class Traits >
      struct pair
      {
         using value_t = internal::proxy< internal::data_holder, Traits >;

         mutable std::string key;
         mutable value_t value;

         template< typename U >
         pair( U&& v )
            : key( Traits< typename std::decay< U >::type >::default_key ),
              value( std::forward< U >( v ) )
         {
         }

         pair( std::string&& k, value_t&& v )
            : key( std::move( k ) ), value( std::move( v ) )
         {
         }

         pair( std::string&& k, const value_t& v )
            : key( std::move( k ) ), value( v )
         {
         }

         pair( const std::string& k, value_t&& v )
            : key( k ), value( std::move( v ) )
         {
         }

         pair( const std::string& k, const value_t& v )
            : key( k ), value( v )
         {
         }

         pair( const char* k, value_t&& v )
            : key( k ), value( std::move( v ) )
         {
         }

         pair( const char* k, const value_t& v )
            : key( k ), value( v )
         {
         }
      };

   }  // namespace json

}  // namespace tao

#endif
