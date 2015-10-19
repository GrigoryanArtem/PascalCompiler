#pragma once

#ifndef COMPILER_H
#define COMPILER_H

#include <string>

namespace Compiler{
	namespace Transliter{
		enum SymbolClass{
			letter,
			number,
			semicolon,
			colon,
			dot,
			space,
			arithmetic,
			lbracket,
			rbracket,
			compare,
			quote,
			newline,
			other
		};

		SymbolClass GetSymbolClass(char symbol);
		std::string GetSymbolString(char symbol);
		std::string GetSymbolNumberString(char symbol);
		void Translit(const char* input_file, const char* output_file, std::string func(char));
	}

	namespace LexicalUnit{
		enum LixicalClass{

		};

		void GenerateTokens(const char* input_file, const char* output_file);
	}

	void TranslitToString(const char* input_file, const char* output_file);
	void TranslitToNumber(const char* input_file, const char* output_file);
}

#endif