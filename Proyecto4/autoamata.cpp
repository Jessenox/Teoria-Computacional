#include <iostream>
#include <fstream>
#include <winbgim.h>

using namespace std;

void automata(string, int *, int *, int, ofstream *, ofstream *, int*, int*, int*, int*, int*, int*, int*);
void cortarCadenas(ifstream *);
void automataGrafico();

int main(){
	char opc;
    ifstream file;
    file.open("pagina.html");
    cortarCadenas(&file);
    file.close();
    cout << "Archivo revisado" << endl;
    cout << "Ver modo grafico? s/n" << endl;
    cin >> opc;
    if(opc == 's'){
    	automataGrafico();
    	while(!kbhit())delay(1000);	
    	closegraph();
	} else
		cout << "Saliendo..."<< endl;
    return 0;
}

void cortarCadenas(ifstream *file){
    string cadena;
    int contPalabras = 0, contGen = 0, contLinea = 1, aux=0, web=0, webpage=0, website=0, webmaster=0, ebay=0, page=0, site=0;
    ofstream historia, f;
    historia.open("Historia.txt");
	f.open("archivo.txt");
	f << "Palabras encontradas:\n" << endl;
    while(!(*file).eof()){
        *file >> cadena;
        if((*file).peek() == '\n' || (*file).peek() == EOF){
        	contLinea++;
    		contGen = 0;
		}
        automata(cadena, &contPalabras, &contGen, contLinea, &historia, &f, &web, &webpage, &website, &webmaster, &ebay, &page, &site);
    }   
    f << "\nConteo de palabras:" << endl;
    f << "web:" << web << endl;
    f << "webmaster: " << webmaster << endl;
    f << "webpage: " << webpage << endl;
    f << "website: " << website << endl;
    f << "ebay:" << ebay << endl;
    f << "page:" << page << endl;
    f << "site: " << site<< endl;
    historia.close(); 
    f.close();
}

void automata(string cadena, int * contPal, int * cGen, int contLin, ofstream * historia, ofstream * file,
int* web, int* webpage, int* website, int* webmaster, int* ebay, int* page, int* site){
    unsigned char estado = 'A', cont = 0;
    for(char i = 0; i < cadena.size(); i++){
        (*historia) << "f("<< estado<< ", " << cadena[i] << ")->";
        switch (estado){
        case 'A':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'C';
                break;
            case 'p':
                estado = 'H';
                break;
            case 's':
                estado = 'I';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'B':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'D';
                break;
            case 'p':
                estado = 'H';
                break;
            case 's':
                estado = 'I';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'C':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'C';
                break;
            case 'b':
                estado = 'E';
                break;
            case 'p':
                estado = 'H';
                break;
            case 's':
                estado = 'I';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'D':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'C';
                break;
            case 'b':
                estado = 'F';
                break;
            case 'p':
                estado = 'H';
                break;
            case 's':
                estado = 'I';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'E':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'C';
                break;
            case 'p':
                estado = 'H';
                break;
            case 'a':
                estado = 'G';
                break;
            case 's':
                estado = 'I';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'F':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'C';
                break;
            case 'p':
                estado = 'H';
                break;
            case 'a':
                estado = 'G';
                break;
            case 's':
                estado = 'I';
                break;
            case 'm':
                estado = 'J';
                break;
            default:
                estado = 'A';
                break;
            }
            cont++;
            break;
        case 'G':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'C';
                break;
            case 'p':
                estado = 'H';
                break;
            case 's':
                estado = 'I';
                break;
            case 'y':
                estado = 'K';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'H':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'C';
                break;
            case 'p':
                estado = 'H';
                break;
            case 'a':
                estado = 'L';
                break;
            case 's':
                estado = 'I';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'I':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'C';
                break;
            case 'p':
                estado = 'H';
                break;
            case 's':
                estado = 'I';
                break;
            case 'i':
                estado = 'M';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'J':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'C';
                break;
            case 'p':
                estado = 'H';
                break;
            case 'a':
                estado = 'N';
                break;
            case 's':
                estado = 'I';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'K':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'C';
                break;
            case 'p':
                estado = 'H';
                break;
            case 's':
                estado = 'I';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'L':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'C';
                break;
            case 'p':
                estado = 'H';
                break;
            case 'g':
                estado = 'O';
                break;
            case 's':
                estado = 'I';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'M':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'C';
                break;
            case 'p':
                estado = 'H';
                break;
            case 's':
                estado = 'I';
                break;
            case 't':
                estado = 'P';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'N':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'C';
                break;
            case 'p':
                estado = 'H';
                break;
            case 's':
                estado = 'Q';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'O':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'R';
                break;
            case 'p':
                estado = 'H';
                break;
            case 's':
                estado = 'I';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'P':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'T';
                break;
            case 'p':
                estado = 'H';
                break;
            case 's':
                estado = 'I';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'Q':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'C';
                break;
            case 'p':
                estado = 'H';
                break;
            case 's':
                estado = 'I';
                break;
            case 'i':
                estado = 'M';
                break;
            case 't':
                estado = 'U';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'R':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'C';
                break;
            case 'b':
                estado = 'E';
                break;
            case 'p':
                estado = 'H';
                break;
            case 's':
                estado = 'I';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'T':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'C';
                break;
            case 'b':
                estado = 'E';
                break;
            case 'p':
                estado = 'H';
                break;
            case 's':
                estado = 'I';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'U':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'V';
                break;
            case 'p':
                estado = 'H';
                break;
            case 's':
                estado = 'I';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'V':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'C';
                break;
            case 'b':
                estado = 'E';
                break;
            case 'p':
                estado = 'H';
                break;
            case 's':
                estado = 'I';
                break;
            case 'r':
                estado = 'W';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        case 'W':
            switch (cadena[i]) {
            case 'w':
                estado = 'B';
                break;
            case 'e':
                estado = 'C';
                break;
            case 'p':
                estado = 'H';
                break;
            case 's':
                estado = 'I';
                break;
            default:
                estado = 'A';
                break;
            }
            break;
        default:
            cout << "Esto no deberia de pasar" << endl;
            break;
        }
        (*historia) << estado << ", ";
    }
    (*cGen)++;
    (*historia) << endl;
    if(estado == 'F' || estado == 'K' || estado == 'R' || estado == 'T' || estado == 'W'){
        (*contPal)++;
        (*file) << "(" << (*contPal) << ") " << cadena << " | Linea: " << contLin << " Palabra: "<< (*cGen) << endl;
    }
    switch(estado){
    	case 'F':
    		(*web)++;
    	break;
    	case 'K':
    		(*ebay)++;
    	break;
    	case 'R':
    		(*page)++;
    		if(cont > 0)
    			(*webpage)++;
    	break;
    	case 'T':
    		(*site)++;
    		if(cont > 0)
    			(*website)++;
    	break;
    	case 'W':
    		(*webmaster)++;
    	break;
	}
}

void automataGrafico(){
	initwindow(1280,700);
	setbkcolor(BLACK);
	cleardevice();
	
	setcolor(WHITE);
	settextstyle(3,0,3);
	
	char *hori[14] = {"R","O","L","H","A","B","D","F","J","N","Q","U","V","W"};
	char *vert[9] = {"T","P","M","I","A","C","E","G","K"};
	//Caracter
	char *hl[13] = {"e","g","a","p","w","e","b","m","a","s","t","e","r"};
	char *vl[8] = {"e","t","i","s","e","b","a","y"};
	
	setcolor(WHITE);
	//Letras
	for(int i = 0; i < 14; i++)
		outtextxy(190 + 70*i, 335, hori[i]);
	for(int i = 0; i < 9; i++)
		outtextxy(470, 55+70*i, vert[i]);
	//Caracteres
	settextstyle(3,0,2);
	for(int i = 0; i < 13; i++)
		outtextxy(230 + 70*i, 345, hl[i]);
	for(int i = 0; i < 8; i++)
		outtextxy(485, 90+70*i, vl[i]);	
	
	//Circulos
	for(int i = 0; i < 14; i++)
		circle(200 + 70*i, 350, 25);
	for(int i = 0; i < 9; i++)
		circle(480, 70+70*i, 25);
	//Estados Finales
	circle(200, 350, 20);
	circle(690, 350, 20);
	circle(1110, 350, 20);
	circle(480, 70, 20);
	circle(480, 630, 20);
	for(int i = 0; i < 3; i++){
		if(i == 0)
			ellipse(335+(i*70), 350, 10, 170,150, 50);
		ellipse((615-70) +(i*70) , 350, 10, 170,150, 50);
		
		ellipse(370-70 +(i*70), 350, 15, 165,120, 40);
		ellipse(580-70 +(i*70), 350, 15, 165,120, 40);
		
		ellipse(405-70 +(i*70), 350, 20, 160,90, 30);
		ellipse(545-70+(i*70) , 350, 20, 160,90, 30);
		
		ellipse(440-70+(i*70) , 350, 40, 120,60, 20);
		ellipse(510-70 +(i*70), 350, 40, 120,60, 20);
		
		ellipse(650-70 +(i*70), 350, 8, 172,180, 60);
		
		ellipse(685-70 +(i*70), 350, 8, 172,210, 70);
		ellipse(720-70 +(i*70), 350, 5, 174,240, 80);
		ellipse(755-70 +(i*70), 350, 5, 176,270, 90);
		if(i != 2)
			ellipse(790-70 +(i*70), 350, 5, 175,300, 100);
	}
	
	for(int i = 0; i < 3; i++){
	if(i != 0)	
		ellipse(480, 210-70+(70*i), 100, 260,50, 150);
	ellipse(480, 245-70+(70*i), 105, 255,40, 120);
	ellipse(480, 280-70+(70*i), 110, 250,30, 90);
	ellipse(480, 315-70+(70*i), 130, 230,20, 60);
	if(i != 2)	
		ellipse(480, 490-70+(70*i), 100, 260,50, 150);
	ellipse(480, 455-70+(70*i), 105, 255,40, 120);
	ellipse(480, 420-70+(70*i), 110, 250,30, 90);
	ellipse(480, 385-70+(70*i), 130, 230,20, 60);
	// i ellipse(480, 175, 105, 255,40, 120);
	}
	for(int i = 0; i <13; i++){
		moveto(225+(70*i), 350);
		lineto(245+(70*i),350);
	}
	for(int i = 0; i <8; i++){
		moveto(480, 95+(70*i));
		lineto(480,115+(70*i));
	}
	
	arc(480, 350, 277, 353, 210);
	ellipse(480, 350, 3, 80,420, 140);
	ellipse(480, 350, 185, 260,280, 140);
	ellipse(480, 350, 280, 358,560, 140);
	ellipse(480, 280, 277, 83,110, 210);
	
	moveto(499, 369);
	lineto(530,401);
	
	setfillstyle(1, YELLOW);
	
	fillellipse(499, 369, 3, 3);
	
	fillellipse(395, 328, 7, 7);
	fillellipse(465, 328, 7, 7);
	fillellipse(535, 328, 7, 7);
	
	fillellipse(425, 328, 7, 7);
	fillellipse(495, 328, 7, 7);
	fillellipse(565, 328, 7, 7);
	
	fillellipse(455, 263, 7, 7);
	fillellipse(455, 403, 7, 7);
	fillellipse(455, 363, 7, 7);
	fillellipse(455, 433, 7, 7);
	fillellipse(450, 490, 7, 7);
	
	fillellipse(510, 485, 7, 7);
	fillellipse(510, 555, 7, 7);
	
	for(int i = 0; i < 13; i++){
		if(i < 4)
			fillellipse(228+(70*i), 350, 3, 3);
		else
			fillellipse(243+(70*i), 350, 3, 3);
	}
	for(int i = 0; i < 8; i++){
		if(i < 4)
			fillellipse(480, 115+(70*i),3,3);
		else
			fillellipse(480, 113+(70*i),3,3);
	}
	
	outtextxy(520, 380,"INICIO");
}

