# 1. SOBRE O PROJETO

Esse projeto tem a implementa de um editor de texto, o ELIS(Editor de LInha Simples), baseado nos antigos editores em prompt de comando e foi desenvolvido com o auxilia da biblioteca [ncurses](ftp://ftp.gnu.org/gnu/ncurses), que facilita a captura e a exibição em um terminal.
Para a organização dos dados foi utilizado a estrutura de dados Hash Table por Chaining. Foi escolhida por ter um bons tempos em termo de busca e edição dos dados armazenados em comparações à outras estruturas de dados.

# 2. MODOS FUNCIONAIS

Aos precionar as seguintes teclas quando o editor estiver no modo ~ NORMAL ~ , o editor muda para os modos a seguir:

## 1. MODO EDIÇÃO (comando <i> ou <I>)
	Ativa o modo edição ~ INSERT ~. Nesse modo é possivel entrar com textos  para compor uma linha.
	1. Ao pressionar <ENTER>, a linha atual é salva e o cursor vai para proximo linha.
	2. AO pressionar <ESC>, a linha atual é salva e editor volta par ao modo ~ NORMAL ~
## 2. MODO COMANDO (comando <:>)
	Ativa o modo comando ~ COMMAND ~:. No modo comando é possivel invocar qualquer um dos comandos abaixo>
	<w ou W>. Write: w [<name>] - Salva os no arquivo [<name>].
	<o ou O>. Open o [<name>] - Abre arquivo [<name>] e carrega as informações na tela.
	<i ou I>. Insert: i [n] - Entra no modo edição (abre um tela preta para inserir a informação, salva ao pressionar <ENTER ou ESC>) e insere uma informação antes da linha n.
	<a ou A>. Append: a [n] - Entra no modo edição abre um tela preta para inserir a informação, salva ao pressionar <ENTER ou ESC>) e insere uma informação depois da linha n.
	<m ou M>. Modify: m [n] - Muda o cursor para a linha n.
	<d ou D>. Delete: d [n] [m] - Deleta as informações da linha n até m.
	<c ou C>. Copy: c [n] [m] - Copia par o buffer as informações de n até m.
	<p ou P>. Paste: p [n] - Cola (inserindo) as linhas atualmentes no buffer depois da linha n.
## 3. NAVEGAR PARA CIMA (comando <k> ou <K>)
	Navega o cursos para cima.
## 4. NAVEGAR PARA BAIXO (comando <j> ou <J>)
	Navega o cursos para baixo.

# 3. INSTALANDO O NCURSES EM SUA MAQUINA

1. Faça Download do [NCURSES 6.1](ftp://ftp.gnu.org/gnu/ncurses/ncurses-6.0.tar.gz).
2. Unzip no arquivo ncurses-6.1.tar.gz ```tar zxvf ncurses<version>.tar.gz```.
3. Entra na pasta ncurses-6.1
4. Use  ```./configure``` para configurar o ambiente build e utilize o comando  ```make```.
5. Use o comando ```sudo su``` para virar o super-usuario e execute o comando ```make install```.
6. Para sair do modo su, aperte CTRL + D.

# 4. COMPILANDO E EXECUTANDO O ELIS

1. Para compilar, utilize o comando ```make args="-lncurses"``` dentro da pasta ELIS.
2. Para exercutar, utilize o comando ```./bin/main``` dentro da pasta ELIS.

# 5. SOBRE O MAKEFILE

Verifica se o setup está configurado, caso contrario, fará um novo setup chamando "make dir" e compila. Ele chama "make all" internamente.

```
make
```

Você também pode passar argumentos para o compilador. Como o exemplo abaixo:
```
make args="-D something=212"
```
Para ativar o modo debug, faça:

```
make args="-D DEBUG"
```

Fará tods os diretórios de trabalho. Você pode fazer isso manualmente ou automaticamente se você usar "make".
```
make dir
```

Limpa todo o diretorio de trabalho, irá apagar todos os arquivos contidos em bin e docs
```
make clean
```

Fará a documentação para o projeto atual.
```
make doxy
```

Irá chamar "make clear" e "make dir"
```
make fresh
```
