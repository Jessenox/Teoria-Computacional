#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

void colocar(int, ofstream *);
void menu(ofstream *);

int main(int argc, char const *argv[]) {
    bool z = false;
    ofstream f;
    menu(&f);
    return 0;
}

void menu(ofstream * f){
	short int opc, n;
	bool end = false;
	while(!end){
		cout << "Elige la opcion correspondiente: " << endl;
		cout << "1.- Elegir valor de n" << endl;
		cout << "2.- Elegir valor de n automaticamente" << endl;
		cout << "3.- Salir" << endl;
		cin >> opc;
		switch(opc){
			case 1:
				(*f).open("tmp.txt");
				*f << "\u03A3" << "^" << n << " = ";
				cout << "Coloque el valor de n entre 1 y 1000: " << endl;
				cin >> n;
				if(n > 1000){
					cout << "Ingrese un valor valido" << endl;
					break;
				} else {
					for (int i = 0; i < n + 1; i++)
						colocar(i, f);
					*f << '}';			
					(*f).close();
				}
				system("cls");
			break;
			case 2:
				(*f).open("tmp.txt");
				*f << "\u03A3" << "^" << n << " = ";
				short int opc = rand()%1000;
				cout << "Se eligio " << n << endl;
				for (int i = 0; i < n + 1; i++)
						colocar(i, f);
				*f << '}';			
				(*f).close();
			break;
			case 3:
				end = true;
			break;
		}
	}
}

void colocar(int n, ofstream * fil){
    double u = pow(2,n);
    double m = (u/2), v = u-1;
    double * s = new double[n];
    double * o = new double[n];
    //Obtener cantidad de ceros
    for (int i = 0; i < n; i++){
        s[i] = m;
        o[i] = s[i];
        m /= 2;   
    }
    //Colocar ceros y unos
    if (n == 0) {
        *fil << '{' << "\u03B5";
    } else 
    for (double i = 0; i < u; i++){
        *fil << ',';
        for (double j = 0;  j < n; j++) {
            //Colocar 0
            if (s[(int)j] > 0) {
                *fil << '0';
                s[(int)j] -= 1;
            } else  if (s[(int)j] <= 0 && (s[(int)j] + o[(int)j]) != 0) {
                *fil << '1';
                s[(int)j] -= 1;
            }
            if ((s[(int)j] + o[(int)j]) == 0) {
                s[(int)j] = o[(int)j];
            }
        }
    }
	delete[] s;
	delete[] o;
}
