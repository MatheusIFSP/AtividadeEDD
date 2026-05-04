#include <iostream>
#include <string>
using namespace std;

// -----------------------------------------
//  Estrutura do nó da lista
// -----------------------------------------
struct Funcionario
{
    int    prontuario;
    string nome;
    double salario;
    Funcionario* prox;
};

// -----------------------------------------
//  Inicializa a lista vazia
// -----------------------------------------
Funcionario* init()
{
    return NULL;
}

// -----------------------------------------
//  Verifica se a lista está vazia
// -----------------------------------------
int isEmpty(Funcionario* lista)
{
    return (lista == NULL);
}

// -----------------------------------------
//  Busca um funcionário pelo prontuário
//  Retorna o ponteiro do nó ou NULL
// -----------------------------------------
Funcionario* find(Funcionario* lista, int prontuario)
{
    Funcionario* aux = lista;
    while (aux != NULL && aux->prontuario != prontuario)
    {
        aux = aux->prox;
    }
    return aux;
}

// -----------------------------------------
//  Inclui um novo funcionário na lista
//  Retorna a lista atualizada
// -----------------------------------------
Funcionario* insert(Funcionario* lista, int prontuario,
                    const string& nome, double salario)
{
    // Observação (a): prontuário duplicado não é permitido
    if (find(lista, prontuario) != NULL)
    {
        cout << "ERRO: já existe funcionario com prontuario "
             << prontuario << "." << endl;
        return lista;
    }

    Funcionario* novo = new Funcionario();
    novo->prontuario  = prontuario;
    novo->nome        = nome;
    novo->salario     = salario;
    novo->prox        = lista;   // insere no início
    return novo;
}

// -----------------------------------------
//  Remove um funcionário pelo prontuário
//  Retorna a lista atualizada
// -----------------------------------------
Funcionario* removeFunc(Funcionario* lista, int prontuario)
{
    Funcionario* ant = NULL;
    Funcionario* aux = lista;

    while (aux != NULL && aux->prontuario != prontuario)
    {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL)
    {
        cout << "Funcionario com prontuario " << prontuario
             << " nao encontrado." << endl;
        return lista;
    }

    if (ant == NULL)          // era o primeiro nó
        lista = aux->prox;
    else                      // estava no meio ou no fim
        ant->prox = aux->prox;

    cout << "Funcionario \"" << aux->nome << "\" removido com sucesso." << endl;
    delete aux;
    return lista;
}

// -----------------------------------------
//  Pesquisa e exibe um funcionário
// -----------------------------------------
void search(Funcionario* lista, int prontuario)
{
    Funcionario* encontrado = find(lista, prontuario);

    if (encontrado == NULL)
    {
        cout << "Funcionário com prontuário " << prontuario
             << " não encontrado." << endl;
        return;
    }

    cout << "------------------------------" << endl;
    cout << "Prontuario : " << encontrado->prontuario << endl;
    cout << "Nome       : " << encontrado->nome       << endl;
    cout << "Salario    : R$ " << encontrado->salario  << endl;
    cout << "------------------------------" << endl;
}

// -----------------------------------------
//  Lista todos os funcionários e o total
// -----------------------------------------
void printAll(Funcionario* lista)
{
    if (isEmpty(lista))
    {
        cout << "Nenhum funcionário cadastrado." << endl;
        return;
    }

    double total = 0.0;
    Funcionario* aux = lista;

    cout << "==============================" << endl;
    cout << " LISTA DE FUNCIONARIOS"         << endl;
    cout << "==============================" << endl;

    while (aux != NULL)
    {
        cout << "Prontuario : " << aux->prontuario << endl;
        cout << "Nome       : " << aux->nome       << endl;
        cout << "Salario    : R$ " << aux->salario  << endl;
        cout << "------------------------------" << endl;
        total += aux->salario;
        aux = aux->prox;
    }

    cout << "TOTAL DOS SALARIOS: R$ " << total << endl;
    cout << "==============================" << endl;
}

// -----------------------------------------
//  Libera toda a memória da lista
// -----------------------------------------
void freeList(Funcionario* lista)
{
    Funcionario* aux = lista;
    while (aux != NULL)
    {
        Funcionario* prox = aux->prox;
        delete aux;
        aux = prox;
    }
}

// -----------------------------------------
//  Exibe o menu e retorna a opção
// -----------------------------------------
int menu()
{
    int opcao;
    cout << endl;
    cout << "=============================" << endl;
    cout << "   GESTAO DE FUNCIONARIOS"     << endl;
    cout << "=============================" << endl;
    cout << "  0. Sair"                     << endl;
    cout << "  1. Incluir"                  << endl;
    cout << "  2. Excluir"                  << endl;
    cout << "  3. Pesquisar"                << endl;
    cout << "  4. Listar"                   << endl;
    cout << "=============================" << endl;
    cout << "Opção: ";
    cin  >> opcao;
    cin.ignore();   // descarta o '\n' que sobra no buffer
    return opcao;
}

// -----------------------------------------
//  Programa principal
// -----------------------------------------
int main()
{
    Funcionario* lista = init();
    int opcao;

    do
    {
        opcao = menu();

        switch (opcao)
        {
            // -- Incluir ------------------
            case 1:
            {
                int    prontuario;
                string nome;
                double salario;

                cout << "Prontuario : ";
                cin  >> prontuario;
                cin.ignore();

                cout << "Nome       : ";
                getline(cin, nome);

                cout << "Salário    : ";
                cin  >> salario;
                cin.ignore();

                lista = insert(lista, prontuario, nome, salario);
                break;
            }

            // -- Excluir ------------------
            case 2:
            {
                int prontuario;
                cout << "Prontuario a excluir: ";
                cin  >> prontuario;
                cin.ignore();

                lista = removeFunc(lista, prontuario);
                break;
            }

            // -- Pesquisar -----------------
            case 3:
            {
                int prontuario;
                cout << "Prontuario a pesquisar: ";
                cin  >> prontuario;
                cin.ignore();

                search(lista, prontuario);
                break;
            }

            // -- Listar -------------------
            case 4:
                printAll(lista);
                break;

            // -- Sair ---------------------
            case 0:
                cout << "Encerrando o programa..." << endl;
                break;

            // -- Opção inválida ------------
            default:
                cout << "Opção invalida. Tente novamente." << endl;
        }

    } while (opcao != 0);

    freeList(lista);
    return 0;
}