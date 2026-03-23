#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char** argv)
{
    const int fileiras = 15;
    const int poltronas = 40;
    int mapa[fileiras][poltronas] = {0};
    
    int opcao = -1;
    
    while(opcao != 0)
    {
        cout << "\n----------------------------" << endl;
        cout << "      PROJETO BILHETERIA    " << endl;
        cout << "----------------------------" << endl;
        cout << "0. Finalizar" << endl;
        cout << "1. Reservar poltrona" << endl;
        cout << "2. Mapa de ocupacao" << endl;
        cout << "3. Faturamento" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        
        if (opcao == 1) { 
            int f, p;
            cout << "\n--- RESERVA ---" << endl;
            cout << "Informe a fileira (1 a 15): ";
            cin >> f;
            cout << "Informe a poltrona (1 a 40): ";
            cin >> p;
            
            if (f >= 1 && f <= 15 && p >= 1 && p <= 40) {
                if (mapa[f-1][p-1] == 0) {
                    mapa[f-1][p-1] = 1; 
                    cout << "Reserva confirmada!" << endl;
                } else {
                    cout << "Este lugar ja esta reservado" << endl;
                }
            } else {
                cout << "Posicao invalida!" << endl;
            }
        } 
        else if(opcao == 2) { 
            cout << "\nMapa de ocupacao do Teatro" << endl;
            for (int i = 0; i < fileiras; i++) {
                cout << "F" << (i + 1 < 10 ? "0" : "") << i + 1 << " ";
                for (int j = 0; j < poltronas; j++) {
                    if (mapa[i][j] == 0) cout << ".";
                    else cout << "#";
                }
                cout << endl;
            }
            cout << "Legenda: [.] Vago | [#] Ocupado" << endl;
        } 
        else if(opcao == 3) {
            int ocupados = 0;
            double faturamento = 0.0;
            
            for(int i = 0; i < fileiras; i++) { // Corrigido int i = 0
                for (int j = 0; j < poltronas; j++) {
                    if (mapa[i][j] == 1) {
                        ocupados++;
                        if (i + 1 <= 5) faturamento += 50.00;
                        else if(i + 1 <= 10) faturamento += 30.00;
                        else faturamento += 15.00;
                    }
                }
            }
            cout << "\n--- RELATORIO DE FATURAMENTO ---" << endl;
            cout << "Qtde de lugares ocupados: " << ocupados << endl;
            cout << fixed << setprecision(2);
            cout << "Valor da bilheteria: R$ " << faturamento << endl;
        } 
        else if(opcao != 0) {
            cout << "Opcao invalida! Tente novamente." << endl;
        }   
    }
    return 0;
}