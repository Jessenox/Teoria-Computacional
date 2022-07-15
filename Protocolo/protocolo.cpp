#include <iostream>
#include <bitset>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <fstream>
#include <ctime>
#include <winbgim.h>

#define size 1024*1024
using namespace std;

string creacion_cadena();
void validacion(ofstream *, ofstream *, ofstream *, ofstream *, int final);
void automata(string, ofstream *, ofstream *, ofstream *);
void loop();
void crearCadenas(ofstream *);
void delayClasico(int);

void ventanaLienzo();
void dibujarCirculos(int, int);
void texto();
void flecha(int, int, int);
void digitos();

int main(){
	short int opc;
	cout << "Selecciona la opcion: " << endl;
	cout << "1 .- Encender protocolo: " << endl;
	cout << "2 .- Ver grafico " << endl;
	cin >> opc;
	switch(opc){
		case 1:
			loop();
		break;			
		case 2:
			ventanaLienzo();
			
			while(!kbhit()) delay(1);
			closegraph();
		break;	
		default:
			cout << "No se eligio una opcion correcta." << endl;		
	}
}

void loop(){
	int i = 0;
	bool on = true;
	while(on) {
		delayClasico(1);
		char n1[128], n2[128], n3[128], n4[128];
		sprintf(n1, "AllCadenas_%d.txt", i);
		sprintf(n2, "CadenasAceptadas_%d.txt", i);
		sprintf(n3, "CadenasRechazadas_%d.txt", i);
		sprintf(n4, "historia_%d.txt", i);
			
		ofstream allCadenas, cadenasA, cadenasR, historia;
		ifstream leyecion;
		allCadenas.open(n1);
		cadenasA.open(n2);
		cadenasR.open(n3);
		historia.open(n4);
		crearCadenas(&allCadenas);
		allCadenas.close();
		validacion(&allCadenas, &cadenasA, &cadenasR, &historia, i);

		cadenasA.close(), cadenasR.close(), historia.close();

		i++;
		short int off = rand()%2;
		if (off == 0){
			on = false;
			cout << "Apagado" << endl;
		}
	}
	

}

void crearCadenas(ofstream * f){
	int i, n = pow(10, 6);
	for (int i = 0; i < n; ++i) {
		string cad = creacion_cadena();
		*f << cad << ',';
	}
}

string creacion_cadena(){
	char cadena[64];
	unsigned char c = 0;
	for (; c < 64; ++c) {
		int r = rand() % 10;
		if (c == 0)
			cadena[c] = '1';
		if(r > 5)
			cadena[c] = '1';
		else
			cadena[c] = '0';
	}
	return (string)cadena;
}

void validacion(ofstream * t, ofstream * a, ofstream * r, ofstream *h, int final){
	//Definimos variables para leer el archivo modo pro
	ifstream f;
    double c = 0, q = 0, u = 0, i = 0, j = 1;
    int p = pow(10, 6);
    int poner;
    bool end = false;
    char nAll[128];
    sprintf(nAll, "AllCadenas_%d.txt", final);
    //Aqui guardamos la cadena a validar
    string cadenita;
    //Abrimos el archivo que vamos a leer
   	f.open(nAll);
    //Creamos el buffer para no saturar la memoria ram
    char * buffer = new char[size];
	//Recorremos el archivo con el buffer (0x0)
	while(!end){
		//Asignamos al buffer un trozo del archivo
		f.read(buffer,size);
		while(true){
			//Si terminamos de recorrer el buffer, continua con la siguiente parte
			if(i >= size)
				break;
			//Si se encuentra con la ultima llave, se conluyó de leer el archivo
			if (c > p){
				end = true;
				break;
			}
			//Aqui realizamos las operaciones que querramos hacer con el buffer
			cadenita += buffer[(int)i];
			if (buffer[(int)i + 1] == ',') {
				if(cadenita[0] == ',')
					cadenita.erase(cadenita.begin());
				automata(cadenita, a, r, h);
				cadenita.erase();
				c++;
			}
			i++;
		}
		//Reinicia el contador de caracteres del buffer
		i = 0;
	}
	//Limpiamos el mB
    delete[] buffer;
    //Cerramos el archivo
    
    f.close();
}

void automata(string cadena, ofstream *a, ofstream *r, ofstream * h){
	unsigned char l= 0, n='0', cont = 0;
	string prueba;
	for (; l < 64; ++l) {
			switch(n){
				case '0':
					*h << "f(q0,";
					if(cadena[l] == '0'){
						n = '1';
						*h << '0';
					} else if (cadena[l] == '1'){
						n = '3';
						*h << '1';
					}
					*h << ") -> q" << n;
				break;
				case '1':
					*h << "f(q1,";
					if(cadena[l] == '0'){
						n = '0';
						*h << '0';
					} else if (cadena[l] == '1'){
						n = '2';
						*h << '1';
					}
					*h << ") -> q" << n;
				break;
				case '2':
					*h << "f(q2,";
					if(cadena[l] == '0'){
						n = '3';
						*h << '0';
					} else if (cadena[l] == '1'){
						n = '1';
						*h << '1';
					}
					*h << ") -> q" << n;
				break;
				case '3':
					*h << "f(q3,";
					if(cadena[l] == '0'){
						n = '2';
						*h << '0';
					} else if (cadena[l] == '1'){
						n = '0';
						*h << '1';
					}
					*h << ") -> q" << n;
				break;
			}
	}
	*h << '|';
	if(n == '0')
		*a << cadena << ',';
	else
		*r << cadena << ',';
}

void delayClasico(int s){
	for(int i = (time(NULL) + s); time(NULL) != i; time(NULL));
}

void ventanaLienzo(){
	initwindow(1000, 700);
	setbkcolor(BLACK);
	cleardevice();
	
	dibujarCirculos(300, 300);
	dibujarCirculos(600, 300);
	dibujarCirculos(300, 600);
	dibujarCirculos(600, 600);
	
	moveto(272, 327);
	lineto(272, 327+248);
	flecha(272, 327+248, 2);
	
	moveto(327, 327);
	lineto(327, 327+248);
	flecha(327, 327, 0);
	
	moveto(572, 327);
	lineto(572, 327+248);
	flecha(572, 327, 0);
	
	moveto(627, 327);
	lineto(627, 327+248);
	flecha(627, 327+248, 2);
	
	moveto(328, 327);
	lineto(328 +248, 327);
	flecha(328, 327, 3);
	
	moveto(327, 273);
	lineto(327+248, 273);
	flecha(327+248, 273, 1);
	
	moveto(328, 627);
	lineto(328 +248, 627);
	flecha(328, 627, 3);
	
	moveto(327, 573);
	lineto(327+248, 573);
	flecha(327+248, 573, 1);
	
	
	ellipse(300, 100, 0, 360, 100, 50);
	ellipse(600, 100, 0, 360, 100, 50);
	ellipse(600, 55, 0, 183, 50, 50);
	
	
	moveto(400, 100);
	lineto(500, 100);
	ellipse(450, 100, 205, 335, 100, 50);
	
	moveto(50, 200);
	lineto(300, 150);
	flecha(300,150, 1);
	flecha(500,100, 1);
	flecha(375,135, 3);
	flecha(550,55, 2);
	
	texto();
}

void dibujarCirculos(int x, int y){
	setcolor(WHITE);
	circle(x, y, 40);
}

void texto(){
	settextstyle(3,0,3);
	outtextxy(80, 140, "START");
	outtextxy(270, 80, "READY");
	outtextxy(570, 80, "SENDING");
	settextstyle(3,0,1);
	outtextxy(660, 20, "TIMEOUT");
	outtextxy(410, 70, "DATA IN");
	outtextxy(410, 150, "ACK");
	
	settextstyle(4,0,3);
	outtextxy(280, 280, "q0");
	outtextxy(580, 280, "q1");
	outtextxy(280, 580, "q3");
	outtextxy(580, 580, "q2");
	
	digitos();
	settextstyle(8,0,2);
	setcolor(YELLOW);
	outtextxy(600, 200, "Apriete una tecla para salir");
}

void flecha(int x, int y, int o){
	switch(o){
		case 0:
			line(x,y,x-10, y+20);
			line(x,y,x+10, y+20);
		break;
		case 1:
			line(x,y,x-20, y-10);
			line(x,y,x-20, y+10);
		break;
		case 2:
			line(x,y,x-10, y-20);
			line(x,y,x+10, y-20);
		break;
		case 3:
			line(x,y,x+20, y-10);
			line(x,y,x+20, y+10);
		break;
		
	}
}

void digitos(){
	settextstyle(5,0,3);
	outtextxy(250, 400, "1");
	outtextxy(300, 400, "1");
	
	outtextxy(450, 250, "0");
	outtextxy(450, 300, "0");
	
	outtextxy(580, 400, "1");
	outtextxy(630, 400, "1");
	
	outtextxy(450, 580, "0");
	outtextxy(450, 630, "0");
}

