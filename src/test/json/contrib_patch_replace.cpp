// Copyright (c) 2016-2022 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#include "test.hpp"

#include <tao/json/value.hpp>

#include <tao/json/contrib/patch.hpp>

namespace tao::json
{
   [[nodiscard]] value cpatch( const value& v, const value& patch )
   {
      return json::patch( v, patch );
   }

   void unit_test()
   {
      const value n = null;
      const value one = 1U;
      const value two = 2;
      const value ea = empty_array;
      const value eo = empty_object;

      const value a = { { "a", { { "foo", one } } } };
      const value b = { { "b", value::array( { one, two, 3, 4 } ) } };

      const value q = { { "q", { { "bar", two } } } };

      TEST_ASSERT( patch( n, ea ) == n );
      TEST_ASSERT( patch( ea, ea ) == ea );
      TEST_ASSERT( patch( eo, ea ) == eo );
      TEST_ASSERT( patch( a, ea ) == a );
      TEST_ASSERT( patch( b, ea ) == b );
      TEST_ASSERT( patch( q, ea ) == q );

      TEST_THROWS( patch( n, value::array( { { { "op", "foo" }, { "path", "" } } } ) ) );

      TEST_ASSERT( patch( a, value::array( { { { "op", "replace" }, { "path", "" }, { "value", 42 } } } ) ) == 42 );
      TEST_ASSERT( patch( a, value::array( { { { "op", "replace" }, { "path", "/a" }, { "value", 42 } } } ) ) == value( { { "a", 42 } } ) );
      TEST_ASSERT( patch( a, value::array( { { { "op", "replace" }, { "path", "/a/foo" }, { "value", 42 } } } ) ) == value( { { "a", { { "foo", 42 } } } } ) );
      TEST_THROWS( patch( a, value::array( { { { "op", "replace" }, { "path", "/b" }, { "value", 42 } } } ) ) );
      TEST_THROWS( patch( a, value::array( { { { "op", "replace" }, { "path", "/a/b" }, { "value", 42 } } } ) ) );
      TEST_ASSERT( patch( b, value::array( { { { "op", "replace" }, { "path", "/b/0" }, { "value", 42 } } } ) ) == value( { { "b", value::array( { 42, 2, 3, 4 } ) } } ) );
      TEST_ASSERT( patch( b, value::array( { { { "op", "replace" }, { "path", "/b/1" }, { "value", 42 } } } ) ) == value( { { "b", value::array( { 1, 42, 3, 4 } ) } } ) );
      TEST_ASSERT( patch( b, value::array( { { { "op", "replace" }, { "path", "/b/2" }, { "value", 42 } } } ) ) == value( { { "b", value::array( { 1, 2, 42, 4 } ) } } ) );
      TEST_ASSERT( patch( b, value::array( { { { "op", "replace" }, { "path", "/b/3" }, { "value", 42 } } } ) ) == value( { { "b", value::array( { 1, 2, 3, 42 } ) } } ) );
      TEST_THROWS( patch( b, value::array( { { { "op", "replace" }, { "path", "/b/4" }, { "value", 42 } } } ) ) );
      TEST_THROWS( patch( b, value::array( { { { "op", "replace" }, { "path", "/b/-" }, { "value", 42 } } } ) ) );
      TEST_THROWS( patch( b, value::array( { { { "op", "replace" }, { "path", "/b/a" }, { "value", 42 } } } ) ) );
      TEST_THROWS( patch( q, value::array( { { { "op", "replace" }, { "path", "/a/foo" }, { "value", 42 } } } ) ) );

      TEST_ASSERT( cpatch( n, ea ) == n );
      TEST_ASSERT( cpatch( ea, ea ) == ea );
      TEST_ASSERT( cpatch( eo, ea ) == eo );
      TEST_ASSERT( cpatch( a, ea ) == a );
      TEST_ASSERT( cpatch( b, ea ) == b );
      TEST_ASSERT( cpatch( q, ea ) == q );

      TEST_THROWS( cpatch( n, value::array( { { { "op", "foo" }, { "path", "" } } } ) ) );

      TEST_ASSERT( cpatch( a, value::array( { { { "op", "replace" }, { "path", "" }, { "value", 42 } } } ) ) == 42 );
      TEST_ASSERT( cpatch( a, value::array( { { { "op", "replace" }, { "path", "/a" }, { "value", 42 } } } ) ) == value( { { "a", 42 } } ) );
      TEST_ASSERT( cpatch( a, value::array( { { { "op", "replace" }, { "path", "/a/foo" }, { "value", 42 } } } ) ) == value( { { "a", { { "foo", 42 } } } } ) );
      TEST_THROWS( cpatch( a, value::array( { { { "op", "replace" }, { "path", "/b" }, { "value", 42 } } } ) ) );
      TEST_THROWS( cpatch( a, value::array( { { { "op", "replace" }, { "path", "/a/b" }, { "value", 42 } } } ) ) );
      TEST_ASSERT( cpatch( b, value::array( { { { "op", "replace" }, { "path", "/b/0" }, { "value", 42 } } } ) ) == value( { { "b", value::array( { 42, 2, 3, 4 } ) } } ) );
      TEST_ASSERT( cpatch( b, value::array( { { { "op", "replace" }, { "path", "/b/1" }, { "value", 42 } } } ) ) == value( { { "b", value::array( { 1, 42, 3, 4 } ) } } ) );
      TEST_ASSERT( cpatch( b, value::array( { { { "op", "replace" }, { "path", "/b/2" }, { "value", 42 } } } ) ) == value( { { "b", value::array( { 1, 2, 42, 4 } ) } } ) );
      TEST_ASSERT( cpatch( b, value::array( { { { "op", "replace" }, { "path", "/b/3" }, { "value", 42 } } } ) ) == value( { { "b", value::array( { 1, 2, 3, 42 } ) } } ) );
      TEST_THROWS( cpatch( b, value::array( { { { "op", "replace" }, { "path", "/b/4" }, { "value", 42 } } } ) ) );
      TEST_THROWS( cpatch( b, value::array( { { { "op", "replace" }, { "path", "/b/-" }, { "value", 42 } } } ) ) );
      TEST_THROWS( cpatch( b, value::array( { { { "op", "replace" }, { "path", "/b/a" }, { "value", 42 } } } ) ) );
      TEST_THROWS( cpatch( q, value::array( { { { "op", "replace" }, { "path", "/a/foo" }, { "value", 42 } } } ) ) );
   }

}  // namespace tao::json

#include "main.hpp"
