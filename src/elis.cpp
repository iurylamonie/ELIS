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

void elis::write( const std::string & _name )
{
	// Verifica se o nome do arquivo foi informado.
	if( _name != std::string() ) //< Grava no arquivo informado.
	{
		std::ofstream file( _name );
		if( file.is_open() )
		{
			std::string txt;
			for ( size_type i = 1; i <= this->size(); ++i )
			{
				this->m_data_file.retrieve( i, txt );
				file << txt;
			}
		} else std::cout << "file isn't open!" << std::endl;
	}
	else //< Grava no arquivo atual.
	{
		if( this->m_file_stream.is_open() )
		{
			std::string txt;
			for ( size_type i = 1; i <= this->size(); ++i )
			{
				this->m_data_file.retrieve( i, txt );
				this->m_file_stream << txt;
			}
		}
		else std::cout << "current file isn't open!" << std::endl;
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

//== OPERAÇÕES DE CRUD (Create, Read, Update, Delete).

void elis::insert( const size_type _n, const std::string & _txt )
{
	// Verifica se foi informado a linha n ou se a linha n existe.
	if( ( _n != 0 ) && ( _n <= this->size() ) )
	{
		this->redistribute( _n );
		this->m_data_file.insert( _n, _txt );
	}
	// Verifica se tem linha atual
	else if( this->m_curr_lin != 0 )
	{
		this->redistribute( this->m_curr_lin );
		this->m_data_file.insert( this->m_curr_lin, _txt );
	}
	else this->m_data_file.insert( 1, _txt ); //< insere na primeira linha.
}

void elis::append( const size_type _n, const std::string & _txt )
{
	// Verifica se foi informado a linha ou se a linha informada existe.
	if( ( _n != 0 ) && ( _n <= this->m_data_file.size() ) )
	{
		this->redistribute( _n + 1 );
		this->m_data_file.insert( _n + 1, _txt );
	}
	// Verifica se tem linha atual
	else if( this->m_curr_lin != 0 )
	{
		this->redistribute( this->m_curr_lin + 1);
		this->m_data_file.insert( this->m_curr_lin + 1, _txt );
	}
	else this->m_data_file.insert( 1, _txt ); //< insere na primeira linha.
}

void elis::deleteL( const size_type _n, const size_type _m)
{
	// Verifica se a linha n foi informada.
	if( _n != 0 )
	{
		//	Verifica se o m foi informado e se m ultrapassa a quantidade de linhas.
		if( ( _m != 0 ) && ( _m <= this->m_data_file.size() ) )
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
		}
		else
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
		}
	}
	else 
	{
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
		//Verifica _n é a ultima linha e se ela é a linha atual e se não é a unica linha. 
		else if( ( this->m_curr_lin == old_size ) && ( this->size() > 1 ) )
		{
			--this->m_curr_lin;
		}
	}
}

void elis::copy( const size_type _n, const size_type _m )
{
	// Verifica se a linha n foi informada.
	if( _n != 0 )
	{
		//	Verifica se o m foi informado e se m ultrapassa a quantidade de linhas.
		//	e se _n é diferente de _m.
		if( ( _m != 0 ) && ( _m <= this->m_data_file.size() ) && ( _n != _m ) )
		{
			this->m_size_copy = _m - _n;
			size_type j = 0;
			this->m_copy_buffer = new std::string[this->m_size_copy];
			for (int i = _n; i <= _m; ++i)
			{
				this->m_copy_buffer[j] = this->m_data_file[i];
				++j;
			}
		}
		else 
		{
			this->m_copy_buffer = new std::string( this->m_data_file[_n] );//< Se a linha m não for informada ou m ultrapassa a quantidade de linhas.
			this->m_size_copy = 1;
		}
		
	}
	else
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
		}
	}
	
}