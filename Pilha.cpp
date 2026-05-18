#include <iostream>
#include <climits>
using namespace std;

#define MAX_ARRAY 30

struct PilhaVetor {
    int qtde;
    int elementos[MAX_ARRAY];
};

PilhaVetor* initVetor() {
    PilhaVetor* p = new PilhaVetor();
    p->qtde = 0;
    return p;
}

int isEmptyVetor(PilhaVetor* p) {
    return (p->qtde == 0);
}

int countVetor(PilhaVetor* p) {
    return p->qtde;
}

int pushVetor(PilhaVetor* p, int v) {
    int podeEmpilhar = (p->qtde < MAX_ARRAY);
    if (podeEmpilhar) {
        p->elementos[p->qtde++] = v;
    }
    return podeEmpilhar;
}

int popVetor(PilhaVetor* p) {
    if (isEmptyVetor(p)) return -999999;
    return p->elementos[--p->qtde];
}

void freeVetor(PilhaVetor* p) {
    delete p;
}

struct No {
    int dado;
    No* ant;
};

struct PilhaLista {
    No* topo;
};

PilhaLista* initLista() {
    PilhaLista* p = new PilhaLista;
    p->topo = NULL;
    return p;
}

int isEmptyLista(PilhaLista* p) {
    return (p->topo == NULL);
}

int countLista(PilhaLista* p) {
    int i = 0;
    No* no = p->topo;
    while (no != NULL) { i++; no = no->ant; }
    return i;
}

void pushLista(PilhaLista* p, int v) {
    No* no = new No;
    no->dado = v;
    no->ant  = p->topo;
    p->topo  = no;
}

int popLista(PilhaLista* p) {
    if (isEmptyLista(p)) return -999999;
    No* no = p->topo;
    int v  = no->dado;
    p->topo = no->ant;
    delete no;
    return v;
}

void freeLista(PilhaLista* p) {
    No* no = p->topo;
    while (no != NULL) {
        No* temp = no->ant;
        delete no;
        no = temp;
    }
    delete p;
}

void cabecalho(const char* titulo) {
    cout << "\n========================================\n";
    cout << "  " << titulo << "\n";
    cout << "========================================\n";
}

void linha() {
    cout << "----------------------------------------\n";
}

void desempilharExibirVetor(PilhaVetor* p, const char* nome) {
    cout << "\n[Vetor] Desempilhando " << nome
         << " (" << countVetor(p) << " elemento(s)) — ordem decrescente:\n";
    linha();
    if (isEmptyVetor(p)) {
        cout << "  (pilha vazia)\n";
        return;
    }
    while (!isEmptyVetor(p)) {
        cout << "  " << popVetor(p) << "\n";
    }
}

void desempilharExibirLista(PilhaLista* p, const char* nome) {
    cout << "\n[Lista] Desempilhando " << nome
         << " (" << countLista(p) << " elemento(s)) — ordem decrescente:\n";
    linha();
    if (isEmptyLista(p)) {
        cout << "  (pilha vazia)\n";
        return;
    }
    while (!isEmptyLista(p)) {
        cout << "  " << popLista(p) << "\n";
    }
}

int main() {
    const int TOTAL = 30;

    PilhaVetor* paresVetor   = initVetor();
    PilhaVetor* imparesVetor = initVetor();

    PilhaLista* paresLista   = initLista();
    PilhaLista* imparesLista = initLista();

    cabecalho("ENTRADA DE DADOS — 30 inteiros em ordem crescente");
    cout << "  Cada numero deve ser MAIOR que o anterior.\n\n";

    int anterior = INT_MIN;
    int contador = 0;

    while (contador < TOTAL) {
        cout << "  [" << (contador + 1) << "/" << TOTAL << "] Digite um inteiro: ";
        int num;

        if (!(cin >> num)) {
            cout << "  Entrada invalida! Digite apenas numeros inteiros.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (num <= anterior) {
            cout << "  ERRO: " << num
                 << " nao e maior que o anterior (" << anterior
                 << "). Tente novamente.\n";
            continue;
        }

        if (num % 2 == 0) {
            pushVetor(paresVetor, num);
            pushLista(paresLista, num);
            cout << "  -> PAR empilhado.\n";
        } else {
            pushVetor(imparesVetor, num);
            pushLista(imparesLista, num);
            cout << "  -> IMPAR empilhado.\n";
        }

        anterior = num;
        contador++;
    }

    cabecalho("RESULTADO — PILHA POR VETOR");
    desempilharExibirVetor(paresVetor,   "PARES");
    desempilharExibirVetor(imparesVetor, "IMPARES");

    cabecalho("RESULTADO — PILHA POR LISTA ENCADEADA");
    desempilharExibirLista(paresLista,   "PARES");
    desempilharExibirLista(imparesLista, "IMPARES");

    cabecalho("FIM DO PROGRAMA");

    freeVetor(paresVetor);
    freeVetor(imparesVetor);
    freeLista(paresLista);
    freeLista(imparesLista);

    return 0;
}