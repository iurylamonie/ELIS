#ifndef _ELIS_H_
#define _ELIS_H_

#include <string>

#include "hashtbl.h" //< size_type

class elis
{
public:
	//== CONSTRUTORES E DESTRUTORES
	elis();
	~elis();

	//== OPERAÇÕES SOBRE O ARQUIVO
	
	/**
	 * @brief	Salva todas as linhas do texto em um arquivo ascii name.
	 *			O Comando sem o fornecimento de um nome simplesmente grava
	 *			o texto no arquivo atual. Se o nome do arquivo atual ainda não
	 *			foi fornecido o programa deve solicitar um nome ao usuário.
	 * 
	 * @param[in]	_name O nome do arquivo.
	 */
	void write( const & std::string _name );

	/**
	 * @brief	Lê para a memória todas as linhas de texto do arquivo ascii name.
	 *			Se o arquivo indicado não existir um novo arquivo vazio name deve ser criado.
	 * 
	 * @param[in]	_name	O nome do arquivo.
	 */
	void open( const & std::string _name );

	/**
	 * @brief	Entra no modo edição permitindo a inserção de texto antes da linha n;
	 *			Se n não é fornecido o texto é inserido antes da linha atual.
	 * 
	 * @param[in]	_n	A linha n.
	 * @param[in]	_txt	O texto.
	 */
	void insert( const size_type _n = 0, const & std::string _txt );


private:
	/**
	 * m_curr_lin	Armazena a linha atual.
	 */

	//== ATRIBUTOS
	size_type m_curr_lin;
};

#endif