#include <iostream>
#include <fstream>
#include <cmath>
#include <winbgim.h>

using namespace std;

void obtenerDatos(int, ofstream *, int *, int*, int *, int*);
void grafica(int *);
void grafica2(int *);
void grafica3(int *);
void grafica4(int *);
void ventana(int *, int *, int *, int *);

int main(int argc, char const *argv[]) {
	int val[500];
	int valog[500];
	int sim[500];
	int simlog[500];
	int buffer = 1024*1024;
	ofstream dat;
	dat.open("datos.txt");
	obtenerDatos(buffer,&dat, val, valog,sim,simlog);
	dat.close();
	ventana(val, valog, sim, simlog);
	while(!kbhit())delay(500);
}

void obtenerDatos(int bSize, ofstream * datos, int *val,int *valog, int *sim,int *simlog){
	ifstream f;
    double c = 0, p = 0, q = 0, u = 0, i = 0, j = 0;
    int poner;
    bool end = false;
    
   	f.open("file_3.txt");
    //Creamos el buffer para no saturar la memoria ram
    char * buffer = new char[bSize];
	//Recorremos el archivo con el buffer (0x0)
	while(!end){
		//Asignamos al buffer un trozo del archivo
		f.read(buffer,bSize);
		while(true){
			//Si terminamos de recorrer el buffer, continua con la siguiente parte
			if(i >= bSize)
				break;
			//Si se encuentra con la ultima llave, se conluyó de leer el archivo
			if (buffer[(int)i] == '}'){
				end = true;
				break;
			}
			switch(buffer[(int)i] ){
				case '1':
					u++;
					p++;
				break;
				case '0':
					p++;
				break;
				case ',':
					c++;
					char buf[64];
					sprintf(buf, "%d", (int)u);
					*datos << buf << ',';
					if((int)c%600 == 0){
						val[(int)q] = u;
						valog[(int)q] = 10*log(u);
						sim[(int)q] = p;
						simlog[(int)q] = 10*log(p);
						q++;
					}
					
					if(log(p) > j)
						j = log(p);
					
					u = 0;
					p = 0;
				break;	
			}
			
			i++;
		}
		//Reinicia el contador de caracteres del buffer
		i = 0;
	}
	cout << "j: " << j<< endl;
	//Limpiamos el mB
    delete[] buffer;
    //Cerramos el archivo
    
    f.close();
}

void ventana(int * v, int * l, int * m, int * n){
	initwindow(800,600);
	setbkcolor(BLACK);
	cleardevice();
	
	grafica(v);
	delay(5000);
	cleardevice();
	grafica2(l);
	delay(5000);
	cleardevice();
	grafica3(m);
	delay(5000);
	cleardevice();
	grafica4(n);
}

void grafica(int * a){
	int x=150, y=500;
	moveto(x,y);
	setcolor(WHITE);
	lineto(x+500,y);
	moveto(x,y);
	lineto(x,y-500);
	
	settextstyle(4,0,1);
	
	for(int i = 0; i < 6; i++){
		char buf[64];
		sprintf(buf, "%d", 5*i);
		outtextxy(x-50, (y-20)-83*i, buf);
	}
	moveto(x,y);
	outtextxy(x, y+10, "0");
	outtextxy(x+480, y+10, "300000");
	setcolor(CYAN);
	for(int i = 0; i < 500; i++){
		int s = (500*a[i])/30;
		//putpixel(x + i, y-s, 3);
		lineto(x + i, y-s);
		moveto(x + i, y-s);
		//cout << "s:" << s << "a: " << a[i] << endl;
	}
	setcolor(GREEN);
	outtextxy(30,20, "UNOS");
	outtextxy(580,550, "CADENAS");
}

void grafica2(int * l){
	int x=150, y=500;
	moveto(x,y);
	setcolor(WHITE);
	lineto(x+500,y);
	moveto(x,y);
	lineto(x,y-500);
	
	settextstyle(4,0,1);
	for(int i = 0; i < 5; i++){
		char buf[64];
		sprintf(buf, "%d", i);
		outtextxy(x-50, (y-20)-100*i, buf);
	}
	moveto(x,y);
	outtextxy(x, y+10, "0");
	outtextxy(x+480, y+10, "300000");
	setcolor(CYAN);
	for(int i = 0; i < 500; i++){
		int s = ((500*l[i])/50);
	
		lineto(x + i, y-s);
		moveto(x + i, y-s);
	
	}
	setcolor(YELLOW);
	outtextxy(30,20, "UNOS");
	outtextxy(650,20, "(logaritmo)");
	outtextxy(580,550, "CADENAS");
}

void grafica3(int * a){
	int x=150, y=500;
	moveto(x,y);
	setcolor(WHITE);
	lineto(x+500,y);
	moveto(x,y);
	lineto(x,y-500);
	
	settextstyle(4,0,1);
	
	for(int i = 0; i < 6; i++){
		char buf[64];
		sprintf(buf, "%d", 5*i);
		outtextxy(x-50, (y-20)-83*i, buf);
	}
	moveto(x,y);
	outtextxy(x, y+10, "0");
	outtextxy(x+480, y+10, "300000");
	setcolor(CYAN);
	for(int i = 0; i < 500; i++){
		int s = (500*a[i])/30;
		//putpixel(x + i, y-s, 3);
		lineto(x + i, y-s);
		moveto(x + i, y-s);
		//cout << "s:" << s << "a: " << a[i] << endl;
	}
	setcolor(YELLOW);
	outtextxy(30,20, "SIMBOLOS");
	outtextxy(580,550, "CADENAS");
}

void grafica4(int * l){
	int x=150, y=500;
	moveto(x,y);
	setcolor(WHITE);
	lineto(x+500,y);
	moveto(x,y);
	lineto(x,y-500);
	
	settextstyle(4,0,1);
	for(int i = 0; i < 5; i++){
		char buf[64];
		sprintf(buf, "%d", i);
		outtextxy(x-50, (y-20)-100*i, buf);
	}
	moveto(x,y);
	outtextxy(x, y+10, "0");
	outtextxy(x+480, y+10, "300000");
	setcolor(GREEN);
	for(int i = 0; i < 500; i++){
		int s = ((500*l[i])/50);
	
		lineto(x + i, y-s);
		moveto(x + i, y-s);
	
	}
	setcolor(YELLOW);
	outtextxy(30,20, "SIMBOLOS");
	outtextxy(650,20, "(logaritmo)");
	outtextxy(580,550, "CADENAS");
}


