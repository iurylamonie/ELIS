#include <iostream>
#include <string>
#include <iterator>

#include "hashtbl.h"
#include "elis.h"

int main()
{
	elis editor_texto;
	std::cout << "---> INSERINDO PRIMEIRA LINHA..." << std::endl;
	editor_texto.insert(1,"Primeira linha.");
	std::cout << "Quantidade de linhas na memoria: " << editor_texto.size() << std::endl;
	std::cout << "---> USANDO UNDO..." << std::endl;
	editor_texto.undo();
	std::cout << "Quantidade de linhas na memoria: " << editor_texto.size() << std::endl;

	return 0;
}