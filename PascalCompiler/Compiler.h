#pragma once

#ifndef COMPILER_H
#define COMPILER_H

#include <string>
#include <map>

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
			// label - label in programm, big letter or big letter and number and colon

			identifier,
			assignment,
			label,
			endString
		};

		enum StateOfMachine{
			// S1 - new string
			// I1 - ID with the single letter,  for example "D"
			// I2 - ID with the single letter and single number,  for example "D7" 

			S1,
			I0,
			I1,
			I2,
			I3,
			P1
		};

		class CLexicalUnit {
		public:
			CLexicalUnit();

			void GenerateTokens(const char* input_file, const char* output_file, const char* id_table, const char* label_table);
		private:
			int _currentString;
			int _lastIdNumber;

			std::string _currentWord;
			LexicalClass _currentClass;
			std::map<std::string, int> _idTable;
			std::map<std::string, int> _labelTable;
			StateOfMachine _currentState;

			std::string LexicalClassToString(LexicalClass lexicalClass);
			std::string TokenToString();
			void LexicalException();
			void UpdateCurrentWord(int numberOfChar);
			void UpdateCurrentState(StateOfMachine state);
			void WriteMessage(std::ostream& stream);
			void PutToIdTable(std::string id);
			void PutToLabelTable(std::string label);
			void PrintTables(const char* id_table, const char* label_table);
		};
	}

	void GenerateTokens(const char* input_file, const char* output_file, const char* id_table, const char* label_table);
	void TranslitToNumber(const char* input_file, const char* output_file);
	void TranslitToString(const char* input_file, const char* output_file);
}

#endif