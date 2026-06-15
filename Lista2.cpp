#include <iostream>
using namespace std;

// ===================== FILA EM PONTEIRO (LISTA ENCADEADA) =====================

struct No {
    int senha;
    No *prox;
};

struct Fila {
    No *inicio;
    No *fim;
    int tamanho;
};

void inicializarFila(Fila &f) {
    f.inicio = NULL;
    f.fim = NULL;
    f.tamanho = 0;
}

void enfileirar(Fila &f, int valor) {
    No *novo = new No;
    novo->senha = valor;
    novo->prox = NULL;

    if (f.fim == NULL) {
        f.inicio = novo;
        f.fim = novo;
    } else {
        f.fim->prox = novo;
        f.fim = novo;
    }
    f.tamanho++;
}

int desenfileirar(Fila &f) {
    if (f.inicio == NULL) {
        return -1;
    }

    No *temp = f.inicio;
    int valor = temp->senha;

    f.inicio = f.inicio->prox;
    if (f.inicio == NULL) {
        f.fim = NULL;
    }

    delete temp;
    f.tamanho--;
    return valor;
}

// ===================== GUICHE E LISTA DE GUICHES (PONTEIRO) =====================

struct Guiche {
    int id;
    Fila senhasAtendidas;
    Guiche *prox;
};

struct ListaGuiches {
    Guiche *inicio;
    int quantidade;
};

void inicializarListaGuiches(ListaGuiches &l) {
    l.inicio = NULL;
    l.quantidade = 0;
}

void abrirGuiche(ListaGuiches &l, int id) {
    Guiche *novo = new Guiche;
    novo->id = id;
    inicializarFila(novo->senhasAtendidas);
    novo->prox = NULL;

    if (l.inicio == NULL) {
        l.inicio = novo;
    } else {
        Guiche *atual = l.inicio;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
    l.quantidade++;
}

Guiche* buscarGuiche(ListaGuiches &l, int id) {
    Guiche *atual = l.inicio;
    while (atual != NULL) {
        if (atual->id == id) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void listarSenhasGuiche(ListaGuiches &l, int id) {
    Guiche *g = buscarGuiche(l, id);

    if (g == NULL) {
        cout << "\nGuiche " << id << " nao encontrado." << endl;
        return;
    }

    if (g->senhasAtendidas.tamanho == 0) {
        cout << "\nO guiche " << id << " ainda nao atendeu nenhuma senha." << endl;
        return;
    }

    cout << "\nSenhas atendidas pelo guiche " << id << ":" << endl;
    No *atual = g->senhasAtendidas.inicio;
    while (atual != NULL) {
        cout << "- Senha " << atual->senha << endl;
        atual = atual->prox;
    }
}

// ===================== PROGRAMA PRINCIPAL =====================

int main() {
    Fila senhasGeradas;
    inicializarFila(senhasGeradas);

    ListaGuiches guiches;
    inicializarListaGuiches(guiches);

    int controleSenhas = 0;
    int totalAtendidas = 0;
    int opcao;

    do {
        cout << "\n===== ATENDIMENTO 2.0 =====" << endl;
        cout << "Senhas aguardando atendimento: " << senhasGeradas.tamanho << endl;
        cout << "Guiches abertos: " << guiches.quantidade << endl;
        cout << "0. Sair" << endl;
        cout << "1. Gerar senha" << endl;
        cout << "2. Abrir guiche" << endl;
        cout << "3. Realizar atendimento" << endl;
        cout << "4. Listar senhas atendidas" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 0:
                if (senhasGeradas.tamanho > 0) {
                    cout << "\nNao e possivel encerrar. Ainda existem senhas aguardando atendimento!" << endl;
                } else {
                    cout << "\nEncerrando o sistema..." << endl;
                    cout << "Total de senhas atendidas: " << totalAtendidas << endl;
                }
                break;

            case 1:
                controleSenhas++;
                enfileirar(senhasGeradas, controleSenhas);
                cout << "\nSenha " << controleSenhas << " gerada com sucesso!" << endl;
                break;

            case 2: {
                int idGuiche;
                cout << "\nDigite o id do guiche: ";
                cin >> idGuiche;

                if (buscarGuiche(guiches, idGuiche) != NULL) {
                    cout << "\nJa existe um guiche com esse id." << endl;
                } else {
                    abrirGuiche(guiches, idGuiche);
                    cout << "\nGuiche " << idGuiche << " aberto com sucesso!" << endl;
                }
                break;
            }

            case 3: {
                if (senhasGeradas.tamanho == 0) {
                    cout << "\nNao ha senhas para atendimento." << endl;
                    break;
                }

                if (guiches.quantidade == 0) {
                    cout << "\nNao ha guiches abertos para atendimento." << endl;
                    break;
                }

                int idGuiche;
                cout << "\nDigite o id do guiche que esta chamando: ";
                cin >> idGuiche;

                Guiche *g = buscarGuiche(guiches, idGuiche);

                if (g == NULL) {
                    cout << "\nGuiche " << idGuiche << " nao encontrado." << endl;
                } else {
                    int senhaAtual = desenfileirar(senhasGeradas);
                    enfileirar(g->senhasAtendidas, senhaAtual);
                    totalAtendidas++;
                    cout << "\nGuiche " << idGuiche << " atendendo senha: " << senhaAtual << endl;
                }
                break;
            }

            case 4: {
                int idGuiche;
                cout << "\nDigite o id do guiche: ";
                cin >> idGuiche;
                listarSenhasGuiche(guiches, idGuiche);
                break;
            }

            default:
                cout << "\nOpcao invalida!" << endl;
                break;
        }

    } while (opcao != 0 || senhasGeradas.tamanho > 0);

    return 0;
}