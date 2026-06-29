#include <iostream>

using namespace std;

void print(int t, int *a) {
    for(int i=0; i<t; ++i) {
        cout << "Elemento: " << i << " = " << a[i] << endl;
    }
    cout << "-----------------" << endl;
}

void sort_insertion(int t, int *a) {
    int aux, j;
    for(int i=1; i<t; ++i) {
        aux = a[i];
        j = i - 1;
        while(j >= 0 && a[j] > aux) {
            a[j+1] = a[j];
            --j;
        }
        a[j+1] = aux;
    }
}

int main(int argc, char** argv)
{
    int v[] = {49, 38, 58, 87, 34, 93, 26, 13};
    int t = sizeof(v) / sizeof(v[0]);

    print(t, v);
    sort_insertion(t, v);
    print(t, v);

    return 0;
}
