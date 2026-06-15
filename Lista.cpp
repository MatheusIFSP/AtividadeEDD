#include <iostream>
using namespace std;

const int MAX = 100;

// ===================== FILA EM PONTEIRO (LISTA ENCADEADA) =====================

struct No {
    int senha;
    No *prox;
};

struct FilaPonteiro {
    No *inicio;
    No *fim;
    int tamanho;
};

void inicializarFilaPonteiro(FilaPonteiro &f) {
    f.inicio = NULL;
    f.fim = NULL;
    f.tamanho = 0;
}

void enfileirarPonteiro(FilaPonteiro &f, int valor) {
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

int desenfileirarPonteiro(FilaPonteiro &f) {
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

// ===================== FILA EM VETOR =====================

struct FilaVetor {
    int dados[MAX];
    int inicio;
    int fim;
    int tamanho;
};

void inicializarFilaVetor(FilaVetor &f) {
    f.inicio = 0;
    f.fim = 0;
    f.tamanho = 0;
}

void enfileirarVetor(FilaVetor &f, int valor) {
    if (f.tamanho == MAX) {
        cout << "Fila cheia!" << endl;
        return;
    }

    f.dados[f.fim] = valor;
    f.fim = (f.fim + 1) % MAX;
    f.tamanho++;
}

int desenfileirarVetor(FilaVetor &f) {
    if (f.tamanho == 0) {
        return -1;
    }

    int valor = f.dados[f.inicio];
    f.inicio = (f.inicio + 1) % MAX;
    f.tamanho--;
    return valor;
}

// ===================== PROGRAMA PRINCIPAL =====================

int main() {

    FilaPonteiro senhasGeradasPtr;
    FilaPonteiro senhasAtendidasPtr;
    inicializarFilaPonteiro(senhasGeradasPtr);
    inicializarFilaPonteiro(senhasAtendidasPtr);

    FilaVetor senhasGeradasVet;
    FilaVetor senhasAtendidasVet;
    inicializarFilaVetor(senhasGeradasVet);
    inicializarFilaVetor(senhasAtendidasVet);

    int controleSenhas = 0;
    int opcao;

    do {
        cout << "\n===== ATENDIMENTO =====" << endl;
        cout << "Senhas aguardando atendimento (ponteiro): " << senhasGeradasPtr.tamanho << endl;
        cout << "Senhas aguardando atendimento (vetor):    " << senhasGeradasVet.tamanho << endl;
        cout << "0. Sair" << endl;
        cout << "1. Gerar senha" << endl;
        cout << "2. Realizar atendimento" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 0:
                if (senhasGeradasPtr.tamanho > 0 || senhasGeradasVet.tamanho > 0) {
                    cout << "\nNao e possivel encerrar. Ainda existem senhas aguardando atendimento!" << endl;
                } else {
                    cout << "\nEncerrando o sistema..." << endl;
                    cout << "Total de senhas atendidas (ponteiro): " << senhasAtendidasPtr.tamanho << endl;
                    cout << "Total de senhas atendidas (vetor):    " << senhasAtendidasVet.tamanho << endl;
                }
                break;

            case 1:
                controleSenhas++;
                enfileirarPonteiro(senhasGeradasPtr, controleSenhas);
                enfileirarVetor(senhasGeradasVet, controleSenhas);
                cout << "\nSenha " << controleSenhas << " gerada com sucesso!" << endl;
                break;

            case 2:
                if (senhasGeradasPtr.tamanho == 0 || senhasGeradasVet.tamanho == 0) {
                    cout << "\nNao ha senhas para atendimento." << endl;
                } else {
                    int senhaPtr = desenfileirarPonteiro(senhasGeradasPtr);
                    enfileirarPonteiro(senhasAtendidasPtr, senhaPtr);

                    int senhaVet = desenfileirarVetor(senhasGeradasVet);
                    enfileirarVetor(senhasAtendidasVet, senhaVet);

                    cout << "\nAtendendo senha: " << senhaPtr << endl;
                }
                break;

            default:
                cout << "\nOpcao invalida!" << endl;
                break;
        }

    } while (opcao != 0 || senhasGeradasPtr.tamanho > 0 || senhasGeradasVet.tamanho > 0);

    return 0;
}