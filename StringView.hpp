#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>


namespace StringViewNS {

	using String = std::string;
	using SizeType = String::size_type;
	using Char = String::value_type;

	class StringView {
		public:
			constexpr StringView()
				:	shared_string_( nullptr ),
					start_index_( 0 ),
					length_( 0 )
				#ifdef _DEBUG
					,DEBUG_string_( "" )
				#endif
			{}

			// StringView() = delete;

			explicit StringView( const std::shared_ptr<String>& shared_string );
			StringView(	const String& string,
						std::shared_ptr<String>& shared_string );

			String ToString() const; // TODO:: Add also stream operations.
		
			SizeType FindFrom( const String& string ) const;
		
			bool operator==( const StringView& other ) const;
		
			constexpr SizeType Length() const{
				return length_;
			}

		private:
			const String* shared_string_;
			SizeType start_index_;
			SizeType length_; // Without terminating character: '\0'.

		#ifdef _DEBUG
			const char* DEBUG_string_; // Only for debugging view.
		#endif
	};


	void RemoveCharacters( String& input, const String& characters );
	std::vector<String> SplitBy( const String& input, const String& separators );
	
	template <typename T>
	String ToString( T t ) {
		return std::to_string( t );
	}

	template <>
	inline String ToString<const Char*>( const Char* string ) {
		return String( string );
	}

	template <>
	inline String ToString<String>( String string ) {
		return string;
	}

};