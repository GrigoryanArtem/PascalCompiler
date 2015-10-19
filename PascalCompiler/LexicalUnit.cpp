#include "Compiler.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace Compiler;
using namespace Compiler::Transliter;
using namespace Compiler::LexicalUnit;

void LexicalUnit::GenerateTokens(const char* input_file, const char* output_file){
	std::string currentWord;

	std::ifstream input(input_file);
	std::ofstream output(output_file);

	int numberOfClass, numberOfChar;
	StateOfMachine state = S1;

	while (input >> numberOfClass >> numberOfChar){
		switch (state){
		case S1:

			switch (numberOfClass){
			case letter:
				state = I1;
				currentWord += (char)numberOfChar;
				break;
			case space:
				state = S1;
				break;
			case newline:
				state = S1;
				output << std::endl;
				break;
			default:
				LexicalException(currentWord);
			}
	
			break;
		case I1:

			switch (numberOfClass)
			{
			case number:
				state = I2;
				currentWord += (char)numberOfChar;
				break;
			case semicolon:
				state = S1;

				output << TokenToString(identifier, currentWord);
				currentWord.clear();

				currentWord += ";";
				output << TokenToString(endString, currentWord);
				currentWord.clear();
				break;
			case space:
				state = I3;

				output << TokenToString(identifier, currentWord);
				currentWord.clear();
				break;
			case colon:
				state = A1;

				output << TokenToString(identifier, currentWord);
				currentWord.clear();

				currentWord += (char)numberOfChar;
				break;
			default:
				LexicalException(currentWord);
			}

			break;
		case I2:

			switch (numberOfClass)
			{
			case space:
				output << TokenToString(identifier, currentWord);
				currentWord.clear();
				state = I3;
				break;
			case semicolon:
				state = S1;

				output << TokenToString(identifier, currentWord);
				currentWord.clear();

				currentWord += ";";
				output << TokenToString(endString, currentWord);
				currentWord.clear();
			case colon:
				output << TokenToString(identifier, currentWord);
				currentWord.clear();
				currentWord += (char)numberOfChar;
				state = A1;
				break;
			default:
				LexicalException(currentWord);
			}

			break;

		case I3:

			switch (numberOfClass)
			{
			case colon:
				currentWord += (char)numberOfChar;
				state = A1;
				break;
			default:
				LexicalException(currentWord);
			}

			break;

		case A1:

			switch (numberOfClass)
			{
			case compare:
				state = A2;
				currentWord += (char)numberOfChar;
				output << TokenToString(assignment, currentWord);
				currentWord.clear();
				break;
			default:
				LexicalException(currentWord);
			}

			break;
		case A2:

			switch (numberOfClass)
			{
			case letter:
				currentWord += (char)numberOfChar;
				state = I1;
				break;
			case space:
				state = A2;
				break;
			default:
				LexicalException(currentWord);
			}

			break;
		default:
			LexicalException(currentWord);
		}
	}

	input.close();
	output.close();
}

std::string LexicalUnit::TokenToString(LexicalClass lexicalClass, const std::string& word){
	std::stringstream output; 

	output << "(" << LixicalClassToString(lexicalClass) << ";\"" << word << "\")";

	return output.str();
}

std::string LexicalUnit::LixicalClassToString(LexicalClass lexicalClass){
	std::string output;
	
	switch (lexicalClass)
	{
	case identifier:
		output = "IDENTIFIER";
		break;
	case assignment:
		output = "ASSIGNMENT";
		break;
	case endString:
		output = "END STRING";
		break;
	}

	return output;
}

void LexicalUnit::LexicalException(const std::string& word){
	std::string exception = "Error : A token is not found : \"" + word + '\"';

	throw std::exception(exception.c_str());
}