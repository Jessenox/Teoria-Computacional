#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
#include <winbgim.h>

using namespace std;

void insercion(string * cad);
void insercionA(string * cad);
void turing(string cadena, string * resultado, int);
void ventana();
void dibujarCadena(string);
void cabezal(int);

int main(){
	int g = 0;
    srand(time(NULL));
    string cadena, resultante;
    char opc;
    cout << "Modo: " << endl;
    cout<< "(1) Manual" << endl;
    cout<< "(2) Automatico" << endl;
    cin >> opc;
    if (opc == '1') {
        insercion(&cadena);
        cout << "Cadena origen: "<<  cadena << endl;
        if(cadena.size() - 3 <= 10 ){
        	g=1;
        	ventana();
        	turing(cadena, &resultante, g);
		}
        else
			turing(cadena, &resultante,0);
    } else {
        insercionA(&cadena);
        cout << "Cadena origen: "<<  cadena << endl;
        turing(cadena, &resultante,0);
    }
    cout << "Cadena resultante: "<< resultante << endl;
    if(g == 1){
	    while(!kbhit())delay(300);
	    closegraph();
	}
}

void insercion(string * cad){
    int n, m;
    string aux, aux2;
    cout << "Inserte n:" << endl;
    cin >> n;
    cout << "Inserte m:" << endl;
    cin >> m;
    for (int i = 0; i < n; i++)
        aux += '|';
    for (int i = 0; i < m; i++)
        aux2 += '|';
    (*cad) = "*"+ aux + "*" + aux2 + "*";
}

void insercionA(string * cad){
    int n = rand() % 50 + 1, m = rand() % 50 + 1;
    string aux, aux2;
    while(n+m>50)
    	n = rand() % 50 + 1, m = rand() % 50 + 1;
    cout << "n: " << n << ", m: " << m << endl;
    for (int i = 0; i < n; i++)
        aux += '|';
    for (int i = 0; i < m; i++)
        aux2 += '|';
    (*cad) = "*"+ aux + "*" + aux2 + "*";
}


void turing(string cadena, string * resultado, int g){
    string cadCopia, cadPantalla;
    ofstream file;
    file.open("Salida.txt");
    char estado = '1', fin = 0;
    
    int i = 0;
    while (!fin){
        cadCopia = cadena;
        cadPantalla = cadena;
        if (i-1 < 0)
            cadCopia = 'q' + cadena;
        else 
            cadCopia.insert(i-1, "q");
        cadCopia += " \u22A6 ";
        file << cadCopia;
        
        switch (estado) {
            case '1':
                switch (cadena[i]) {
                    case '*':
                        cadena[i] = 'X';
                        i++;
                        estado = '2';
                        
                    break;
                        cout << "fallo 1" << endl;
                        break;
                    default:
                    break;
                }
            break;
            case '2':
                switch (cadena[i]) {
                    case '*':
                        i++;
                        estado = '3';
                    break;
                    case '|':
                        i++;
                        estado = '2';
                    break;
                    default:
                        cout << "fallo 2" << endl;
                        break;
                    break;
                }
            break;
            case '3':
                switch (cadena[i]) {
                    case '*':
                        cadena[i] = 'X';
                        i--;
                        estado = '4';
                    break;
                    case '|':
                        i++;
                        estado = '3';
                    break;
                    default:
                        cout << "fallo 3" << endl;
                        break;
                    break;
                }
            break;
            case '4':
                switch (cadena[i]) {
                    case '*':
                        i--;
                        estado = '4';
                    break;
                    case '|':
                        cadena[i] = 'a';
                        i++;
                        estado = '5';
                    break;
                    case 'X':
                        i++;
                        estado = '7';
                    break;
                    default:
                        cout << "fallo 4" << endl;
                        break;
                    break;
                }
            break;
            case '5':
                switch (cadena[i]) {
                    case '\0':
                        if(i == -1)
                            cadena = '|' + cadena;
                        else   
                            cadena += '|';
                        i--;
                        estado = '6';
                    break;
                    case '*':
                        i++;
                        estado = '5';
                    break;
                    case '|':
                        i++;
                        estado = '5';
                    break;
                    case 'X':
                        i++;
                        estado = '5';
                    break;
                    default:
                        cout << "fallo 5" << endl;
                        break;
                    break;
                }
            break;
            case '6':
                switch (cadena[i]) {
                    case '*':
                        i--;
                        estado = '6';
                    break;
                    case '|':
                        i--;
                        estado = '6';
                    break;
                    case 'a':
                        cadena[i] = '|';
                        i--;
                        estado = '4';
                    break;
                    case 'X':
                        i--;
                        estado = '6';
                    break;
                    default:
                        cout << "fallo 6" << endl;
                        break;
                    break;
                }
            break;
            case '7':
                switch (cadena[i]) {
                    case '*':
                        i++;
                        estado = '8';
                    break;
                    case '|':
                        i++;
                        estado = '7';
                    break;
                    default:
                        cout << "fallo 7" << endl;
                        break;
                    break;
                }
            break;
            case '8':
                switch (cadena[i]) {
                    case '\0':
                        if(i == -1)
                            cadena = '*' + cadena;
                        else   
                            cadena += '*';
                        i--;
                        estado = '9';
                    break;
                    case '|':
                        i++;
                        estado = '8';
                    break;
                    case 'X':
                        cadena[i] = '*';
                        i++;
                        estado = '8';
                    break;
                    default:
                        cout << "fallo 8" << endl;
                        break;
                    break;
                }
            break;
            case '9':
                switch (cadena[i]) {
                    case '*':
                        i--;
                        estado = '9';
                    break;
                    case '|':
                        i--;
                        estado = '9';
                    break;
                    case 'X':
                        cadena[i] = '*';
                        estado = '9';
                        (*resultado) = cadena;
                        fin = 1;
                        cadCopia = cadena;
                        if (i-1 < 0)
                            cadCopia = 'q' + cadena;
                        else 
                            cadCopia.insert(i-1, "q");
                        file << cadCopia;
                    break;
                    default:
                        cout << "fallo 9" << endl;
                        break;
                    break;
                }
            break;
        }   
        if(g == 1){
			dibujarCadena(cadena); 
			cabezal(i);
		}
    }   
    file.close();
}

void ventana(){
	initwindow(1000,700);
	setbkcolor(0);
	cleardevice();
}

void dibujarCadena(string cadena){
	cleardevice();
	setcolor(15);
	settextstyle(3,0,4);
	int n = cadena.size();
	char texto[n-1];
	strcpy(texto,cadena.c_str());
	for(int i = 0; i < n; i++){
		char txt[2];
		txt[0] = NULL;
		txt[0] = texto[i];
		outtextxy(50+30*i,300,txt);	
	}
}

void cabezal(int x){
	int points[8] = {50+30*x, 230, 80+30*x,  230, 80+30*x, 260, 50+30*x,260};
	setfillstyle(1,BLUE);
	fillpoly(4, points);
	moveto(65+30*x,260);
	lineto(65+30*x,280);
	moveto(65+30*x,280);
	lineto(63+30*x,275);
	lineto(67+30*x,275);
	delay(500);
}
