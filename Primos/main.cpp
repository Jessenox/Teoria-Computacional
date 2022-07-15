#include <iostream>
#include <fstream>
#include <cmath>
#include <bitset>
#include <string>>

using namespace std;

bool esPrimo(unsigned int);
void colocar(ofstream *, ofstream *, int);
void toBinario(ofstream *, unsigned int);
void loop();

int main(int argc, const char * argv[]) {
    loop();
    return 0;
}

void loop(){
	bool fin = false;
	while(!fin){
		int n;
		char opc;
	    ofstream file, file2;
	    file.open("file.txt");
	    file2.open("fileDecimal.txt");
	    cout << "Coloque la cantidad de primos: " << endl;
	    cin >> n;
	    colocar(&file, &file2, n);
	    file.close();
	    cout << "¿Desea calcular otra N? s/n" << endl;
	    cin >> opc;
	    if(opc == 'n')
	    	fin = true;
	    system("cls");
	}
	
}

void colocar(ofstream *file, ofstream *file2,int n){
    double c = 0;
    unsigned int i = 1, m = n +1, p = 1;
    *file << "{";
    *file2 << "{";
    char buffer[128];
    string str;
    while (true) {
    	if(i > 1)
	        if (esPrimo(i)) {
	            toBinario(file,i);
	            sprintf(buffer,"%d", i);
	            *file2 << buffer << ',';
	            c++;
	        }
        if(m == c) {
            *file << '}';
            *file2 << '}';
            break;
        }
        i++;
    }
}

bool esPrimo(unsigned int n){
    unsigned int i = 0, j = 0, c = 0, p= 1;
    bool no = false;
    while (i < n) {
    	j += p;
        if(n%j == 0){
        	c++;
        	if(j == 2 && n > 2){
        		no = true;
        		break;
			} else if(n>2 && j >2) p=2;
		}
        if (c>2) {
        	no = true;
        	break;
		}
		i+=p;
    }
    if (no)
        return false;
    else return true;
}

void toBinario(ofstream *f, unsigned int n){
    *f << ',';
    unsigned int i = 0, aux = n;
    bitset<64> fil(n);
    string t = fil.to_string();
    
    while (true) {
        if(t[i] != '0')
            break;
        i++;
    }
    aux = fil.size() - i;
    for(int j = 0; j < aux ; j++){
        *f << t[i + j];
        
    }
}
