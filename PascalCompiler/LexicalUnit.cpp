#include "Compiler.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace Compiler;
using namespace Compiler::Transliter;
using namespace Compiler::LexicalUnit;
using namespace Compiler::LexicalUnit;

CLexicalUnit::CLexicalUnit() {
	_currentState = S1;
	_currentString = 1;
}

void CLexicalUnit::UpdateCurrentState(StateOfMachine state) {
	_currentState = state;
}

void CLexicalUnit::GenerateTokens(const char* input_file, const char* output_file){
	std::ifstream input(input_file);
	std::ofstream output(output_file);

	int numberOfClass, numberOfChar;

	while (input >> numberOfClass >> numberOfChar){
		switch (_currentState){
		case S1:
			switch (numberOfClass)
			{
			case letter:
				UpdateCurrentState(I1);
				UpdateCurrentWord(numberOfChar);
				break;
			case space:
				UpdateCurrentState(S1);
				break;
			case newline:
				std::endl(output);
				_currentString++;
				UpdateCurrentState(S1);
				break;
			default:
				LexicalException();
				
			}

			break;
		case I0:
			switch (numberOfClass)
			{
			case letter:
				UpdateCurrentState(I1);
				UpdateCurrentWord(numberOfChar);
				break;
			case space:
				UpdateCurrentState(I0);
				break;
			default:
				LexicalException();
			}
			break;
		case I1:
			switch (numberOfClass) {
			case number:
				UpdateCurrentState(I2);
				UpdateCurrentWord(numberOfChar);
				break;
			case semicolon:
				_currentClass = identifier;
				WriteMessage(output);

				UpdateCurrentWord(numberOfChar);
				_currentClass = endString;
				WriteMessage(output);

				UpdateCurrentState(S1);
				break;
			case space:
				UpdateCurrentState(I3);
				break;
			case colon:
				UpdateCurrentState(P1);
				UpdateCurrentWord(numberOfChar);
				break;
			default:
				LexicalException();
			}

			break;
		case I2:
			switch (numberOfClass) {
			case semicolon:
				_currentClass = identifier;
				WriteMessage(output);

				UpdateCurrentWord(numberOfChar);
				_currentClass = endString;
				WriteMessage(output);

				UpdateCurrentState(S1);
				break;
			case space:
				UpdateCurrentState(I3);
				break;
			case colon:
				UpdateCurrentState(P1);
				UpdateCurrentWord(numberOfChar);
				break;
			default:
				LexicalException();
			}

			break;
		case I3:
			switch (numberOfClass) {
			case semicolon:
				_currentClass = identifier;
				WriteMessage(output);

				UpdateCurrentWord(numberOfChar);
				_currentClass = endString;
				WriteMessage(output);

				UpdateCurrentState(S1);
				break;
			case space:
				UpdateCurrentState(I3);
				break;
			case colon:
				UpdateCurrentState(P1);
				UpdateCurrentWord(numberOfChar);
				break;
			default:
				LexicalException();
			}

			break;
		case P1:
			switch (numberOfClass) {
			case letter:
				_currentClass = label;
				WriteMessage(output);

				UpdateCurrentWord(numberOfChar);
				UpdateCurrentState(I1);
				break;
			case compare:
				if ((char)numberOfChar == '=') {
					UpdateCurrentWord(numberOfChar);
					_currentClass = assignment;
					WriteMessage(output);
					UpdateCurrentState(I0);
				}
				break;
			case space:
				_currentClass = label;
				WriteMessage(output);

				UpdateCurrentState(I0);
				break;
			default:
				LexicalException();
			}

			break;
		default:
			LexicalException();
		}
	}

	input.close();
	output.close();
}

void CLexicalUnit::WriteMessage(std::ostream& stream) {
	stream << TokenToString();
	_currentWord.clear();
}

std::string CLexicalUnit::TokenToString(){
	std::stringstream output; 

	output << "(" << LexicalClassToString(_currentClass) << ";\"" << _currentWord << "\")";

	return output.str();
}

std::string CLexicalUnit::LexicalClassToString(LexicalClass lexicalClass){
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
	case label:
		output = "LABEL";
		break;
	}

	return output;
}

void CLexicalUnit::LexicalException(){
	std::stringstream message;
	message << "Error : A token is not found : \"" << _currentWord << "\" in string " <<_currentString;
	std::string exception = message.str();

	throw std::exception(exception.c_str());
}

void CLexicalUnit::UpdateCurrentWord(int numberOfChar) {
	_currentWord += (char)numberOfChar;
}