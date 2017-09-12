#include "JsonParser.hpp"


namespace JsonV2 {

	// using namespace StringViewNS;

	JsonObject::JsonObject(	const String& shared_string )
						:	shared_string_( std::make_shared<String>( shared_string ) ),
							value_( shared_string_ ),
							is_list_( false ),
							children_()
	{}

	JsonObject::JsonObject(	std::shared_ptr<String>& shared_string )
						:	shared_string_( shared_string ),
							value_( shared_string_ ),
							is_list_( false ),
							children_()
	{}


	JsonObject& JsonObject::LoadFromString( String input ) {
		StringViewNS::RemoveCharacters( input, " \t\n" ); // \"
		const std::vector<String> strings = StringViewNS::SplitBy( input, "{}:,[]" );
		CreateHierarchy( strings );
		return *this;
	}


	SizeType JsonObject::CreateHierarchy(	const std::vector<String>& strings,
											SizeType start_position )
	{
		for ( SizeType i=start_position; i<strings.size(); ++i ) {
			auto current = strings[i]; // Only for debugging.

			if ( strings[i] == "{" || strings[i] == "[" ) { // "{"
				auto& child = NewChild();
				if ( strings[i] == "[" ) {
					child.is_list_ = true;
				}
				i = child.CreateHierarchy( strings, i+1 );
			}
			else if ( strings[i] == "}" || strings[i] == "]" ) { // "]"
				return i+1;
			}
			else if ( strings[i+1] == "}" || strings[i+1] == "]" ) { // "A}"
				NewChild()[ strings[i] ];
				return i+2;
			}
			else if ( strings[i+1] == ":" &&
					( strings[i+2] == "{" || strings[i+2] == "[" ) ) // "X:{"
			{
				auto& child = NewChild();
				child[ strings[i] ];

				auto& childs_child = child.NewChild();

				if ( strings[i+2] == "[" ) {
					childs_child.is_list_ = true;
				}
				i = childs_child.CreateHierarchy( strings, i+3 );
			}
			else if ( strings[i+1] == ":" &&
					( strings[i+3] == "}" || strings[i+3] == "]" ) ) // "A:B}"
			{
				NewChild()[ strings[i] ] = strings[i+2];
				return i+4;
			}
			else if ( strings[i+1] == ":" && strings[i+3] == "," ) { // "A:B,"
				NewChild()[ strings[i] ] = strings[i+2];
				i=i+3;
			}
			else if ( strings[i+1] == "," ) { // "A,"
				NewChild()[ strings[i] ];
				i=i+1;
			}
			else { // Only for debugging.
				auto wut = strings[i]; // Only for debugging.
				return i;
			}
		}
		return strings.size();
	}

	JsonObject& JsonObject::NewChild() {
		children_.emplace_back( shared_string_ );
		return children_.back();
	}

	JsonObject& JsonObject::operator[]( const String& value ) {
		if ( value.empty() ) throw;
		value_ = StringView( value, shared_string_ );
		return *this;
	}


	const JsonObject* JsonObject::FindByValue( const StringView value_view ) const {
		if ( value_view == value_ ) return this;
		for ( const auto& child : children_ ) {
			if ( const JsonObject* it = child.FindByValue( value_view ) ) {
				return it;
			}
		}
		return nullptr;
	}
	JsonObject* JsonObject::FindByValue( const StringView value_view ) {
		if ( value_view == value_ ) return this;
		for ( auto& child : children_ ) {
			if ( JsonObject* it = child.FindByValue( value_view ) ) {
				return it;
			}
		}
		return nullptr;
	}

	String JsonObject::ChildrenToString() const {
		String str;
		const auto last_index = children_.size() - 1;
		for ( int i=0; i<last_index; ++i ) {
			str += children_[i].ToString() + ",";
		}
		str += children_[ last_index ].ToString();
		return str;
	}

	String JsonObject::ToString() const {
		String str( value_.ToString() );

		if ( children_.empty() ) return str;
	
		if ( value_.Length() > 0 ) {
			str += ":";
		}
	
		const bool is_list = is_list_;
		if ( is_list ) {
			str += "[";
		}
		else {
			bool only_one_child = ( children_.size() == 1 );
			for ( const auto& c : children_ ) {
				if ( c.children_.size() > 1 ) {
					only_one_child = false;
					break;
				}
			}
			if ( only_one_child ) {
			}
			else {
				str += "{";
			}
		}

		str += ChildrenToString();

		if ( is_list ) {
			str += "]";
		}
		else {
			bool only_one_child = ( children_.size() == 1 );
			for ( const auto& c : children_ ) {
				if ( c.children_.size() > 1 ) {
					only_one_child = false;
					break;
				}
			}
			if ( only_one_child ) {
			}
			else {
				str += "}";
			}
		}

		return str;
	}

	String JsonObject::DEBUG_PrintSharedString() const {
		return "DebugPrint:\n'" + ( *shared_string_ ) + "'\n";
	}

	/*const JsonObject* Find( const JsonObject& object, const String& key ) {
		if ( *object.key_ == key ) return &object;
		for ( const auto& child : object.children_ ) {
			if ( const JsonObject* it = Find( child, key ) ) return it;
		}
		return nullptr;
	}*/


};