#include <iostream>

#include "Compiler.h"

int main(){
	try{
		Compiler::TranslitToString("Resource\\input.txt", "Resource\\SafeTransliterOutput.txt");
		Compiler::TranslitToNumber("Resource\\input.txt", "Resource\\TransliterOutput.txt");

		Compiler::GenerateTokens("Resource\\TransliterOutput.txt", "Resource\\SafeLexicalOutput.txt");
	}
	catch (std::exception& exp){
		std::cerr << exp.what() << std::endl;
	}

	return 0;
}