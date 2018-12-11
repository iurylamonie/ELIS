#include <iostream>
#include <string>
#include <iterator>

#include "hashtbl.h"
#include "elis.h"

int main()
{
	//== TESTANDO HASH COM STD::STRING
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


	//== TESTANDO NEW;
	int * ptr = new int[4];
	for (int i = 0; i < 4; ++i)
	{
		ptr[i] = i;
	}
	std::cout << "[ ";
	for (int i = 0; i < 4; ++i)
	{
		std::cout << ptr[i] << " ";
	}
	std::cout << "]" << std::endl;
	ptr = new int[5];
	std::cout << "[ ";
	for (int i = 0; i < 5; ++i)
	{
		std::cout << ptr[i] << " ";
	}
	std::cout << "]" << std::endl;
	return 0;
}