#include <elis.h>

//== CONSTRUTORES

elis::elis()
{
	// Essas informações são desnecessarias já que são valores padrões.
	this->m_save = false;
	this->m_curr_lin = 0;
	this->m_size_copy = 0;
}

//== FUNÇÕES AUXILIARES.

void elis::redistribute( const size_type _n )
{
	// Verifica se o arquivo não está vazio.
	if( !this->empty() )
	{
		// Percorre da última linha até a linha n.
		for (int i = this->size(); i >= _n ; --i)
		{
			// "Passa" a informação da linha atual para a linha seguinte.
			this->m_data_file.insert( i + 1, this->m_data_file[i] );
		}
	}
}
//== OPERAÇÕES DA JANELA

void help()
{
	std::cout << "Precisa de ajuda? Não conte comigo!" << std::endl;
}
//== OPERAÇÕES SOBRE O ARQUIVO

void elis::quit()
{
	// Verifica se o arquivo está salvo
	if( this->m_save )
	{
		//^ O arquivo está salvo.

		//Zera os atributos, menos o buffer de cópia.
		this->m_curr_lin = 0;
		this->m_save = false;
		this->m_name_file.clear();
		this->m_data_file.clear();
	}
	else
	{
		std::cout << "As alterações no arquivo não foram salvas! Deseja sair?" << std::endl;
	}
}

void elis::write( const std::string & _name )
{
	// Verifica se o nome do arquivo foi informado.
	if( _name != std::string() ) //< Grava no arquivo informado.
	{	
		std::ofstream file( _name );
		if( file.is_open() )
		{
			std::string line;

			// Percorre toda a memoria do hash com as linhas.
			for ( size_type i = 1; i <= this->size(); ++i )
			{
				this->m_data_file.retrieve( i, line );
				// Verifica se a linha que vai ser inserida é a ultima.
				if( i != this->size() ) file << line + "\n";
				else file << line;
			}
			// Verifica se existe arquivo atual.
			if( this->m_name_file.empty() )
			{
				// Caso não tenha arquivo atual,
				// o arquivo recém-salvo se torna o arquivo atual.
				this->m_name_file = _name;
				this->m_save = true;
			}
			file.close();
		} else std::cout << "file isn't open!" << std::endl;
	}
	else //< Grava no arquivo atual.
	{
		std::fstream file_stream( this->m_name_file, std::fstream::out | std::fstream::in | std::fstream::trunc );
		// Cria um novo arquivo vazio.
		if( file_stream.is_open() )
		{
			std::string line;
			// Percorre toda a memoria do hash com as linhas.
			for ( size_type i = 1; i <= this->size(); ++i )
			{
				this->m_data_file.retrieve( i, line );
				// Verifica se a linha que vai ser inserida é a ultima.
				if( i != this->size() ) file_stream << line + "\n";
				else file_stream << line;
			}
			this->m_save = true;
		}
		else std::cout << "Current file isn't open!" << std::endl;
	}
}

void elis::open( const std::string & _name)
{
	// Verifica se já tem um arquivo aberto que não foi salvo.
	if( this->m_name_file.empty() && !this->m_save )
	{
		this->quit();
	}
	else
	{
		this->m_name_file =  _name;
		std::fstream file_stream( this->m_name_file, std::fstream::out | std::fstream::in );
		// Verifica se o arquivo foi aberto.
		if( file_stream.is_open() )
		{
			// Limpa a memória.
			this->m_data_file.clear();
			// Reseta a posição atual( não tem posição atual).
			this->modify();

			size_type i = 1; //< Identificador da linha.
			std::string line; //< Texto da linha.
			// Percorre todo arquivo.
			while( std::getline( file_stream, line) )
			{
				// Insere a linha na memoria.
				this->m_data_file.insert( i, line);
				++i;
			}
			this->m_save = true;
		}
		else
		{
			// Cria um novo arquivo vazio.
			file_stream.open( this->m_name_file, std::fstream::out | std::fstream::in | std::fstream::trunc );
			// Limpa a memória.
			this->m_data_file.clear();
			// Reseta a posição atual( não tem posição atual).
			this->modify();
			this->m_save = true;
		}
	}
}

void elis::modify( const size_type _n )
{
	// Verifica se a linha foi informado ou se o linha informada
	// ultrapassa a quantidade de linhas.
	if( ( _n != 0 ) && ( _n <= this->size() ) ) 
	{
		this->m_curr_lin = _n;
	}
	else 
	{
		this->m_curr_lin = this->size();
	}
}

void elis::undo( void )
{
	std::cout << "Entrou undo" << std::endl;
	// Verifica se a pilha está vazia
	if( !this->m_stack_exc.empty() )
	{
		auto ec = this->m_stack_exc.top();
		switch(ec.ms_command)
		{
			case c_insert:
				// Deleta a linha inserida.
				this->deleteL( ec.ms_affec_rows[0].m_key );
				break;

			case c_append:
				std::cout << "Foi c_append!" << std::endl;
				break;
			case c_edit:
				std::cout << "Foi c_edit!" << std::endl;
				break;
			case c_delete:
				std::cout << "Foi c_delete!" << std::endl;
				break;
			case c_paste:
				std::cout << "Foi c_paste!" << std::endl;
				break;
			default:
				std::cout << "só o choro" << std::endl;
		} 
	}
}

//== OPERAÇÕES DE CRUD (Create, Read, Update, Delete).

void elis::insert( const size_type _n, const std::string & _txt )
{
	// Verifica se foi informado a linha n ou se a linha n existe.
	if( ( _n != 0 ) && ( _n <= this->size() ) )
	{
		// Reorganiza as linhas.
		// Deixa o indice n "vago".
		this->redistribute( _n );
		// Insere a linha,
		this->m_data_file.insert( _n, _txt );
	}
	// Verifica se o indice n é maior que a quantidade de linhas atuais.
	else if( _n > this->size() )
	{
		// Insere na última linha.
		this->m_data_file.insert( this->size() + 1, _txt );
	}
	// Verifica se tem linha atual
	else if( this->m_curr_lin != 0 )
	{
		// Reorganiza as linhas.
		this->redistribute( this->m_curr_lin );
		// Insere a linha,
		this->m_data_file.insert( this->m_curr_lin, _txt );
	}
	else 
	{
		this->m_data_file.insert( 1, _txt ); //< insere na primeira linha.
	}
	// Os dados foram modificados.
	this->m_save = false;
}

void elis::append( const size_type _n, const std::string & _txt )
{
	// Verifica se foi informado a linha ou se a linha informada existe.
	if( ( _n != 0 ) && ( _n <= this->m_data_file.size() ) )
	{
		// Reorganiza as linhas.
		// Deixa o indice n + 1 "vago".
		this->redistribute( _n + 1 );
		this->m_data_file.insert( _n + 1, _txt );
	}
	// Verifica se o indice n é maior que a quantidade de linhas atuais.
	else if( _n > this->size() )
	{
		// Insere na última linha.
		this->m_data_file.insert( this->size() + 1, _txt );
	}
	// Verifica se tem linha atual
	else if( this->m_curr_lin != 0 )
	{
		this->redistribute( this->m_curr_lin + 1);
		this->m_data_file.insert( this->m_curr_lin + 1, _txt );
	}
	else 
	{
		this->m_data_file.insert( 1, _txt ); //< insere na primeira linha.
	}
	this->m_save = false;
}

void elis::deleteL( const size_type _n, const size_type _m)
{
	if( _n != 0 )
	{
		//	Verifica se o m foi informado e se m ultrapassa a quantidade de linhas.
		if( ( _m != 0 ) && ( _m <= this->m_data_file.size() ) && ( _m >= _n ) )
		{
			// Armazena a quantidade de linhas antes de deletar as linhas
			// de _n até _m.
			size_type old_size = this->size();
			// Deleta as linhas de _n até _m.
			for (int i = _n; i <= _m; ++i)
			{
				this->m_data_file.erase( i );
				// Verifica se está deletando a linha atual.
				if( this->m_curr_lin == i ) this->modify( _n );
			}

			// Verifica se a última linha deletada, _m, é a última linha.
			// Caso não seja, repassa todos as linhas seguintes a _m para
			// a posição _n.
			if( _m < old_size )
			{
				int j = 0;
				for (int i = _m + 1; i <= old_size; ++i)
				{
					// "Cópia" a linha seguintes à _m em _n;
					this->m_data_file.insert( _n + j, this->m_data_file[ i ] );
					if( this->m_curr_lin == i ) this->modify( _n + j );
					// Deleta a linha original que foi "cópiada".
					this->m_data_file.erase(i);
					++j;
				}
			}
			this->m_save = false;
		}
		// Verifica se m é maior que a quantidade de linhas do arquivo.
		else if( _m > this->size() )
		{
			// Armazena a quantidade de linhas antes de deletar as linhas
			// de _n até quantidade de linhas atuais.
			size_type old_size = this->size();
			// Deleta as linhas de _n até size().
			for (int i = _n; i <= old_size; ++i)
			{
				this->m_data_file.erase( i );
				// Verifica se está deletando a linha atual.
				if( this->m_curr_lin == i ) this->modify( _n - 1);
			}

			this->m_save = false;
		}
		else if ( ( _n > _m ) && ( _n <= this->size() ) )
		{	
			// Armazena a quantidade de linhas antes de deletar a linha _n.
			size_type old_size = this->size();

			this->m_data_file.erase( _n ); //< Se a linha m não for informada ou m ultrapassa a quantidade de linhas.
			//Verifica _n é a ultima linha e se ela é a linha atual e se não é a unica linha.
			if( ( _n == old_size ) && ( this->m_curr_lin == _n ) && ( this->size() > 1 ) )
			{
				--this->m_curr_lin;
			}
			// Verifica se a última linha deletada, _n, é a última linha.
			// Caso não seja, repassa todos as linhas seguintes a _n para
			// a posição _n.
			if( _n < old_size )
			{
				int j = 0;
				for (int i = _n + 1; i <= old_size; ++i)
				{
					// "Cópia" a linha seguintes à _m em _n;
					this->m_data_file.insert( _n + j, this->m_data_file[ i ] );
					// Deleta a linha original que foi "cópiada".
					this->m_data_file.erase(i);
					++j;
				}
			}		
			this->m_save = false;
		}
	}
	else if( _n == 0 )
	{
		{}
		// Armazena a quantidade de linhas antes de deletar a linha current.
		size_type old_size = this->size();

		this->m_data_file.erase( this->m_curr_lin );

		// Verifica se a última linha deletada, _n, é a última linha.
		// Caso não seja, repassa todos as linhas seguintes a _n para
		// a posição _n.
		if( this->m_curr_lin < old_size )
		{
			int j = 0;
			for (int i = this->m_curr_lin + 1; i <= old_size; ++i)
			{
				// "Cópia" a linha seguintes à _m em _n;
				this->m_data_file.insert( this->m_curr_lin + j, this->m_data_file[ i ] );
				// Deleta a linha original que foi "cópiada".
				this->m_data_file.erase(i);
				++j;
			}
		}
		//Verifica se a linha atual estava na ultima posição e se o arquivo tem mais de uma linha.
		else if( ( this->m_curr_lin == old_size ) && ( this->size() > 1 ) )
		{
			--this->m_curr_lin;
		}

		this->m_save = false;
	}
}

void elis::copy( const size_type _n, const size_type _m )
{
	// Verifica se a linha n foi informada.
	if( _n != 0 )
	{
		//	Verifica se o m foi informado e se m ultrapassa a quantidade de linhas.
		//	e se _n é diferente de _m.
		if( ( _m != 0 ) && ( _m <= this->size() ) /*&& ( _n != _m )*/ )
		{
			this->m_size_copy = _m - _n + 1;
			size_type j = 0;
			this->m_copy_buffer = new std::string[this->m_size_copy];
			for (int i = _n; i <= _m; ++i)
			{
				this->m_copy_buffer[j] = this->m_data_file[i];
				++j;
			}
		}
		// Verifica se m é maior que a quantidade de linhas atuais.
		else if( _m > this->size() )
		{
			this->m_size_copy = _m - this->size() + 1;
			size_type j = 0;
			this->m_copy_buffer = new std::string[this->m_size_copy];
			for (int i = _n; i <= this->size(); ++i)
			{
				this->m_copy_buffer[j] = this->m_data_file[i];
				++j;
			}
		}
		
	}
	else if( _n == 0)
	{
		this->m_copy_buffer = new std::string( this->m_data_file[this->m_curr_lin] );
		this->m_size_copy = 1;
	} 
}

void elis::paste( const size_type _n )
{
	size_type old_size = this->size();
	if( _n != 0 )
	{
		// Percorre todo o buffer copia.
		// Se m_size_copy for 0, ou seja, não tem informação no buffer,
		// não entrar no for.
		for (int i = 1; i <= this->m_size_copy; ++i)
		{
			// Verifica se _n não é a ultima linha.
			// Repassa as linhas seguintes a _n para as proximas posições.
			if( _n <  old_size ) this->redistribute( _n + i );
			// Armazena o texto armazenado no copy buffer para os dados do arquivo.
			this->m_data_file.insert( _n + i, this->m_copy_buffer[ i - 1 ] );
			if( i == 1 ) this->m_save = false;
		}
	}
	else
	{
		// Percorre todo o buffer copia.
		// Se m_size_copy for 0, ou seja, não tem informação no buffer,
		// não entrar no for.
		for (int i = 1; i <= this->m_size_copy; ++i)
		{
			// Verifica se a linha não é a ultima linha.
			// Repassa as linhas seguintes a _n para as proximas posições.
			if( this->m_curr_lin < old_size ) this->redistribute( this->m_curr_lin + i );
			// Armazena o texto armazenado no copy buffer para os dados do arquivo.
			this->m_data_file.insert( this->m_curr_lin + i, this->m_copy_buffer[ i - 1 ] );
			if( i == 1 ) this->m_save = false;
		}
	}	
}