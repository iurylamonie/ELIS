#include <iostream>
#include <string>
#include <iterator>

#include "hashtbl.h"
#include "elis.h"

int main()
{
	elis editor_texto;

	std::cout << "---> TESTE SIMPLES..." << std::endl;
	// O editor deve está vazio.
	std::cout << "Quantidade de linhas: " << editor_texto.size() << std::endl;
	std::cout << "Está vazio? " <<editor_texto.empty() << std::endl;
	std::cout << "Linha atual: " << editor_texto.linha_atual() << std::endl;
	std::cout << std::endl;
	
	std::cout << "---> INSERINDO PELA PRIMEIRA VEZ..." << std::endl;
	// Insere a primeira linha do arquivo.
	editor_texto.insert( 23, "Primeira linha\n");
	// Verifica se tem linha no arquivo.
	std::cout << "Quantidade de linhas: " << editor_texto.size() << std::endl;
	std::cout << "Está vazio? " <<editor_texto.empty() << std::endl;
	std::cout << "Linha atual: " << editor_texto.linha_atual() << std::endl;
	std::cout << std::endl;

	std::cout << "---> TRANSFORMANDO A PRIMEIRA LINHA INSERIDA NA LINHA ATUAL..." << std::endl;
	// Transforma a ultima linha a linha atual.
	editor_texto.modify(1);
	std::cout << "Linha atual: " << editor_texto.linha_atual() << std::endl;
	std::cout << std::endl;

	std::cout << "---> INSERINDO ANTES DE DEPOIS DA PRIMEIRA LINHA..." << std::endl;
	editor_texto.insert(1, "Linha Anterior.\n");
	std::cout << "Quantidade de linhas: " << editor_texto.size() << std::endl;
	editor_texto.append(2, "Linha Sucessora.\n");
	std::cout << "Quantidade de linhas: " << editor_texto.size() << std::endl;
	std::cout << std::endl;

	std::cout << "---> TRANSFORMANDO A ULTIMA LINHA NA LINHA ATUAL...\n--->	INSERINDO DEPOIS DA LINHA ATUAL..." << std::endl;
	// Joga a linha atual para ultima linha;
	editor_texto.modify(0);
	std::cout << "Linha atual: " << editor_texto.linha_atual() << std::endl;
	editor_texto.append(0, "Inserindo depois da ultima linha\n");
	std::cout << std::endl;
	

	std::cout << "---> INSERINDO VARIAS LINHAS NO FIM DO ARQUIVO..." << std::endl;
	editor_texto.modify(0);
	for (int i = 0; i < 10; ++i)
	{
		editor_texto.append(0, std::to_string(i) + "\n");
		editor_texto.modify(0);
	}
	std::cout << "Quantidade de linhas: " << editor_texto.size() << std::endl;
	std::cout << "Linha atual: " << editor_texto.linha_atual() << std::endl;
	std::cout << std::endl;

	std::cout << "---> DELETANDO LINHAS 1, 2 e 3..." << std::endl;
	editor_texto.deleteL(1,3);
	std::cout << "Quantidade de linhas: " << editor_texto.size() << std::endl;
	std::cout << "Linha atual: " << editor_texto.linha_atual() << std::endl;
	std::cout << std::endl;
	
	std::cout << "---> TRANSFORMANDO A ULTIMA LINHA NA ATUAL E DELETANDO A ATUAL LINHA..." << std::endl;
	editor_texto.modify();
	editor_texto.deleteL();
	std::cout << "Quantidade de linhas: " << editor_texto.size() << std::endl;
	std::cout << "Linha atual: " << editor_texto.linha_atual() << std::endl;
	std::cout << std::endl;
	
	std::cout << "---> GERANDO ARQUIVO COM FUNÇÃO WRITE..." << std::endl;
	editor_texto.write("fileline.txt");
	std::cout << "<--- ARQUIVO GERADO." << std::endl;
	std::cout << "Quantidade de linhas: " << editor_texto.size() << std::endl;
	std::cout << std::endl;
	return 0;
}