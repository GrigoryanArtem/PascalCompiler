#include <iostream>

#include "Compiler.h"

int main(){
	Compiler::TranslitToString("Resource\\input.txt", "Resource\\SafeTransliterOutput.txt");
	Compiler::TranslitToNumber("Resource\\input.txt", "Resource\\TransliterOutput.txt");

	return 0;
}