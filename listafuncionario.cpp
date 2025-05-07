#include <iostream>
#include <locale.h>
using namespace std;

/*
Nome: Guilherme Mendes de Sousa
Prontuario: CB3030857
*/
struct Funcionario {
	int prontuario;
	string nome;
	double salario;	
};

struct ListaFuncionarios {
	Funcionario* funcionario;
	ListaFuncionarios* ant;	
};

ListaFuncionarios* init() {
	return NULL;
}
ListaFuncionarios* incluir (ListaFuncionarios* lista, Funcionario* func) {
	ListaFuncionarios* novoFunc = new ListaFuncionarios();
	novoFunc->funcionario = func;
	novoFunc->ant = lista;
	return novoFunc;
}

ListaFuncionarios* remover (ListaFuncionarios* lista, int prontuario) {
	ListaFuncionarios* aux = lista;
	ListaFuncionarios* apoio = NULL;
	while (aux != NULL && aux->funcionario->prontuario != prontuario) {
		apoio = aux;
		aux = aux->ant;
	}
	if (aux == NULL) {
		return lista;
	}
	if (apoio == NULL) {
		lista = aux->ant;
	}
	else {
		apoio->ant = aux->ant;
	}
	free(aux);
	
	return lista;	
}

ListaFuncionarios* pesquisar (ListaFuncionarios* lista, int prontuario) {
	ListaFuncionarios* aux = lista;
	while(aux != NULL && aux->funcionario->prontuario != prontuario) {
		aux = aux->ant;
	}
	return aux;
}
void listar (ListaFuncionarios* lista) {
	ListaFuncionarios* aux = lista;
	double totalSalario = 0;
	cout << "Listando funcion�rios: " << endl << "----------------------------" << endl;
	while (aux != NULL) {
		cout << "Nome: " << aux->funcionario->nome << endl <<
		"Prontuario: " << aux->funcionario->prontuario << endl <<
		"Salario: R$" << aux->funcionario->salario << endl << "----------------------------" <<endl;
		totalSalario += aux->funcionario->salario;
		aux = aux->ant;
	}
	cout << "----------------------------" << endl <<
	"Valor total de salarios: " << totalSalario << endl;
	
	
}
int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	ListaFuncionarios *listaFunc = init();
	int seletor = 1;
	cout << "----- Gerenciamento de cadastros de funcionarios -----" << endl;
	cout << "Sumario de op��es: " << endl << "0 - finalizar execu��o. " << endl <<
	"1 - Incluir funcion�rio." << endl << "2 - Remover funcionario." << endl <<
	"3 - Pesquisar funcion�rio. " << endl << "4 - Listar e exibir total salarial. " << endl;
	while (seletor != 0) {
		cout << endl << "Selecione sua op��o: " << endl;
		cin >> seletor;
		int prontuario;
		switch(seletor) {
		case 1: {
			cout << "Informe o prontu�rio para cadastro" << endl;
			cin >> prontuario;
			cin.ignore(1000,'\n');
			while(pesquisar(listaFunc, prontuario) != NULL) {
				cout << "Prontu�rio j� cadastrado! Informe um valor v�lido. " << endl;
				cin >> prontuario;
				cin.ignore(1000,'\n');
			}
			string nome;
			cout << "Informe o nome do funcion�rio: " << endl;
			getline(cin, nome);
			double salario;
			cout << "Informe o sal�rio do funcion�rio: " << endl;
			cin >> salario;
			Funcionario* func = new Funcionario();
			func->prontuario = prontuario;
			func->nome = nome;
			func->salario = salario;
			listaFunc = incluir(listaFunc, func);
			cout << "Funcion�rio cadastrado!" << endl;
			cout << "----------------------------" << endl;
			break;
		}
		case 2: {
			cout << "Informe o prontu�rio do funcion�rio: " << endl;
			cin >> prontuario;
			if (pesquisar(listaFunc, prontuario) == NULL) {
				cout << "Funcion�rio n�o encontrado." << endl;
			} else {
				string nome = pesquisar(listaFunc, prontuario)->funcionario->nome;
				listaFunc = remover(listaFunc, prontuario);
				cout << "Funcion�rio " << nome << " removido." << endl;
			}
			cout << "----------------------------" << endl;
			break;
		}
		
		case 3: {
			cout << "Informe o prontu�rio do funcion�rio" << endl;
			cin >> prontuario;
			cin.ignore(1000, '\n');
			ListaFuncionarios *funcionarioPesquisado = pesquisar(listaFunc, prontuario);
			if (funcionarioPesquisado == NULL) {
				cout << "Funcion�rio n�o encontrado." << endl;
			}
			else {
				cout << "----------------------------" << endl << 
				funcionarioPesquisado->funcionario->prontuario << endl 
				<< "----------------------------" << endl <<
				"Nome: " << funcionarioPesquisado->funcionario->nome << endl <<
				"Salario: R$" << funcionarioPesquisado->funcionario->salario << endl;
			}
			cout << "----------------------------" << endl;
			break;
		}
		case 4: {
			listar(listaFunc);
			cout << "----------------------------" << endl;
			break;
		}
		default:
			if (seletor == 0) {
				cout << "Programa finalizado!" << endl;
				cout << "----------------------------" << endl;
			}
			else {
				cout << "Op��o inv�lida!" << endl;
				cout << "----------------------------" << endl;
			}
		}	
	}
	
	return 0;
}