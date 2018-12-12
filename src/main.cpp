/**
 * @autor Iury Lamonie
 * 
 * @brief Arquivo de testes.
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
	elis editor_texto;
	pLINHA_ATUAL;
	pQTD_LINHA;
	editor_texto.insert(1,"E ai man.");
	editor_texto.insert(2,"E ai man2.");
	editor_texto.insert(3,"E ai man3.");
	editor_texto.modify();
	pLINHA_ATUAL;
	pQTD_LINHA;

	std::cout << "Modo atual: " << editor_texto.get_current_mode() << std::endl;
	editor_texto.set_current_mode(elis::Modo::mo_edit);
	std::cout << "Modo atual: " << editor_texto.get_current_mode() << std::endl;
	editor_texto.set_current_mode(elis::Modo::mo_command);
	std::cout << "Modo atual: " << editor_texto.get_current_mode() << std::endl;

	std::cout << "Linha 2: " << editor_texto.get_row(1) << std::endl;
	std::cout << "Linha 2: " << editor_texto.get_row(2) << std::endl;
	std::cout << "Linha 2: " << editor_texto.get_row(3) << std::endl;
	return 0;
}