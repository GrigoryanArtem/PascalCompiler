#pragma once

#ifndef COMPILER_H
#define COMPILER_H

#include <string>

namespace Compiler{
	namespace Transliter{
		enum SymbolClass{
			// letter - character set {a - z, A - Z}
			// number - character set {1 - 9}
			// arithmetic - set of arithmetic symbols {+, -, *, /}
			// compare - ñomparative set of characters {<, >, =}
			// dot - character "."
			// semicolon - character ";"
			// space - character " "
			// quote - character "'"
			// colon - character ":"
			// lbracket - character "("
			// rbracket - character ")"
			// newline - line break symbol, for example "\n"
			// other - set of other symbols

			letter,		
			number,
			arithmetic,
			compare,
			dot,
			semicolon,
			space,
			quote,
			colon,
			lbracket,
			rbracket,
			newline,
			other
		};

		SymbolClass GetSymbolClass(char symbol);
		std::string GetSymbolString(char symbol);
		std::string GetSymbolNumberString(char symbol);
		void Translit(const char* input_file, const char* output_file, std::string func(char));
	}

	namespace LexicalUnit{
		enum LexicalClass{
			// identifier - identifier big letter or big letter and number
			// assignment - assignment operation ":="

			identifier,
			assignment
		};

		enum StateOfMachine{
			// S1 - new string
			// I1 - ID with the single letter,  for example "D"
			// I2 - ID with the single letter and single number,  for example "D7" 

			S1,
			I1,
			I2,
			I3,
			A1,
		};

		std::string LixicalClassToString(LexicalClass lexicalClass);
		std::string TokenToString(LexicalClass lexicalClass, const std::string& word);
		void GenerateTokens(const char* input_file, const char* output_file);
		void LexicalException(const std::string& word);
	}

	void TranslitToString(const char* input_file, const char* output_file);
	void TranslitToNumber(const char* input_file, const char* output_file);
}

#endif