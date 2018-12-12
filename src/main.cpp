/**
 * @autor Iury Lamonie
 * 
 * @brief Arquivo de testes I.
 * 
 * @status Passou em tudo.
 */

#include <iostream>
#include <string>
#include <iterator>

#include "hashtbl.h"
#include "elis.h"

#define pLINHA_ATUAL std::cout << "Linha atual: " << editor_texto.linha_atual() << std::endl
#define pQTD_LINHA std::cout << "Quantidade de linhas na memoria: " << editor_texto.size() << std::endl

int main()
{
	std::cout << "----------- ARQUIVO DE TESTES I -----------" << std::endl;
	
	// Instanciado doo objeto ELIS
	elis editor_texto;

	std::cout << "---> INSERINDO PRIMEIRA LINHA..." << std::endl;
	editor_texto.insert(1,"Primeira linha.");
	editor_texto.modify();
	pQTD_LINHA;

	std::cout << "---> INSERINDO NO MODYFY..." << std::endl;
	editor_texto.insert(1,"Segunda linha.");
	pLINHA_ATUAL;
	pQTD_LINHA;
	
	std::cout << "---> APPEND NO MODYFY..." << std::endl;
	editor_texto.append(0,"Terceira linha.");
	pLINHA_ATUAL;
	pQTD_LINHA;
	editor_texto.modify();
	pLINHA_ATUAL;
	editor_texto.append(0, "Quarta linha.");
	pQTD_LINHA;

	std::cout << "---> TESTES DE INSERT..." << std::endl;
	editor_texto.insert(1, "Quinta linha.");
	editor_texto.insert(3, "Sexta linha.");
	editor_texto.insert(editor_texto.size(), "Setima linha.");
	editor_texto.insert(123, "Oitava linha.");
	pQTD_LINHA;

	std::cout << "---> TESTES DE APPEND..." << std::endl;
	editor_texto.append(1, "Nona linha.");
	editor_texto.append(4, "Decima linha.");
	editor_texto.append(editor_texto.size(), "Decima primeira linha.");
	editor_texto.append(123, "Decima segunda linha.");
	pQTD_LINHA;

	std::cout << "---> TESTES DE DELETE..." << std::endl;
	editor_texto.deleteL();
	pLINHA_ATUAL;
	pQTD_LINHA;
	editor_texto.deleteL(3, 5);
	pLINHA_ATUAL;
	pQTD_LINHA;

	std::cout << "---> TESTES DO COPY..." << std::endl;
	editor_texto.copy(1,4);
	editor_texto.deleteL(1,4);
	editor_texto.paste(1);
	editor_texto.modify();
	editor_texto.paste();

	std::cout << "---> TESTES SOBRE O ARQUIVO..." << std::endl;
	editor_texto.quit();
	editor_texto.open("doc/texto1.txt");
	editor_texto.write("doc/texto1.txt");
	editor_texto.open("doc/texto2.txt");
	pLINHA_ATUAL;
	pQTD_LINHA;
	editor_texto.modify();
	//editor_texto.quit();
	editor_texto.write("doc/texto3.txt");
	pLINHA_ATUAL;
	pQTD_LINHA;

	std::cout << "\n----------- IMPRIMINDO VALORES DA MEMORIA -----------" << std::endl;
	editor_texto.print_linhas();
	return 0;
}