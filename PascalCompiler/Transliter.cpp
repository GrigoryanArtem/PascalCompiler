#include <fstream>
#include <sstream>
#include <string>

#include "Compiler.h"

using namespace Compiler;
using namespace Compiler::Transliter;

void Transliter::Translit(const char* input_file, const char* output_file, std::string func(char)){
	std::ifstream input(input_file);
	std::ofstream output(output_file);
	char curr(0), prev(0);

	while ((curr = input.get()) != EOF){
		if (curr == '\t')
			curr = ' ';

		if (!(curr == prev && curr == ' '))
			output << func(curr);

		prev = curr;
	}

	input.close();
	output.close();
}

SymbolClass Transliter::GetSymbolClass(char symbol){
	if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z'))
		return letter;

	if (symbol >= '0' && symbol <= '9')
		return number;

	if (symbol == ';')
		return semicolon;

	if (symbol == '.')
		return dot;

	if (symbol == ' ')
		return space;

	if (symbol == '-' || symbol == '+' || symbol == '*' || symbol == '/' || symbol == '=')
		return arithmetic;

	if (symbol == ':')
		return colon;

	if (symbol == '(')
		return lbracket;

	if (symbol == ')')
		return rbracket;

	if (symbol == '\'')
		return quote;

	if (symbol == '\n')
		return newline;

	return other;
}

std::string Transliter::GetSymbolString(char symbol){
	std::stringstream output;

	switch (GetSymbolClass(symbol))
	{
	case letter:
		output << "(LETTER;\'" << symbol << "\')";
		break;
	case number:
		output << "(NUMBER;\'" << symbol << "\')";
		break;
	case semicolon:
		output << "(SEMICOLON;\'" << symbol << "\')";
		break;
	case dot:
		output << "(DOT;\'" << symbol << "\')";
		break;
	case space:
		output << "(SPACE;\'" << symbol << "\')";
		break;
	case arithmetic:
		output << "(ARITHMETIC;\'" << symbol << "\')";
		break;
	case colon:
		output << "(COLON;\'" << symbol << "\')";
		break;
	case lbracket:
		output << "(LBRACKET;\'" << symbol << "\')";
		break;
	case rbracket:
		output << "(RBRACKET;\'" << symbol << "\')";
		break;
	case newline:
		output << "(NEWLINE;'\\n')" << std::endl;
		break;
	case quote:
		output << "(QUOTE;\'" << symbol << "\')";
		break;
	case other:
		output << "(OTHER;\'" << symbol << "\')";
		break;
	}

	return output.str();
}

std::string Transliter::GetSymbolNumberString(char symbol){
	std::stringstream output;

	output << (int)GetSymbolClass(symbol) << ' ' << (int)symbol << (symbol == '\n' ? '\n' : ' ');

	return output.str();
}

void Compiler::TranslitToString(const char* input_file, const char* output_file){
	Transliter::Translit(input_file, output_file, Transliter::GetSymbolString);
}

void Compiler::TranslitToNumber(const char* input_file, const char* output_file){
	Transliter::Translit(input_file, output_file, Transliter::GetSymbolNumberString);
}