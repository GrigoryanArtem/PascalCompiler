#include "Compiler.h"

void Compiler::GenerateTokens(const char* input_file, const char* output_file) {
	Compiler::LexicalUnit::CLexicalUnit clu;

	clu.GenerateTokens(input_file, output_file);
}