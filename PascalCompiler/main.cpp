#include <iostream>

#include "Compiler.h"

int main(){
	Compiler::TranslitToString("input.txt", "SafeTransliterOutput.txt");
	Compiler::TranslitToNumber("input.txt", "TransliterOutput.txt");

	return 0;
}