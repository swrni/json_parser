#include <iostream>
#include <string>

#include "JsonParser.hpp"


using namespace JsonV2;


void Test1();
void Test2();
void Test3();


int main( int argc, char* argv[] ) {
	Test1();
	// Test2();
	// Test3();

	system( "pause" );
	return 0;
}


void Test1() {
	JsonObject o;
	o.NewChild()[ "event_type" ] = "'event01'";
	o.NewChild()[ "id" ] = 12345;
	o.NewChild()[ "position" ] = std::vector<float>{ 3.0f, -2.5f, 5.3f };
	o.NewChild()[ "orientation" ] = std::vector<float>{ 1.100f, 2.1f, 3.3f };

	const std::string output = o.ToString();
	std::cout << output << "\n\n";
}

void Test2() {
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
		
		
	// std::cout << example << "\n\n";
	o.LoadFromString( example );

	std::cout << o.ToString() << "\n\n";
	// std::cout << '\n' << '\n';

	o.NewChild()[ "ASDF" ];
	o.NewChild()[ "0ASD" ];

	std::cout << o.ToString() << "\n\n";

	std::cout << o.DEBUG_PrintSharedString();
}

void Test3() {
	// std::string test_string = "{ \"Ankka\":{\"kvak\":13}, \"kvak\":14, \"kvak\":[13,14] }";
	const std::string test_string =
		"{ [a,b], Duck:12, Ankka:{kvak1:13}, kvak2:14, kvak3:[15,16] }";

	std::cout << test_string << "\n\n";

	JsonObject o;
	o.LoadFromString( test_string );
	o.NewChild()[ "test_var" ].AppendAsNewChild( 1.100f, 2.1, 3 );

	std::cout << o.ToString() << "\n\n";
}