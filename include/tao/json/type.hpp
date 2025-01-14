// Copyright (c) 2015-2019 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAO_JSON_TYPE_HPP
#define TAO_JSON_TYPE_HPP

#include <cstdint>
#include <string_view>
#include <type_traits>

#include "binary_view.hpp"

namespace tao::json
{
   enum class type : std::uint8_t
   {
      UNINITIALIZED,
      DISCARDED,
      DESTROYED,
      NULL_,
      BOOLEAN,
      SIGNED,
      UNSIGNED,
      DOUBLE,
      STRING,
      STRING_VIEW,
      BINARY,
      BINARY_VIEW,
      ARRAY,
      OBJECT,
      VALUE_PTR,
      OPAQUE_PTR
   };

   [[nodiscard]] constexpr bool needs_discard( const type t )
   {
      switch( t ) {
         case type::STRING:
         case type::BINARY:
         case type::ARRAY:
         case type::OBJECT:
            return true;
         case type::STRING_VIEW:
            return !std::is_trivially_destructible_v< std::string_view >;
         case type::BINARY_VIEW:
            return !std::is_trivially_destructible_v< tao::binary_view >;
         default:
            return false;
      }
   }

   constexpr std::string_view to_string( const type t )
   {
      switch( t ) {
         case type::UNINITIALIZED:
            return "uninitialized";
         case type::DISCARDED:
            return "discarded";
         case type::DESTROYED:
            return "destroyed";
         case type::NULL_:
            return "null";
         case type::BOOLEAN:
            return "boolean";
         case type::SIGNED:
            return "signed";
         case type::UNSIGNED:
            return "unsigned";
         case type::DOUBLE:
            return "double";
         case type::STRING:
            return "string";
         case type::STRING_VIEW:
            return "string_view";
         case type::BINARY:
            return "binary";
         case type::BINARY_VIEW:
            return "binary_view";
         case type::ARRAY:
            return "array";
         case type::OBJECT:
            return "object";
         case type::VALUE_PTR:
            return "value_ptr";
         case type::OPAQUE_PTR:
            return "opaque_ptr";
      }
      return "unknown";
   }

   struct null_t
   {
      explicit constexpr null_t( int /*unused*/ ) {}
   };

   struct empty_string_t
   {
      explicit constexpr empty_string_t( int /*unused*/ ) {}
   };

   struct empty_binary_t
   {
      explicit constexpr empty_binary_t( int /*unused*/ ) {}
   };

   struct empty_array_t
   {
      explicit constexpr empty_array_t( int /*unused*/ ) {}
   };

   struct empty_object_t
   {
      constexpr explicit empty_object_t( int /*unused*/ ) {}
   };

   struct uninitialized_t
   {
      constexpr explicit uninitialized_t( int /*unused*/ ) {}
   };

   constexpr null_t null{ 0 };

   constexpr empty_string_t empty_string{ 0 };
   constexpr empty_binary_t empty_binary{ 0 };
   constexpr empty_array_t empty_array{ 0 };
   constexpr empty_object_t empty_object{ 0 };

   constexpr uninitialized_t uninitialized{ 0 };

}  // namespace tao::json

#endif
