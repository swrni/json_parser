#include <iostream>
#include <string>

#include "JsonParser.hpp"


using namespace JsonV2;


void Example1();
void Example2();
void Example3();


int main() {
	Example1();
	// Example2();
	// Example3();

	system( "pause" );
	return 0;
}


void Example1() {
	JsonObject o;
	o.NewChild()[ "event_type" ] = "'event01'";
	o.NewChild()[ "id" ] = 12345;
	o.NewChild()[ "position" ] = std::vector<float>{ 3.0f, -2.5f, 5.3f };
	o.NewChild()[ "orientation" ] = std::vector<float>{ 1.100f, 2.1f, 3.3f };

	const std::string output = o.ToString();
	std::cout << output << "\n\n";
}

void Example2() {
	JsonObject o;
	const std::string example =
		"{ \
			id: X998, \
			from:{ \
				name: Peyton, \
				id: X18 \
			}, \
			actions: [ \
				{ \
					name: Comment, \
					link: facebook1 \
				}, \
				{ \
					name: Like, \
					link: facebook2 \
				} \
			], \
			updated_time: 2010 \
		}";
		
	// Create JsonObject from the string.
	o.LoadFromString( example );

	// Print the hierarchy.
	std::cout << o.ToString() << "\n\n";

	// Append two new items.
	o.NewChild()[ "ASDF" ];
	o.NewChild()[ "0ASD" ];

	// Print the modified hierarchy.
	std::cout << o.ToString() << "\n\n";

	// Print the shared string.
	std::cout << o.DEBUG_PrintSharedString();
}

void Example3() {
	const std::string test_string =
		"{ [a,b], Duck:12, Ankka:{kvak1:13}, kvak2:14, kvak3:[15,16] }";

	std::cout << test_string << "\n\n";

	JsonObject o;
	o.LoadFromString( test_string );
	o.NewChild()[ "test_var" ].AppendAsNewChild( 1.100f, 2.1, 3 );

	std::cout << o.ToString() << "\n\n";
}