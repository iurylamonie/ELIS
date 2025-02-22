#ifndef _ELIS_H_
#define _ELIS_H_

#include <string> //< std::string
#include <fstream> // < std::fstream
#include <iostream> //< std::cout
#include <stack> //< std::stack<>
#include <vector>
#include <ncurses.h>

#include "hashtbl.h" //< size_type

using HEntry = ac::HashEntry< int, std::string >;

/**
 * @brief      Tipos de comando.
 */
enum command_t
{
	c_insert,
	c_append,
	c_edit,
	c_delete,
	c_paste
};

/**
 * @brief      Organiza os dados de comandos útilizados, armazenando o comando
 *             executado, salvando posiveis linhas afetadas e a quantida de
 *             linhas afetadas.
 */
struct Exe_commands
{
	/**
	 * ms_command	Comando útilizado.
	 * ms_affec_rows	Linhas afetadas.
	 * ms_size	Quantidade de linhas afetadas.
	 */
	command_t ms_command;
	std::vector<HEntry> ms_affec_rows;
	size_type ms_size;
};

/**
 * @brief      classe com as funcionalidades do Editor de LInha Simples.
 */
class elis
{
public:

	/**
	 * @brief      Os modos do exclusivos do ELIS, modo normal, edição e comando.
	 */
	enum Modo
	{
		mo_normal,
		mo_edit,
		mo_command
	};

	//== CONSTRUTORES E DESTRUTORES
	elis();
	//~elis();

	//== OPERAÇÕES DA JANELA

	/**
	 * @brief	Exibe um texto de ajuda, explicando de forma resumida quais são os
	 * 			comandos do programa.
	 */
	void help();

	/**
	 * @brief	Encerra o programa. Se o texto atual não tiver sido salvo, o programa
	 * 			deve exibir uma mensagem indicando o fato e confirmar a operação.
	 */
	void quit();

	//== OPERAÇÕES SOBRE O ARQUIVO
	
	/**
	 * @brief	Salva todas as linhas do texto em um arquivo ascii name.
	 *			O Comando sem o fornecimento de um nome simplesmente grava
	 *			o texto no arquivo atual. Se o nome do arquivo atual ainda não
	 *			foi fornecido o programa deve solicitar um nome ao usuário.
	 * 
	 * @param[in]	_name O nome do arquivo.
	 */
	void write( const std::string & _name = std::string() );

	/**
	 * @brief	Lê para a memória todas as linhas de texto do arquivo ascii name.
	 *			Se o arquivo indicado não existir um novo arquivo vazio name deve ser criado.
	 * 
	 * @param[in]	_name	O nome do arquivo.
	 */
	void open( const std::string & _name );

	/**
	 * @brief	Torna n linha atual. Se n não é fornecido então a última
	 *			linha do texto passa a ser a atual.
	 * 
	 * @param[in]	_n	A linha n.
	 */
	void modify( const size_type _n = 0);

	/**
	 * @brief      Desfaz os últimos comandos realizados desde a última gravação do arquivo.
	 */
	void undo();

	/**
	 * @brief	Edita linha n, posicionando o cursos no final da linha. 
	 *			A edição será básica, suportando apenas o uso do <backspace> 
	 *			para apagar os caracteres da linha. Se n não é fornecido, 
	 *			então a linha atual será editada.
	 * 
	 * @param[in]	_n	A linha n.
	 */
	void edit( const size_type _n );

	//== OPERAÇÕES DE CRUD (Create, Read, Update, Delete).

	/**
	 * @brief	Entra no modo edição, permitindo a inserção de texto antes da linha n;
	 *			Se n não é fornecido, o texto é inserido antes da linha atual.
	 * 
	 * @param[in]	_n	A linha n.
	 * @param[in]	_txt	O texto.
	 */
	void insert( const size_type _n = 0, const std::string & _txt = std::string() );

	/**
	 * @brief	Entra no modo edição, permitindo a inserção de texto depois da linha n;
	 *			Se n não é fornecido, o texto é inserido depois da linha atual.
	 * 
	 * @param[in]	_n	A linha n.
	 * @param[in]	_txt	O texto.
	 */
	void append( const size_type _n = 0, const std::string & _txt = std::string() );

	/**
	 * @brief	Remove as linhas n até m. Se apenas n é fornecido, remove-se a linha n.
	 *			Se nenhum número é fornecido, remove-se a linha atual.
	 * 
	 * @param[in]	_n	A linha n.
	 * @param[in]	_m	A linha m.
	 */
	void deleteL( const size_type _n = 0, const size_type _m = 0 );

	/**
	 * @brief	Copia as linhas n até m para um buffer. Se apenas n é fornecido, copia-se a linha n.
	 *			Se nenhum número é fornecido, copia-se a linha atual.
	 * 
	 * @param[in]	_n	A linha n.
	 * @param[in]	_m	A linha m.
	 */
	void copy( const size_type _n = 0, const size_type _m = 0 );

	/**
	 * @brief	Cola (inserindo) as linhas atualmente armazenada no buffer depois da linha n, permanecendo no modo de comando.
	 *			Se nenhum número é fornecido, as linhas serão coladas logo após a linha atual.
	 * 
	 * @param[in]	_n	A linha n.
	 * @param[in]	_m	A linha m.
	 */
	void paste( const size_type _n = 0 );

	//== OPERADORES DE CAPACIDADE

	/**
	 * @brief	Retorna a quantidade de linhas atualmente armazenadas.
	 *
	 * @return	A quantidade de linhas.
	 */
	size_type size() { return this->m_data_file.size(); }

	/**
	 * @brief	Verifica se o arquivo atual está vázio.
	 *
	 * @return	True se o arquivo estiver vazio, false caso contrário.
	 */
	size_type empty() { return this->m_data_file.empty(); }

	/**
	 * @brief	Retorna a posição da linha atual.
	 *
	 * @return	A posição da linha atual.
	 */
	size_type linha_atual() { return this->m_curr_lin; }

	/**
	 * @brief      Obtém o dado associado ao indice da linha fornecido.
	 *
	 * @param[in]  _n    O indice da linha.
	 *
	 * @return     O dado associado ao indice.
	 */
	std::string get_row( const size_type & _n ) { return this->m_data_file[ _n ]; }

	/**
	 * @brief      Verifica se atualmente há um arquivo aberto.
	 *
	 * @return     True se há um arquivo aberto, false caso contrário.
	 */
	bool file_is_open() { return this->m_name_file.empty(); }

	/**
	 * @brief      Obtém o nome do arquivo atual.
	 *
	 * @return     O nome do arquivo.
	 */
	const std::string& get_file_name() const { return this->m_name_file; } 
	
	/**
	 * @brief      Obtém o modo atual do elis.
	 *
	 * @return     O modo atual.
	 */
	const Modo get_current_mode() const { return this->m_current_mode; }

	/**
	 * @brief      Modifica o modo atual do elis.
	 *
	 * @param[in]  _mod  O novo modo atual.
	 */
	void set_current_mode( const Modo & _mod ) { this->m_current_mode = _mod; }

	/**
	 * @brief      Imprime as linhas armazenadas na memoria (apenas para testes).
	 */
	void print_linhas()
	{
		std::cout << this->m_data_file << std::endl;
	}
private:
	/**
	 * m_curr_lin	Armazena a linha atual.
	 * m_copy_buffer	Armazena as linhas que foram copiadas.
	 * m_size_copy	Armazena a quantidade de linhas que foram copiadas.
	 * m_save	True se o arquivo estiver salvo, false caso contrário.
	 * m_name_file	Armazena o nome do arquivo que está atualmente aberto.
	 * m_data_file	Armazena cada linha do arquivo ascii.
	 * m_file_stream	Armazena a associação com o objeto stream.
	 * m_execut_c	Uma pilha para comando executados.
	 * m_current_mode	Guarda o modo atual, se é normal, edição ou comando.
	 */

	//== ATRIBUTOS
	size_type m_curr_lin;
	std::string * m_copy_buffer;
	size_type m_size_copy;
	bool m_save;
	std::string m_name_file;
	ac::HashTbl< int, std::string > m_data_file;
	std::stack< Exe_commands > m_stack_exc;
	Modo m_current_mode;
	//std::fstream m_file_stream;

	//== FUNÇÕES AUXILIARES

	/**
	 * @brief      Passa a linha n para a proxima linha, ou seja,n + 1. 
	 * Ocorre a mesma situação com as linhas sucessores à n até a última linha.
	 *
	 * @param[in]  _n    A linha n.
	 */
	void redistribute( const size_type _n );
};

#endif