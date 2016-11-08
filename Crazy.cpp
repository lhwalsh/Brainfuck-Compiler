// Kevin De La Torre and Luke Walsh
// Homework 3 - Crazy language compiler/interpreter
// Completed on: 2-9-2016

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

const int SIZE = 1000;
int tape[ SIZE ]; // Initialize tape array to 1000.
int *dp = tape; // Set data pointer at position 0 of tape array.
int position = 0;
int indent = 0;

void initializeArray(  )
{
	for ( int i = 0; i < SIZE; i++ )
	{
		tape[ i ] = 0;
	}
}

void printTape()
{
	// Index: 0 1 2 3 4 5 6 ...   <- Index
	// Ascii: /0 /0 /0 /0 /0 ...  <- Ascii Character
	// Value: 0 0 0 0 0 0 0 ...   <- Actual Value
	// 	  ^		      <- Current position of data pointer
	// >> 
	//
	// I want to make the tape look like this. 
	// Top row'll be the index of the array
	// Mid row'll correspond to whatever that value is in ascii
	// Bot row'll be the actual value of that array spot
	// We have to make it move with us too btw in like a range of 9-10
	// ( I'm thinking we do an odd number cause then we'll have an exact middle )
	// So like if we were to move the pointer to position 100 it should show the values
	// between 96 - 104 ( if we do it with 9 )
	//
	// Index: 96  97  98  99 100 101 102 103 104 105
	// Ascii:  `   a   b   c   d   e   f   g   h   i
	// Value:  0   0   0   0   0   0   0   0   0   0
	//                         ^
	// >>
	
	int startPos = position - 4;
	int endPos = position + 5;
	
	if ( position < 5 )
	{
	    startPos = 0;
	    endPos = 9;
	} else if ( position > 994 )
	{
	    startPos = 991;
	    endPos = 1000;
	}
	std::cout << "\nIndex: ";
	for ( int i = ( startPos ); i < ( endPos ); i++ )
	{
	    std::cout << std::setw( 4 ) << i;
	}
	std::cout << "\nAscii: ";
	for ( int i = ( startPos ); i < ( endPos ); i++ )
	{
	    if ( *(dp + i) < 33 )
	    {
		std::cout << std::setw( 4 ) << " ";
	    } else 
	    {
		std::cout << std::setw( 4 ) << static_cast<char>( *( dp + i ) );
	    }
	}
	std::cout << "\nValue: ";
	for ( int i = ( startPos ); i < ( endPos ); i++ )
	{
	    std::cout << std::setw( 4 ) << *( dp + i );
	}
	if ( position < 5 )
	{
	    std::cout << std::endl << std::setw( 11 + 4*position ) << "^";
	} else if ( position > 994 )
	{
	     std::cout << std::endl << std::setw( 27 + 4 * ( position % 995 ) ) << "^";
	} else
	{
	     std::cout << std::endl << std::setw( 27 ) << "^";
	}

	
}

void executeCommand( std::string command )
{
	// Possible Commands:
	// + = Increment value pointed at by dp.
	// - = Decrement value pointed at by dp.
	// > = Move position of dp to the right.
	// < = Move position of dp to the left.
	// : = Print out current value as an int.
	// . = Print out current value as a char.
	// { = If value pointed at by dp is 0, jump to location after closing bracket
	//     else move to next instruction.
	// } = Jump back to corresponding opening bracket.
	//
	if ( command != "exit" )
	{
		for ( int i = 0; i < command.length(); i++ )
		{
			switch ( command[ i ] )
			{
			    case '+':
				    if ( *dp < 127 ) // 127 is the last ascii char so that is our max
				    {
					++*( dp + position );
					break;
				    }
			    case '-':
				    if ( *dp >= 0 ) // 0 is minimum ascii character
				    {
					--*( dp + position);
					break;
				    }
			    case '>':
				    if ( position < SIZE ) // Don't want it moving past 999 
				    {
					position++;
				    }
				    break;
			    case '<':
				    if ( position > 0 ) // Don't want it moving below 0
				    {
					position--;
				    }
				    break;
			    case ':':
				    std::cout << *( dp + position ); // Print out int value
				    break;
			    case '.':
				    std::cout << static_cast<char>( *( dp + position ) ); // Print out char value
				    break;
			    case '{':
				    std::string newCom = "";
				    int brackStack = 1; // An extremely basic stack implementation
				    int closeBrackPosition = i + 1; // Initialize close position as one after opener
				    
				    for ( int j = (i+1); j < command.length(); j++ )
				    {
					if ( command[ j ] == '{' )
					{
					    brackStack++;
					} else if ( command[ j ] == '}' )
					{
					   if ( --brackStack == 0 )
					   {
					       closeBrackPosition = j;
					       break;
					   }
					}
				    }

				    if ( *( dp + position ) )
				    {
					for ( int j = ( i + 1 ); j < closeBrackPosition; j++ )
					{
					    newCom = newCom + command[ j ];
					}	

					while ( *( dp + position ) )
					{
					    executeCommand( newCom );
					}
				    }
				    i = closeBrackPosition;
				    break;
			}
		}
	}
}

void interpreterMode()
{
	std::string command = "";	

	while ( command != "exit" )
	{
	    printTape();
	    std::cout << "\n>> ";
	    std::cin >> command;
	    executeCommand( command );
	}
}

std::string setWidth()
{
    std::string spaces = "";
    for ( int i = 0; i < indent * 4; i++ )
    {
	spaces = spaces + " ";
    }
    return spaces;
}

void compileCommand( std::string command )
{
	for ( int i = 0; i < command.length(); i++ )
	{
	    switch ( command[ i ] )
	    {
		case '+':
		    std::cout << setWidth() << "++*dp;\n";
		    break;
		case '-':
		    std::cout << setWidth() << "--*dp;\n";
		    break;
		case '>':
		    std::cout << setWidth() << "dp++;\n";
		    break;
		case '<':
		    std::cout << setWidth() << "dp--;\n";
		    break;
		case ':':
		    std::cout << setWidth() << "std::cout << *dp;\n";
		    break;
		case '.':
		    std::cout << setWidth() << "std::cout << static_cast<char>(*dp);\n";
		    break;
		case '{':
		    std::cout << setWidth() << "while (*dp) {\n";
		    indent++;
		    break;
		case '}':
		    std::cout << setWidth() << "}\n";
		    indent--;
		    break;

	    }

	}
}

void crazyToCompiled( std::string file )
{
	// Take a crazy file and convert to cpp code and output via cout.

	std::ifstream fin( file.c_str() );
	std::string command = "";

	std::cout << "#include <iostream>\n\n";
	std::cout << "const int SIZE = 1000;";
	std::cout << "int tape[ SIZE ];\n";
	std::cout << "int *dp = tape;\n\n";

	std::cout << "int main()\n{\n";
	indent++;
	
	while ( fin >> command )
	{
	    compileCommand( command );
	}

	indent--;
	std::cout << "}\n";

}

void fileToCrazy( std::string file )
{
	std::ifstream fin ( file.c_str() );
	std::string command = "";
	std::string totalCommand = "";

	while ( fin  >> command )
	{
	    totalCommand = totalCommand + command;
	}
	executeCommand( totalCommand );
}

void printHelp( std::string file )
{
	std::cout << "Usage: " + file + " <argument> <file>" << std::endl;
	std::cout << "Arguments:" << std::endl;
	std::cout << "    <> - If no argument, program will run in interpreter mode." << std::endl;
	std::cout << "    -c - Reads file and converts from Crazy file to c++ file." << std::endl;
	std::cout << "    -e - Reads file and executes as Crazy program." << std::endl;

}

int main( int argc, char *argv[] )
{
	initializeArray();

	if ( argc == 1 )
	{
		interpreterMode();

	} else if ( argc == 3 ) // If it's 3 that means it should have 
	{
		std::string argument = argv[ 1 ];
		std::string file = argv[ 2 ];

		if ( argument == "-c" )
		{
			// Read contents of file, copmile to c++, output via cout
			crazyToCompiled( file );

		} else if ( argument == "-e" )
		{
			// read contents of file as crazy program and execute
			
			fileToCrazy( file );

		} else
		{
			printHelp( file );
		}
	} else
	{
		std::string temp = argv[ 0 ];
		printHelp( temp );
	}
	return 0;
}
