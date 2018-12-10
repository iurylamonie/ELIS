#include <iostream>
#include <string>

#include "hashtbl.h"

int main()
{
	
	ac::HashTbl<int, std::string> hash_data;
	// Verificando quantidade de elementos
	// e a capacidade do hash.
	std::cout << "Quantidade de elementos no hash: " << hash_data.size() << std::endl;
	std::cout << "Capacidade máxima atual do hash: " << hash_data.tam() << std::endl;

	// Inserindo as primeiras linhas
	hash_data.insert(1, "Primeira linha");
	hash_data.insert(2, " Segunda linha");
	hash_data.insert(3, "Terceira linah com quebra de texto\n");
	
	// Verificando quantidade de elementos
	// e a capacidade do hash.
	std::cout << "Quantidade de elementos no hash: " << hash_data.size() << std::endl;
	std::cout << "Capacidade máxima atual do hash: " << hash_data.tam() << std::endl;

	// Imprimindo hash;
	std::cout << hash_data << std::endl;
	return 0;
}