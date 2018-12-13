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
		// Modo commmand
		if( com == 58 )
		{
			win = mod_jan_com(win, "~ COMMAND ~: ");
			// Torna as letras visiveis
			echo();
			// Armazena a linha de comando.
			char cstr[COLS];
			// Reseta a posição do curso da janela de comandos.
			wmove(win, 1, 14);
			// torna visivel o cursor.
			curs_set(1);
			wrefresh(win);
			
			
			while( wgetstr(win,cstr) )
			{

			}	
		}
		// Modo insert
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
					printw("%d   %s", editor_texto.linha_atual(), str.c_str() );
					str.clear();
					move(editor_texto.linha_atual() % (LINES - 3) , 0 );
					stdscr = scrolling( stdscr, editor_texto, "descer" );
					win = mod_jan_com(win, "~ INSERT ~ ");
				}
				// Verifica se <backspace> foi digitado.
				else if( v == BACKSPACE )
				{
					if( !str.empty() )
					{
						str.pop_back();	
						stdscr = key_backspace(stdscr);
						getyx(stdscr,y,x);
						move(y,x);					
					}
					
								
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
					// arquivos da memoria;
					wclear(stdscr);
					win = mod_jan_com(win, "~ NORMAL ~");
					
					// Verifica se o tamanho do arquivo na memoria é
					// maior que a capacidade de linhas.
					int qlin = editor_texto.size();;
					if( qlin >= LINES - 3) qlin = LINES - 4;
					// Percorre todas as linhas inseridas na memoria.
					for (int i = 0; i < qlin; ++i)
					{
						if( i + 1 == editor_texto.linha_atual() )
						{
							mvwprintw(stdscr, i, 0, "%d> %s", i + 1, editor_texto.get_row(i + 1).c_str() );
						}
						else
						{
							mvwprintw(stdscr, i, 0, "%d  %s", i + 1, editor_texto.get_row(i + 1).c_str() );								
						}
					}
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
					// arquivos da memoria;
					wclear(stdscr);
					win = mod_jan_com(win, "~ NORMAL ~");
					
					// Verifica se o tamanho do arquivo na memoria é
					// maior que a capacidade de linhas.
					int qlin = editor_texto.size();;
					if( qlin >= LINES - 3) qlin = LINES - 4;

					// Percorre todas as linhas inseridas na memoria.
					for (int i = 0; i < qlin; ++i)
					{
						if( i + 1 == editor_texto.linha_atual() )
						{
							mvwprintw(stdscr, i, 0, "%d> %s", i + 1, editor_texto.get_row(i + 1).c_str() );
						}
						else
						{
							mvwprintw(stdscr, i, 0, "%d  %s", i + 1, editor_texto.get_row(i + 1).c_str() );								
						}
					}
					refresh();
					str.clear();
			}	

			noecho();
			curs_set(0);
			move(editor_texto.linha_atual(),0);
			win = mod_jan_com(win, "~ NORMAL ~");
			editor_texto.write("doc/corno.txt");
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
				wclear(_w);
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
				_et.modify( _et.linha_atual() + 1);
			}
		}

	}

	return _w;
}