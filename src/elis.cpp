#include <elis.h>

elis::elis()
{
	// Essas informações são desnecessarias já que são valores padrões.
	this->m_save = false;
	this->m_curr_lin = 0;
	this->m_size_copy = 0;
}

void elis::redistribute( const size_type _n )
{
	// Verifica se o arquivo não está vazio.
	if( !this->m_data_file.empty() )
	{
		// Percorre da última linha até a linha n.
		size_type sz = this->m_data_file.size();
		for (int i = sz; i <= _n ; --i)
		{
			// "Passa" a informação da linha atual para a linha seguinte.
			this->m_data_file.insert( i + 1, this->m_data_file[i] );
		}
	}
}

void elis::insert( const size_type _n, const std::string & _txt )
{
	// Verifica se foi informado a linha ou se a linha informada existe.
	if( ( _n != 0 ) && ( _n <= this->m_data_file.size() ) )
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
			for (int i = _n; i <= _m; ++i)
			{
				this->m_data_file.erase( _n );
			}
		}
		else this->m_data_file.erase( _n ); //< Se a linha m não for informada ou m ultrapassa a quantidade de linhas.
	}
	else this->m_data_file.erase( this->m_curr_lin );
	
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
			size_type sz = _m - _n;
			size_type j = 0;
			this->m_copy_buffer = new std::string[sz];
			this->m_size_copy = sz;
			for (int i = _n; i <= _m; ++i)
			{
				this->m_copy_buffer[j] = this->m_data_file[i];
				++j;
			}
		}
		else this->m_copy_buffer = new std::string( this->m_data_file[_n] );//< Se a linha m não for informada ou m ultrapassa a quantidade de linhas.
	}
	else this->m_copy_buffer = new std::string( this->m_data_file[this->m_curr_lin] );
}

//void elis::paste( const size_type _n );