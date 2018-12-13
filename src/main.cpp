/**
 * @autor Iury Lamonie
 */
#include "elis.h"

#define pLINHA_ATUAL std::cout << "Linha atual: " << editor_texto.linha_atual() << std::endl
#define pQTD_LINHA std::cout << "Quantidade de linhas na memoria: " << editor_texto.size() << std::endl

#define ENTER 10
#define ESC 27
#define DOISPONTOS 58
#define BACKSPACE 127

/**
 * @brief      Muda o status da janela de comando.
 *
 * @param      _win      The window
 * @param      _comando  The comando
 *
 * @return     { description_of_the_return_value }
 */
WINDOW* mod_jan_com(  WINDOW * _win, const std::string & _comando );

/**
 * @brief      Apaga o elemento da janela.
 *
 * @param      _win  The window
 *
 * @return     { description_of_the_return_value }
 */
WINDOW* key_backspace(  WINDOW * _win );

/**
 * @brief      Desce ou sobe a tela depedendo do tipo de operação(subir ou descer) na linha.
 *
 * @param[in]  _tipo  The tipo //< subir ou descer
 */
WINDOW* scrolling( WINDOW* _w,  elis & _et, const std::string & _tipo );

WINDOW* imprimir_linhas( WINDOW * _w, elis & _et);
int main()
{
	elis editor_texto;

	//Inicializando janela padrão;
	initscr();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	// Especificações da tabela.
	int win_height = 3, win_width = COLS , win_start_y = LINES - 3, win_start_x = 0;
	// Janela espefifica de commando.
	WINDOW * win = newwin( win_height, win_width, win_start_y, win_start_x );
	refresh();

	win = mod_jan_com(win, "~ NORMAL ~");
	//wrefresh(win);
	
	// Variavel para armazenar o modo comando.
	char com;

	// Seleciona um comando.
	while( com = getch() )
	{
		//== Modo commmand
		if( com == 58 )
		{
			win = mod_jan_com(win, "~ COMMAND ~: ");
			wmove(win, 1, 14);
			// Torna as letras visiveis
			echo();
			// Armazena a linha de comando.
			char cstr/*[COLS]*/;
			// Reseta a posição do curso da janela de comandos.
			wmove(win, 1, 14);
			// torna visivel o cursor.
			curs_set(1);
			wrefresh(win);
			
			cstr = wgetch(win);
			while( cstr != ESC )
			{				
				// Comando Modify	
				if( cstr == 'm' || cstr == 'M' )
				{
					// Linha.
					int n;
					wgetch(win); //<pula o espaço.
					wmove(win, 3, 14);
					cstr = wgetch(win);
					std::string str;
					
					while( cstr != ' ' && cstr != ENTER )
					{
						str.push_back(cstr);
						cstr = wgetch(win);
					}

					// converte string para inteiro.
					n = std::stoi(str);

					editor_texto.modify(n);
					stdscr = imprimir_linhas(stdscr, editor_texto);
					win = mod_jan_com(win, "~ COMMAND ~: ");
					refresh();			
				}
				// Comando Write
				else if( cstr == 'w' || cstr == 'W' )
				{
					wgetch(win); //<pula o espaço.
					wmove(win, 3, 14);
					cstr = wgetch(win);
					std::string str;
					
					while( cstr != ' ' && cstr != ENTER )
					{
						str.push_back(cstr);
						cstr = wgetch(win);
					}

					editor_texto.write(str);	
				}
				// Comando Open
				else if( cstr == 'O' || cstr == 'o' )
				{
					wgetch(win); //<pula o espaço.
					wmove(win, 3, 14);
					cstr = wgetch(win);
					std::string str;
					
					while( cstr != ' ' && cstr != ENTER )
					{
						str.push_back(cstr);
						cstr = wgetch(win);
					}

					editor_texto.open(str);
					stdscr = imprimir_linhas(stdscr, editor_texto);	
				}
				// Comando Insert
				else if( cstr == 'i' || cstr == 'I' )
				{
					
					int n;
					wgetch(win); //<pula o espaço.
					wmove(win, 3, 14);
					cstr = wgetch(win);
					std::string str1;
					
					while( cstr != ' ' && cstr != ENTER )
					{
						str1.push_back(cstr);
						cstr = wgetch(win);
					}

					// converte string para inteiro.
					n = std::stoi(str1);
					editor_texto.modify(n);

					int x,y;
					wclear(stdscr);
					win = mod_jan_com(win, "~ INSERT ~ ");
					wrefresh(stdscr);
					//wrefresh(win);
					//wrefresh(stdscr);
					echo();
					// Mover o curso para o final da linha atual.
					move( 0,0);

					curs_set(1);

					// Armazena a linha digitada
					char cstr[COLS];
					char v = getch();
					std::string str;
					// Verifica se <esc> foi digitado
					while( v != ESC )
					{
						// Verifica se <enter> foi digitado
						// ou se x chegou no limite das colunas.
						if ( v == ENTER)
						{					
							// Obtém linha e coluna atual;
							//getyx(stdscr,y,x);
							// Insere o valor na pilha
							editor_texto.insert( editor_texto.linha_atual(), str );
							// Torna a linha recem inserida na atual;
							editor_texto.modify(editor_texto.linha_atual());
							
							// Limpa a tela para imprimir os
							// arquivos da memoria.
							stdscr = imprimir_linhas(stdscr, editor_texto);
							
							str.clear();
							break;
						}
						// Verifica se <backspace> foi digitado.
						else if( v == BACKSPACE )
						{
							if( !str.empty() )
							{
								str.pop_back();	
													
							}
							
							stdscr = key_backspace(stdscr);
							// Por algum motivo divino, so apaga quando uso isso.
							win = mod_jan_com(win, "~ INSERT ~ ");
							refresh();
							getyx(stdscr,y,x);
							move(y,x);	
						}
						else
						{
							str.push_back(v);
							getyx(stdscr,y,x);
							move(y,x);
						}
						v = getch();
						if( v == ESC )
						{
							//getyx(stdscr,y,x);
							editor_texto.insert( editor_texto.linha_atual(), str );
							

							// Limpa a tela para imprimir os
							// arquivos da memoria.
							stdscr = imprimir_linhas(stdscr, editor_texto);
						
							refresh();
							v = 'a';
							str.clear();
							break;
						}			
					}

					// Caso dê ESC no inicio.
					if( v == ESC )
					{
							//getyx(stdscr,y,x);
							editor_texto.insert( editor_texto.linha_atual(), str );

							// Limpa a tela para imprimir os
							// arquivos da memoria.
							stdscr = imprimir_linhas(stdscr, editor_texto);
							win = mod_jan_com(win, "~ NORMAL ~");

							refresh();
							str.clear();
					}	

					noecho();
					curs_set(0);
					move(editor_texto.linha_atual(),0);				
				}
				// Comando Append
				else if( cstr == 'a' || cstr == 'A' )
				{
					
					int n;
					wgetch(win); //<pula o espaço.
					wmove(win, 3, 14);
					cstr = wgetch(win);
					std::string str1;
					
					while( cstr != ' ' && cstr != ENTER )
					{
						str1.push_back(cstr);
						cstr = wgetch(win);
					}

					// converte string para inteiro.
					n = std::stoi(str1);
					editor_texto.modify(n);

					int x,y;
					wclear(stdscr);
					win = mod_jan_com(win, "~ INSERT ~ ");
					wrefresh(stdscr);
					//wrefresh(win);
					//wrefresh(stdscr);
					echo();
					// Mover o curso para o final da linha atual.
					move( 0,0);

					curs_set(1);

					// Armazena a linha digitada
					char cstr[COLS];
					char v = getch();
					std::string str;
					// Verifica se <esc> foi digitado
					while( v != ESC )
					{
						// Verifica se <enter> foi digitado
						// ou se x chegou no limite das colunas.
						if ( v == ENTER)
						{					
							// Obtém linha e coluna atual;
							//getyx(stdscr,y,x);
							// Insere o valor na pilha
							editor_texto.append( editor_texto.linha_atual(), str );
							// Torna a linha recem inserida na atual;
							editor_texto.modify(editor_texto.linha_atual());
							
							// Limpa a tela para imprimir os
							// arquivos da memoria.
							stdscr = imprimir_linhas(stdscr, editor_texto);
							
							str.clear();
							break;
						}
						// Verifica se <backspace> foi digitado.
						else if( v == BACKSPACE )
						{
							if( !str.empty() )
							{
								str.pop_back();	
													
							}
							
							stdscr = key_backspace(stdscr);
							// Por algum motivo divino, so apaga quando uso isso.
							win = mod_jan_com(win, "~ INSERT ~ ");
							refresh();
							getyx(stdscr,y,x);
							move(y,x);	
						}
						else
						{
							str.push_back(v);
							getyx(stdscr,y,x);
							move(y,x);
						}
						v = getch();
						if( v == ESC )
						{
							//getyx(stdscr,y,x);
							editor_texto.append( editor_texto.linha_atual(), str );
							

							// Limpa a tela para imprimir os
							// arquivos da memoria.
							stdscr = imprimir_linhas(stdscr, editor_texto);
						
							refresh();
							v = 'a';
							str.clear();
							break;
						}			
					}

					// Caso dê ESC no inicio.
					if( v == ESC )
					{
							//getyx(stdscr,y,x);
							editor_texto.insert( editor_texto.linha_atual(), str );

							// Limpa a tela para imprimir os
							// arquivos da memoria.
							stdscr = imprimir_linhas(stdscr, editor_texto);
							win = mod_jan_com(win, "~ NORMAL ~");

							refresh();
							str.clear();
					}	

					noecho();
					curs_set(0);
					move(editor_texto.linha_atual(),0);				
				}
				// Comando Delete
				else if( cstr == 'd' || cstr == 'D' )
				{
					int n, m;
					wgetch(win); //<pula o espaço.
					wmove(win, 3, 14);
					cstr = wgetch(win);
					std::string str1;
					
					while( cstr != ' ' )
					{
						if( cstr == ENTER ) 
						{
							editor_texto.deleteL( editor_texto.linha_atual() );
							break;
						}
						str1.push_back(cstr);
						cstr = wgetch(win);
					}

					n = std::stoi(str1);
					str1.clear();

					cstr = wgetch(win);
					while( cstr != ' ' )
					{
						if( cstr == ENTER ) 
						{
							editor_texto.deleteL( n );
							break;
						}
						str1.push_back(cstr);
						cstr = wgetch(win);
					}

					m = std::stoi(str1);
					editor_texto.deleteL(n,m);
					stdscr = imprimir_linhas(stdscr, editor_texto);					
				}
				// Comando copia
				else if( cstr == 'c' || cstr == 'C' )
				{
					int n, m;
					wgetch(win); //<pula o espaço.
					wmove(win, 3, 14);
					cstr = wgetch(win);
					std::string str1;
					
					while( cstr != ' ' )
					{
						if( cstr == ENTER ) 
						{
							editor_texto.copy( editor_texto.linha_atual() );
							break;
						}
						str1.push_back(cstr);
						cstr = wgetch(win);
					}

					n = std::stoi(str1);
					str1.clear();

					cstr = wgetch(win);
					while( cstr != ' ' )
					{
						if( cstr == ENTER ) 
						{
							editor_texto.copy( n );
							break;
						}
						str1.push_back(cstr);
						cstr = wgetch(win);
					}

					m = std::stoi(str1);
					editor_texto.copy(n,m);
					stdscr = imprimir_linhas(stdscr, editor_texto);					
				}

				// Comando paste	
				if( cstr == 'p' || cstr == 'P' )
				{
					// Linha.
					int n;
					wgetch(win); //<pula o espaço.
					wmove(win, 3, 14);
					cstr = wgetch(win);
					std::string str;
					
					while( cstr != ' ' && cstr != ENTER )
					{
						str.push_back(cstr);
						cstr = wgetch(win);
					}

					// converte string para inteiro.
					n = std::stoi(str);

					editor_texto.paste(n);
					stdscr = imprimir_linhas(stdscr, editor_texto);
					win = mod_jan_com(win, "~ COMMAND ~: ");
					refresh();			
				}
				win = mod_jan_com(win, "~ COMMAND ~: ");
				wmove(win, 1, 14);
				cstr = wgetch(win);
				echo();
				curs_set(1);
			}

			noecho();
			curs_set(0);
			move(editor_texto.linha_atual(),0);
			win = mod_jan_com(win, "~ NORMAL ~");
			
		}
		//== Modo EDIÇÂO
		else if( com == 'i' || com == 'I' )
		{
			win = mod_jan_com(win, "~ INSERT ~ ");
			
			echo();

			// Mover o curso para o final da linha atual.
			move(editor_texto.linha_atual(),0);
			int x,y;
			getbegyx(stdscr,y,x);
			move(editor_texto.linha_atual() % (LINES - 3),x);
			curs_set(1);

			// Armazena a linha digitada
			char cstr[COLS];
			char v = getch();
			std::string str;
			// Verifica se <esc> foi digitado
			while( v != ESC )
			{
				// Verifica se <enter> foi digitado
				// ou se x chegou no limite das colunas.
				if ( v == ENTER)
				{					
					// Obtém linha e coluna atual;
					//getyx(stdscr,y,x);
					// Insere o valor na pilha
					editor_texto.insert( editor_texto.linha_atual() + 1, str );
					// Torna a linha recem inserida na atual;
					editor_texto.modify(editor_texto.linha_atual() + 1);
					
					// Limpa a tela para imprimir os
					// arquivos da memoria.
					stdscr = imprimir_linhas(stdscr, editor_texto);
					win = mod_jan_com(win, "~ INSERT ~");
					
					str.clear();
					move(editor_texto.linha_atual() % (LINES - 3) , 0 );
					stdscr = scrolling( stdscr, editor_texto, "descer" );
					//stdscr = imprimir_linhas(stdscr, editor_texto);
					win = mod_jan_com(win, "~ INSERT ~");
					//win = mod_jan_com(win, "~ INSERT ~ ");
				}
				// Verifica se <backspace> foi digitado.
				else if( v == BACKSPACE )
				{
					if( !str.empty() )
					{
						str.pop_back();	
											
					}
					
					stdscr = key_backspace(stdscr);
					// Por algum motivo divino, so apaga quando uso isso.
					win = mod_jan_com(win, "~ INSERT ~ ");
					refresh();
					getyx(stdscr,y,x);
					move(y,x);	
				}
				else
				{
					str.push_back(v);
					getyx(stdscr,y,x);
					move(y,x);
				}
				v = getch();
				if( v == ESC )
				{
					//getyx(stdscr,y,x);
					editor_texto.insert( editor_texto.linha_atual() + 1, str );
					editor_texto.modify( editor_texto.linha_atual() + 1);

					// Limpa a tela para imprimir os
					// arquivos da memoria.
					stdscr = imprimir_linhas(stdscr, editor_texto);
					win = mod_jan_com(win, "~ NORMAL ~");
					
					refresh();
					v = 'a';
					str.clear();
					break;
				}			
			}

			// Caso dê ESC no inicio.
			if( v == ESC )
			{
					//getyx(stdscr,y,x);
					editor_texto.insert( editor_texto.linha_atual() + 1, str );
					editor_texto.modify( editor_texto.linha_atual() + 1);

					// Limpa a tela para imprimir os
					// arquivos da memoria.
					stdscr = imprimir_linhas(stdscr, editor_texto);
					win = mod_jan_com(win, "~ NORMAL ~");

					refresh();
					str.clear();
			}	

			noecho();
			curs_set(0);
			move(editor_texto.linha_atual(),0);
			win = mod_jan_com(win, "~ NORMAL ~");
			
		}
		//== Navega pra cima.
		else if( com == 'k' || com == 'K' )
		{
			if( editor_texto.linha_atual() > 1 )
			{
				editor_texto.modify( editor_texto.linha_atual() - 1 );
				stdscr = imprimir_linhas( stdscr, editor_texto );
				win = mod_jan_com(win, "~ NORMAL ~");
			}
		}
		//== Navega pra baix
		else if( com == 'j' || com == 'J' )
		{
			if( editor_texto.linha_atual() <= editor_texto.size() )
			{
				editor_texto.modify( editor_texto.linha_atual() + 1 );
				stdscr = imprimir_linhas( stdscr, editor_texto );
				win = mod_jan_com(win, "~ NORMAL ~");
			}
		}
	}

	endwin();

	return 0;
}


WINDOW* mod_jan_com( WINDOW * _win, const std::string & _comando )
{
	wclear(_win);
	box(_win, 0, 0);
	mvwprintw(_win,1,1, "%s", _comando.c_str() );
	keypad(_win, TRUE);
	wrefresh(_win);
	return _win;
}

WINDOW * key_backspace( WINDOW *  _win )
{
	int y,x;
	getyx( _win,y,x);
	mvwdelch(_win,y,x-1);
	mvwdelch(_win,y,x-2);
	mvwdelch(_win,y,x-3);	
	wrefresh(_win);
}

WINDOW* scrolling( WINDOW* _w,  elis & _et, const std::string & _tipo )
{
	// Verifica se tem linha atual.
	if( _et.linha_atual() != 0 )
	{
		int /*quociente*/q, /*resto*/r;

		// Verifica a operação.
		if( _tipo == "subir" )
		{
			q = (_et.linha_atual() - 1) / (LINES - 3);
			r = (_et.linha_atual() - 1) % (LINES - 3);
		}
		else if( _tipo == "descer" )
		{
			q = (_et.linha_atual() + 1) / (LINES - 3);
			r = (_et.linha_atual() + 1) % (LINES - 3);
			// Verifica se a operação descer vai fazer a linha seguinte bater no menu.
			// e se não é uma lista vazia.
			if( r == 0 && q >= 1 )
			{
				_et.modify( _et.linha_atual() + 1);

				_w = imprimir_linhas(_w, _et);
				/*
				// Diferença entre a quantidade de linhas na memoria e a linha atual.
				int limite = _et.size() - _et.linha_atual() + 1;
				// Verifica se a diferença é maior que quantidade de linhas que a tela pode imprimir.
				if( limite > LINES - 3) limite = LINES - 3;

				for( int i = _et.linha_atual() + 1; i <= limite; ++i )
				{
					if( i == _et.linha_atual() + 1)
					{
						// Imprimi em ordem
						mvwprintw(_w, _et.linha_atual() + 1 - i, 0, "%d> %s", i, _et.get_row(i) );
					}
					else mvwprintw(_w, _et.linha_atual() + 1 - i, 0, "%d  %s", i, _et.get_row(i) );
				} 
				wrefresh(_w);
				*/
				
			}
		}

	}

	return _w;
}

WINDOW* imprimir_linhas( WINDOW * _w, elis & _et )
{

	// Em qual tela o linha atual está
	int la= _et.linha_atual() / (LINES - 3);
	// Em qual tela a ultima linha está
	int ul = _et.size() / (LINES - 3);

	// Verifica se estão em telas diferentes.
	// linha atual nunca é maior que ultima linha
	if(ul > la)
	{
		// ul será usado no for como if( strlimite.
		// ul é posicionado na ultima linha da tela.
		ul = (LINES - 3) * (la + 1);
	}
	else ul = _et.size();

	wclear(_w);

	int j = 0;
	// Percorre todas as linhas dessa tela.
	for (int i = la + 1; i <= ul; ++i)
	{
		if( i == _et.linha_atual() )
		{
			mvwprintw(_w, j, 0, "%d> %s", i, _et.get_row(i).c_str() );
		}
		else
		{
			mvwprintw(_w, j, 0, "%d  %s", i, _et.get_row(i).c_str() );								
		}
		++j;
	}
	wrefresh( _w );
	return _w;
}