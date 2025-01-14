// Copyright (c) 2015-2019 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#include "test.hpp"

#include <tao/json/type.hpp>

namespace tao::json
{
   void unit_test()
   {
      static_assert( sizeof( type ) == 1 );

      TEST_ASSERT( to_string( type::UNINITIALIZED ) == std::string( "uninitialized" ) );
      TEST_ASSERT( to_string( type::DISCARDED ) == std::string( "discarded" ) );
      TEST_ASSERT( to_string( type::DESTROYED ) == std::string( "destroyed" ) );

      TEST_ASSERT( to_string( type::NULL_ ) == std::string( "null" ) );
      TEST_ASSERT( to_string( type::BOOLEAN ) == std::string( "boolean" ) );
      TEST_ASSERT( to_string( type::SIGNED ) == std::string( "signed" ) );
      TEST_ASSERT( to_string( type::UNSIGNED ) == std::string( "unsigned" ) );
      TEST_ASSERT( to_string( type::DOUBLE ) == std::string( "double" ) );

      TEST_ASSERT( to_string( type::STRING ) == std::string( "string" ) );
      TEST_ASSERT( to_string( type::STRING_VIEW ) == std::string( "string_view" ) );
      TEST_ASSERT( to_string( type::BINARY ) == std::string( "binary" ) );
      TEST_ASSERT( to_string( type::BINARY_VIEW ) == std::string( "binary_view" ) );
      TEST_ASSERT( to_string( type::ARRAY ) == std::string( "array" ) );
      TEST_ASSERT( to_string( type::OBJECT ) == std::string( "object" ) );

      TEST_ASSERT( to_string( type::VALUE_PTR ) == std::string( "value_ptr" ) );
      TEST_ASSERT( to_string( type::OPAQUE_PTR ) == std::string( "opaque_ptr" ) );

      TEST_ASSERT( to_string( type( 42 ) ) == std::string( "unknown" ) );

      TEST_ASSERT( needs_discard( type::UNINITIALIZED ) == false );
      TEST_ASSERT( needs_discard( type::DISCARDED ) == false );
      TEST_ASSERT( needs_discard( type::DESTROYED ) == false );

      TEST_ASSERT( needs_discard( type::NULL_ ) == false );
      TEST_ASSERT( needs_discard( type::BOOLEAN ) == false );
      TEST_ASSERT( needs_discard( type::SIGNED ) == false );
      TEST_ASSERT( needs_discard( type::UNSIGNED ) == false );
      TEST_ASSERT( needs_discard( type::DOUBLE ) == false );

      TEST_ASSERT( needs_discard( type::STRING ) == true );
      TEST_ASSERT( needs_discard( type::STRING_VIEW ) == !std::is_trivially_destructible_v< std::string_view > );
      TEST_ASSERT( needs_discard( type::BINARY ) == true );
      TEST_ASSERT( needs_discard( type::BINARY_VIEW ) == !std::is_trivially_destructible_v< tao::binary_view > );
      TEST_ASSERT( needs_discard( type::ARRAY ) == true );
      TEST_ASSERT( needs_discard( type::OBJECT ) == true );

      TEST_ASSERT( needs_discard( type::VALUE_PTR ) == false );
      TEST_ASSERT( needs_discard( type::OPAQUE_PTR ) == false );
   }

}  // namespace tao::json

#include "main.hpp"
