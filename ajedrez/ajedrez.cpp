#include <iostream>
#include <fstream>
#include <winbgim.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <time.h>

using namespace std;

void menu(bool);
void configuracion();
void dfa(string, string*);
void dfa2(string, string*);
void creacionRutas(string, string, bool);
void estados(string* ,char);
void estados2(string* ,char);
void ruta(string, string,string *, int i, int, int, char, ofstream *, ofstream *, bool);
bool nfa(char color, int act, int sig);

string leerRuta(int, bool);


void ventana();
void tablero();
void posiciones(int);

void cadenaRandom(string *);

int main(int argc, char const *argv[]) {
    srand(time(NULL));
	configuracion();
    return 0;
}

void menu(bool random){
	
	int players, i = 0;
    cout << "Coloque 1 si solo es un jugador o 2 si son 2 jugadores.\n";
    if(!random)
		cin >> players;
	else{
		players = rand()%2 + 1;
		cout << players << endl;
	}
    if (players == 1) {
        string cadena, cadEstados;
        cout << "Coloque la cadena (Solo r o n):" << endl;
        if(!random)
			cin >> cadena;
		else{
			cadenaRandom(&cadena);
			cout << cadena << endl;
		}
			
        dfa(cadena, &cadEstados);
        creacionRutas(cadEstados, cadena, 0);
        
        string ruta = leerRuta(i, 0);
        
        if(ruta.empty()){
        	cout << "La cadena no tiene movimientos ganadores." << endl;
        	exit(0);
		} else{
			ventana();
		}
        
		for(int k = 0; k < ruta.size(); k++){
			setfillstyle(1,YELLOW);
			cout << (int)ruta[k] << ", ";
			
			posiciones((int)ruta[k]);
			delay(800);
			tablero();
		}
		cout << endl;
		cleardevice();
		settextstyle(4,0,5);
		outtextxy(100,600,"Presione para finalizar");
    } else{
        string cadena, cadEstados, cadena2, cadEstados2;
        if(!random){
        	cout << "Coloque la cadena del jugador 1 (Solo r o n):" << endl;
        	cin >> cadena;
        	cout << "Coloque la cadena del jugador 2 (Solo r o n):" << endl;
        	cin >> cadena2;
		}
		else{
			cout << "Coloque la cadena del jugador 1 (Solo r o n):" << endl;
        	cadenaRandom(&cadena);
        	cout << cadena << endl;
        	cout << "Coloque la cadena del jugador 2 (Solo r o n):" << endl;
        	cadenaRandom(&cadena2);
        	
		}
        
        dfa(cadena, &cadEstados);
        dfa2(cadena2, &cadEstados2);

        creacionRutas(cadEstados, cadena, 0);
        creacionRutas(cadEstados2, cadena2, 1);
        int turno = rand()%2;
        
    	string ruta1 = leerRuta(i, 0), ruta2 = leerRuta(i, 1);
    	if(ruta1.empty() || ruta2.empty()){
        	cout << "La cadena no tiene movimientos ganadores." << endl;
        	exit(0);
		} else{
			ventana();
		}
		for(int k = 0; k < ruta1.size(); k++){
			if(turno){
	        	
				settextstyle(4,0,4);
				outtextxy(350,50,"Empieza el jugador 1");
			} else{
				
				settextstyle(4,0,4);
				outtextxy(350,50,"Empieza el jugador 2");
			}
			if((int)ruta1[k] == (int)ruta2[k]){
				int p = 0;
				if(turno){
					while((int)ruta1[k] == (int)ruta2[k]){
						ruta1 = leerRuta(p,0);
						p++;
					}
					setcolor(WHITE);
					settextstyle(4,0,5);
					outtextxy(100,600,"Jugador 1 cambia de ruta");
				} else {
					while((int)ruta1[k] == (int)ruta2[k]){
						ruta2 = leerRuta(p,1);
						p++;
					}
					setcolor(WHITE);
					settextstyle(4,0,5);
					outtextxy(100,600,"Jugador 2 cambia de ruta");
				}
			}
			if(turno){
				setfillstyle(1,YELLOW);
				posiciones((int)ruta1[k]);
				delay(700);
				setfillstyle(1,CYAN);
				posiciones((int)ruta2[k]);
				delay(700);
			} else{	
				setfillstyle(1,CYAN);
				posiciones((int)ruta2[k]);
				delay(700);
				setfillstyle(1,YELLOW);
				posiciones((int)ruta1[k]);
				delay(700);
			}
			cout << "ruta1: " << (int)ruta1[k] <<" ruta2: "<< (int)ruta2[k] << endl;
			if((int)ruta1[k] == 16 && turno){
				cleardevice();
				settextstyle(4,0,5);
				outtextxy(200,600,"Jugador 1 llega primero");
				break;
			} else if((int)ruta2[k] == 13){
				cleardevice();
				settextstyle(4,0,5);
				outtextxy(200,600,"Jugador 2 llega primero");
				break;
			}
			tablero();
		}
    }
    while(!kbhit()) delay(500);
    closegraph();
}

void configuracion(){
    int mod, ply;
    cout << "Elija el modo: " << endl;
    cout << "1.- Manual" << endl;
    cout << "2.- Automatico" << endl;
    cin >> mod;
    switch (mod) {
        case 1:
        	menu(0);
            break;
        case 2:
        	menu(1);
            break;
        default:
            cout << "No es una opcion valida" << endl;
            break;
    }
}

void dfa(string cadena, string *opc){
    int i = 0;
    char st = 'A';
    string opciones;
    opciones += st;
    while (i < cadena.size()) {
        switch (st) {
            case 'A':
                if (cadena[i] == 'r') {
                    st = 'B';
                } else {
                    st = 'C';
                }
                break;
            case 'B': case 'C':
                if(cadena[i] == 'r'){
                    st = 'D';
                } else {
                    if (st == 'B')  {
                        st = 'E';
                    }
                    if (st == 'B')
                        st = 'F';
                }
                break;
            case 'D': case 'F': case 'G': case 'H': case 'I': case 'J': case 'K':
                if(cadena[i] == 'r'){
                    st = 'G';
                } else {
                    if (st == 'D' || st == 'I') 
                        st = 'H';
                    if(st == 'J')
                        st = 'F';
                    if(st == 'G' || st == 'H' || st == 'K')
                        st = 'K';
                    if(st == 'F')
                        st = 'J';
                }
                break;
            case 'E':
                if(cadena[i] == 'r'){
                    st = 'G';
                } else {
                    st = 'H';
                }
            break;
            default:
                break;
        }
        opciones += st;
        i++;
    }
    (*opc) = opciones;
    
}

void dfa2(string cadena, string *opc){
    int i = 0;
    char st = 'A';
    string opciones;
    opciones += st;
    while (i < cadena.size()) {
        switch (st) {
            case 'A':
                if (cadena[i] == 'r') {
                    st = 'B';
                } else {
                    st = 'C';
                }
                break;
            case 'B': case 'C':
                if(cadena[i] == 'n'){
                    st = 'E';
                } else {
                    if (st == 'B')  {
                        st = 'D';
                    }
                    if (st == 'C')
                        st = 'F';
                }
                break;
            case 'D': case 'E': case 'G': case 'H': case 'I': case 'J': case 'K':
                if(cadena[i] == 'n'){
                    st = 'H';
                } else {
                    if (st == 'E' || st == 'J') 
                        st = 'I';
                    if(st == 'D')
                        st = 'G';
                    if(st == 'H' || st == 'I' || st == 'K')
                        st = 'K';
                    if(st == 'G')
                        st = 'D';
                }
                break;
            case 'F':
                if(cadena[i] == 'n'){
                    st = 'J';
                } else {
                    st = 'I';
                }
            break;
            default:
                break;
        }
        opciones += st;
        i++;
    }
    (*opc) = opciones;
}

void creacionRutas(string opc, string colores, bool s){
    int n = opc.size(), m = colores.size();
    string conjuntos[n+1];
    if(!s){
        for (int i = 0; i < n; i++) {
            estados(&conjuntos[i], opc[i]);
        }
        /*
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < conjuntos[i].size(); j++){
                cout <<(int)conjuntos[i][j] << ", ";
            }
            cout << endl;
        }
        */ 
        conjuntos[n] = "final";
    
        ofstream f1, f2;
        f1.open("Rutas.txt");
        f2.open("RutasAceptadas.txt");
        ruta("1", colores, conjuntos, 0, 0, m, 1, &f1, &f2, false);
        f1.close();
        f2.close();
    } else {
        for (int i = 0; i < n; i++) {
            estados2(&conjuntos[i], opc[i]);
        }
        conjuntos[n] = "final";
        ofstream f1, f2;
        f1.open("Rutas2.txt");
        f2.open("RutasAceptadas2.txt");
        ruta("4", colores, conjuntos, 0, 0, m, 4, &f1, &f2, true);
        f1.close();
        f2.close();
    }
}

void estados(string *conjuntos, char e){
    switch (e) {
    case 'A':
        *conjuntos = 1;
        break;
    case 'B':
        *conjuntos = {2,5};
        break;
    case 'C':
        *conjuntos = {6};
        break;
    case 'D':
        *conjuntos = {2,5,7,10};
        break;
    case 'E':
        *conjuntos = {1,3,6,9};
        break;
    case 'F':
        *conjuntos = {1,3,9,11};
        break;
    case 'G':
        *conjuntos = {2,4,5,7,10,12,13,15};
        break;
    case 'H':
        *conjuntos = {1,3,6,8,9,11,14};
        break;
    case 'I':
        *conjuntos = {2,4,5,7,10,13};
        break;
    case 'J':
        *conjuntos = {6,8,14,16};
        break;
    case 'K':
        *conjuntos = {1,3,6,8,9,11,14,16};
        break;
    default:
    cout << "No deberia de existir" << endl;
        break;
    }
}

void estados2(string *conjuntos, char e){
    switch (e) {
    case 'A':
        *conjuntos = 4;
        break;
    case 'B':
        *conjuntos = {7};
        break;
    case 'C':
        *conjuntos = {3,8};
        break;
    case 'D':
        *conjuntos = {2,4,10,12};
        break;
    case 'E':
        *conjuntos = {3,6,8,11};
        break;
    case 'F':
        *conjuntos = {2,4,7,12};
        break;
    case 'G':
        *conjuntos = {5,7,13,15};
        break;
    case 'H':
        *conjuntos = {1,3,6,8,9,11,14,16};
        break;
    case 'I':
        *conjuntos = {2,4,5,7,10,12,15};
        break;
    case 'J':
        *conjuntos = {1,3,6,8,11,16};
        break;
    case 'K':
        *conjuntos = {2,4,5,7,10,12,13,15};
        break;
    default:
    cout << "No deberia de existir" << endl;
        break;
    }
}

bool nfa(char color, int act, int sig){
    bool cumple;
    switch (act) {
    case 1:
        if (color == 'r'){
            if (sig == 2 || sig == 5) {
                cumple = true;
            } else
                cumple = false;
        } else{
            if (sig == 6) {
                cumple = true;
            } else 
                cumple = false;
        }
        
    break;
    case 2:
        if (color == 'r'){
            if (sig == 5 || sig == 7) {
                cumple = true;
            } else
                cumple = false;
        } else{
            if (sig == 1 || sig == 3 || sig == 6) {
                cumple = true;
            } else 
                cumple = false;
        }
    break;
    case 3:
        if (color == 'r'){
            if (sig == 2 || sig == 4 || sig == 7) {
                cumple = true;
            } else
                cumple = false;
        } else{
            if (sig == 6 || sig == 8) {
                cumple = true;
            } else 
                cumple = false;
        }
    break;
    case 4:
        if (color == 'r'){
            if (sig == 7) {
                cumple = true;
            } else
                cumple = false;
        } else{
            if (sig == 3 || sig == 8) {
                cumple = true;
            } else 
                cumple = false;
        }
    break;
    case 5:
        if (color == 'r'){
            if (sig == 2 || sig == 10) {
                cumple = true;
            } else
                cumple = false;
        } else{
            if (sig == 1 || sig == 6 || sig == 9) {
                cumple = true;
            } else 
                cumple = false;
        }
    break;
    case 6:
        if (color == 'r'){
            if (sig == 2 || sig == 5 || sig == 7 || sig == 10) {
                cumple = true;
            } else
                cumple = false;
        } else{
            if (sig == 1 || sig == 3 || sig == 9 || sig == 11) {
                cumple = true;
            } else 
                cumple = false;
        }
    break;
    case 7:
        if (color == 'r'){
            if (sig == 2 || sig == 4 || sig == 10 || sig == 12) {
                cumple = true;
            } else
                cumple = false;
        } else{
            if (sig == 3 || sig == 6 || sig == 8 || sig == 11) {
                cumple = true;
            } else 
                cumple = false;
        }
    break;
    case 8:
        if (color == 'r'){
            if (sig == 4 || sig == 7 || sig == 12) {
                cumple = true;
            } else
                cumple = false;
        } else{
            if (sig == 3 || sig == 11) {
                cumple = true;
            } else 
                cumple = false;
        }
    break;
    case 9:
        if (color == 'r'){
            if (sig == 5 || sig == 10 || sig == 13) {
                cumple = true;
            } else
                cumple = false;
        } else{
            if (sig == 6 || sig == 14) {
                cumple = true;
            } else 
                cumple = false;
        }
    break;
    case 10:
        if (color == 'r'){
            if (sig == 5 || sig == 7 || sig == 13 || sig == 15) {
                cumple = true;
            } else
                cumple = false;
        } else{
            if (sig == 6 || sig == 9 || sig == 11 || sig == 14) {
                cumple = true;
            } else 
                cumple = false;
        }
    break;
    case 11:
        if (color == 'r'){
            if (sig == 7 || sig == 10 || sig == 12 || sig == 15) {
                cumple = true;
            } else
                cumple = false;
        } else{
            if (sig == 6 || sig == 8 || sig == 14 || sig == 16) {
                cumple = true;
            } else 
                cumple = false;
        }
    break;
    case 12:
        if (color == 'r'){
            if (sig == 7 || sig == 15) {
                cumple = true;
            } else
                cumple = false;
        } else{
            if (sig == 8 || sig == 11 || sig == 16) {
                cumple = true;
            } else 
                cumple = false;
        }
    break;
    case 13:
        if (color == 'r'){
            if (sig == 10) {
                cumple = true;
            } else
                cumple = false;
        } else{
            if (sig == 9 || sig == 14) {
                cumple = true;
            } else 
                cumple = false;
        }
    break;
    case 14:
        if (color == 'r'){
            if (sig == 10 || sig == 13 || sig == 15) {
                cumple = true;
            } else
                cumple = false;
        } else{
            if (sig == 9 || sig == 11) {
                cumple = true;
            } else 
                cumple = false;
        }
    break;
    case 15:
        if (color == 'r'){
            if (sig == 10 || sig == 12) {
                cumple = true;
            } else
                cumple = false;
        } else{
            if (sig == 11 || sig == 14 || sig == 16) {
                cumple = true;
            } else 
                cumple = false;
        }
    break;
    case 16:
        if (color == 'r'){
            if (sig == 12 || sig == 15) {
                cumple = true;
            } else
                cumple = false;
        } else{
            if (sig == 11) {
                cumple = true;
            } else 
                cumple = false;
        }
    break;
    }
    return cumple;
}

//Vemos si se cumple el nfa , con el color, los datos y valores
//de los conjuntos actuales y el siguiente
void ruta(string cadena, string color,string * datos, int i, int j, int n, char k, ofstream *f1 , ofstream *f2, bool s){
    for (; j < datos[i].size(); j++) { 
        if (datos[i+1] != "final" && datos[i][j] == k){
            for (int p = 0; p < datos[i+1].size() ; p++) {
                if(nfa(color[i], datos[i][j], datos[i+1][p])){
                    string aux = cadena;
                    int dato = (int)datos[i+1][p];
                    aux += ",";
                    aux += to_string(dato);
                    if(i == n-1){
                        (*f1) << aux << endl;
                        if (s) {
                            if(dato == 13)
                                (*f2) << aux << endl;    
                        }
                        else {
                            if(dato == 16)
                                (*f2) << aux << endl;
                        }   
                    }
                    ruta(aux, color, datos, i+1, 0, n, datos[i+1][p], f1, f2, s);     
                }
            }
        }
    }
}

string leerRuta (int i, bool dP){
	int j = 0, k = 0, dato;
	ifstream f1;
	string num,datosos;
	if(dP)
		f1.open("RutasAceptadas2.txt");
	else
		f1.open("RutasAceptadas.txt");
	while(!f1.eof()){
		num += f1.get();
		j++;
		if(num[j-1] == ','){
			char temp;
			num = num.erase(j-1);
			dato = stoi(num);
			temp = dato;
			datosos += temp;
			num.clear();
			j = 0;
		}
		if(num[j-1] == '\n'){
			k++;
			char temp;
			num = num.erase(j-1);
			dato = stoi(num);
			temp = dato;
			datosos += temp;
			num.clear();
			
			if(i+1 == k){
				break;	
			} else{
				j=0;
				datosos.clear();
			}
		}
	}
	f1.close();
	
	return datosos;
}

void cadenaRandom(string *cadena){
	int saiz = rand() % 11;
	while(saiz < 4) saiz = rand() % 11;
	int v;
	for(int i = 0; i < saiz; i++){
		v = rand()% 2;
		if(v){
			(*cadena) += 'r';
		} else
			(*cadena) += 'n';
	}
}

void ventana(){
	initwindow(1200, 700);
	setbkcolor(DARKGRAY);
	cleardevice();

	tablero();
	
}

void tablero(){
	setfillstyle(1,BLACK);
	for(int i = 0; i < 4; i++){
		int puntos[8] = {400,100+(i*100),500,100+(i*100),500,200+(i*100),400,200+(i*100)};
		for(int j = 0; j < 4; j++){
			if((i+1)%2 != 0){
				if((j+1)%2 == 0)
					setfillstyle(1,RED);
				else
					setfillstyle(1,BLACK);	
			} else{
				if((j+1)%2 == 0)
					setfillstyle(1,BLACK);
				else
					setfillstyle(1,RED);	
			}
			
			fillpoly(4,puntos);
			puntos[0] += 100;
			puntos[2] += 100;
			puntos[4] += 100;
			puntos[6] += 100;
			
		}
	}
}

void posiciones(int i){
	switch(i){
		case 1:
			fillellipse(450,150, 25, 25);
		break;
		case 2:
			fillellipse(550,150, 25, 25);
		break;
		case 3:
			fillellipse(650,150, 25, 25);
		break;
		case 4:
			fillellipse(750,150, 25, 25);
		break;
		case 5:
			fillellipse(450,250, 25, 25);
		break;
		case 6:
			fillellipse(550,250, 25, 25);
		break;
		case 7:
			fillellipse(650,250, 25, 25);
		break;
		case 8:
			fillellipse(750,250, 25, 25);
		break;
		case 9:
			fillellipse(450,350, 25, 25);
		break;
		case 10:
			fillellipse(550,350, 25, 25);
		break;
		case 11:
			fillellipse(650,350, 25, 25);
		break;
		case 12:
			fillellipse(750,350, 25, 25);
		break;
		case 13:
			fillellipse(450,450, 25, 25);
		break;
		case 14:
			fillellipse(550,450, 25, 25);
		break;
		case 15:
			fillellipse(650,450, 25, 25);
		break;
		case 16:
			fillellipse(750,450, 25, 25);
		break;
	}
}
