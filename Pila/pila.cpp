#include <iostream>
#include <stack>
#include <ctime>
#include <random>
#include <fstream>
#include <winbgim.h>
#include <cstring>
using namespace std;

void ventana(string);
void genCadena(string *);
void aPila(string, int );
void cajas(int, int, char);
void grafCadena(string cadena);

int main(int argc, char const *argv[]) {
	int g = 0;
    srand(time(NULL));
    char opc;
    string cadena;
    cout << "Elija el modo: " << endl;
    cout << "(1) Manual" << endl;
    cout << "(2) Automatico" << endl;
    cin >> opc;
    if (opc == '1') {
        cout << "Inserte cadena: " << endl;
        cin >> cadena;
        cadena += ' ';
        if(cadena.size() <= 11){
        	ventana(cadena);
        	g = 1;
		}
    } else {
        genCadena(&cadena);
        cout << "Cadena generada: " << cadena << endl;
    }
    aPila(cadena, g);
    if(g == 1){
    	while(!kbhit())delay(1);
    	closegraph();
	}
    	
    return 0;
}
void genCadena(string * cadena){
    int n = rand()%100000+1, m = rand()%100000+1;
    while (n + m > 100000) {
        n = rand()%100000+1, m = rand()%100000+1;
        
    }
    cout << "n: "<<n <<endl;
        cout << "m: "<<m <<endl;
    for (int i = 0; i < n; i++){
        (*cadena) += '0';
    }
    for (int i = 0; i < m; i++){
        (*cadena) += '1';
    }
    cadena += ' ';
}


void aPila(string cadena, int g){
	grafCadena(cadena);
	int j = 0, p = 0;
    string id = "Z\u2080",cadCopia = cadena, aux;
    ofstream file;
    file.open("ID.txt");
    stack<int> pila;
    int n = cadena.size();
    char e = 'q';
    for (int i = 0; i < n; i++) {
        file << "(" << e << ", " <<cadCopia <<", "<< id << ")" << " \u22A6 ";
        cout << "(" << e << ", " <<cadCopia <<", "<< id << ")" << " -| ";
        if (cadena[i] == '0') {
        	j = i;
            pila.push(0);
            id = "X"+id;
            e = 'q';
        } else if (cadena[i] == '1') {
        	j--;
            e = 'p';
            if(id.size() > 0 && id[0] != 'Z')
                id.erase(0,1);
            if (pila.empty())
                break;
            pila.pop();
            
        } else if(pila.empty()){
            e = 'f';
        }
        if(cadCopia.size() > 2){
        	cadCopia.erase(0,1);
        	aux = cadCopia;
		}
        else{
            cadCopia = " \u03B5 ";
        	p = 1;	
		}
		if(g == 1) {
			cajas(0,j, 'X');
	        if(p != 1)
	    		grafCadena(aux);
	    	else
	    		grafCadena("-");
	    	delay(800);	
		}
        
    }
    file << "(" << e << ", " <<cadCopia <<", "<< id << ")";
    if(e == 'f'){
    	cout << "\nCadena aceptada. " << endl;
    	if(g = 1){
    		setcolor(YELLOW);
    		settextstyle(3,0,6);
    		outtextxy(100,600, "Cadena Aceptada");
		}
	}
    else{
        cout << "\nCadena rechazada." << endl;   
    	if(g = 1){
    		setcolor(RED);
    		settextstyle(3,0,6);
    		outtextxy(100,600, "Cadena Rechazada");
		}
	}
    file.close();
}

void ventana(string cadena){
	initwindow(1000,700);
	setbkcolor(BLACK);
	cleardevice();
}

void cajas(int x, int c, char l){
	char letra[2] = {0,0};
	letra[0] = l;
	cleardevice();
	int i =0;
	setcolor(WHITE);
	settextstyle(3,0,2);
	moveto(262+30*x,375);
	lineto(262+30*x,350);
	moveto(262+30*x,350);
	lineto(260+30*x,353);
	lineto(264+30*x,353);
	setfillstyle(1,3);
	for(; i <= c;i++){
		//int points[8] = {237+30*x, 375 + 25*i, 287+30*x, 375 + 25*i, 287+30*x, 400 + 25*i, 237+30*x,400+ 25*i};
		//fillpoly(4, points);	
		outtextxy(250, 373+ 25*i, letra);	
		outtextxy(250, 398+ 25*i, "Z");
	}
	if(i == 0)
		outtextxy(250, 398+ 25*i, "Z");
}

void grafCadena(string cadena){
	int n = cadena.size();
	char cad[n+1];
	strcpy(cad, cadena.c_str());
	
	setcolor(WHITE);
	settextstyle(6,0,5);
	outtextxy(250, 300, cad);
}


