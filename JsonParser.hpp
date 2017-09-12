#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "StringView.hpp"


namespace JsonV2 {

	using namespace StringViewNS;

	class JsonObject {
		public:
			JsonObject( const JsonObject& ) = delete;

			explicit JsonObject( JsonObject&& ) = default;
			explicit JsonObject( const String& shared_string = String("") );
			explicit JsonObject( std::shared_ptr<String>& shared_string );
		
			JsonObject& LoadFromString( String input );

			SizeType CreateHierarchy(	const std::vector<String>& strings,
										SizeType start_position = 0 );

			JsonObject& NewChild();

			template <typename T>
			void AppendAsNewChild( T&& t ) {
				const auto string_value = StringViewNS::ToString(
					std::forward<T>( t )
				);
				NewChild()[ string_value ];
			}

			template <typename T, typename ...Args>
			void AppendAsNewChild( T&& t, Args&&... args ) {
				AppendAsNewChild(
					std::forward<T>( t )
				);
				AppendAsNewChild(
					std::forward<Args>( args )...
				);
			}
		
			template <typename T>
			void operator=( const T& value ) {
				children_.clear();
				AppendAsNewChild(
					StringViewNS::ToString( value )
				);
			}

			template <typename T>
			void operator=( const std::vector<T>& values ) {
				children_.clear();
				for ( const auto& value : values ) {
					AppendAsNewChild(
						StringViewNS::ToString( value )
					);
				}
			}

			JsonObject& operator[]( const String& value );
		
			String ChildrenToString() const;
			String ToString() const;
		
			String DEBUG_PrintSharedString() const;

		private:
			const JsonObject* FindByValue( const StringView value_view ) const;
			JsonObject* FindByValue( const StringView value_view );
		
			std::shared_ptr<String> shared_string_;

			StringView value_;
			bool is_list_;
			std::vector<JsonObject> children_;
	};

	// const JsonObject* Find( const JsonObject& object, const String& key );

};