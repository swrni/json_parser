#include "StringView.hpp"

#include <algorithm>


namespace StringViewNS {

	void RemoveCharacters(	String& input,
							const String& characters )
	{
		const auto remove_condition = [ &characters ]( const char c )
		{
			for ( const auto& character : characters ) {
				if ( character == c ) return true;
			}
			return false;
		};

		input.erase(
			std::remove_if(
				std::begin( input ),
				std::end( input ),
				remove_condition
			),
			std::end( input )
		);
	}

	std::vector<String> SplitBy(	const String& input,
									const String& separators )
	{
		std::vector<String> strings;

		int start = 0;
		for ( int i=0; i<input.length(); ++i ) {
			for ( const auto& condition : separators ) {
				if ( input[i] != condition ) continue;
				const int count = i - ( start + 1 );
				if ( count > 0 ) {
					String item;
					if ( start == 0 && input[0] != '{' ) {
						item = input.substr( start, count+1 );
					}
					else {
						item = input.substr( start+1, count );
					}
					strings.push_back( item );
				}
				const auto separator = input.substr( i, 1 );
				strings.push_back( separator );
				start = i;
			}
		}
		return strings;
	}


	StringView::StringView( const std::shared_ptr<String>& shared_string )
		:	shared_string_( shared_string.get() ), start_index_( 0 ), length_( 0 )
		#ifdef _DEBUG
			,DEBUG_string_( "" )
		#endif
	{}

	StringView::StringView( const String& string, std::shared_ptr<String>& shared_string )
		:	shared_string_( shared_string.get() ), start_index_( 0 ), length_( 0 )
		#ifdef _DEBUG
			,DEBUG_string_( "" )
		#endif
	{
		const SizeType found_index = FindFrom( string );
		if ( found_index == String::npos ) {
			start_index_ = shared_string->length();
			shared_string->append( string );
		}
		else {
			start_index_ = found_index;
		}

		length_ = string.length();
	
		#ifdef _DEBUG
			const String temp = ToString();
			DEBUG_string_ = temp.c_str();
			// std::cout << '\n' << DEBUG_string_ << '\n';
		#endif
	}


	String StringView::ToString() const {
		if ( !shared_string_ || shared_string_->empty() || length_ == 0 ) return "";
		String str;
		for ( int i=0; i<length_; ++i ) {
			str += ( *shared_string_ )[ start_index_ + i ];
		}
		return str;
	}

	SizeType StringView::FindFrom( const String& string ) const {
		if ( !shared_string_ ) throw;
		return shared_string_->find( string, 0 );
	}

	bool StringView::operator==( const StringView& other ) const {
		if ( length_ != other.length_ ) return false;
		if ( !shared_string_ || !other.shared_string_ ) return false;
		for ( int i=0; i<length_; ++i ) {
			if ( ( *shared_string_ )[i] != ( *other.shared_string_ )[i] ) {
				return false;
			}
		}
		return true;
	}

};