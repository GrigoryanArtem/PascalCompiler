#include "Compiler.h"

void Compiler::GenerateTokens(const char* input_file, const char* output_file, const char* id_table, const char* label_table) {
	Compiler::LexicalUnit::CLexicalUnit clu;

	clu.GenerateTokens(input_file, output_file, id_table, label_table);
}