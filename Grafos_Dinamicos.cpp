#include "MiniWin.h"
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<iostream>
#include<cmath>
#include<windows.h>
#include<cstdio>

using namespace std;
using namespace miniwin;
HWND hwnd;

int xVertice = 100;
int yVertice = 100;
int indice = 0;

void NewVertice(int v) {
    double angulo = 2 * M_PI * indice / v;
    xVertice = 500 + 240 * cos(angulo);
    yVertice = 300 + 240 * sin(angulo);
}

void DibujarFlecha(int xI, int yI, int xF, int yF) {
    double angulo = atan2(yF - yI, xF - xI);
    double longitudFlecha = 15.0;
    double anguloFlecha = M_PI / 6;

    int xM = (xI + xF) / 2;
    int yM = (yI + yF) / 2;

    int x3 = xM - longitudFlecha * cos(angulo + anguloFlecha);
    int y3 = yM - longitudFlecha * sin(angulo + anguloFlecha);

    int x4 = xM - longitudFlecha * cos(angulo - anguloFlecha);
    int y4 = yM - longitudFlecha * sin(angulo - anguloFlecha);

    linea(xM, yM, x3, y3);
    linea(xM, yM, x4, y4);
}

void DibujarVertice(char *n,int v){
    NewVertice(v);
    color(AZUL);
    circulo_lleno(xVertice,yVertice,20);
    color(BLANCO);
    char c = *n;
    string s;
    s.push_back(c);
    texto(xVertice-4,yVertice-10,s);

}

void DibujarArista(int xI, int yI, int xF, int yF, char*n){
    char c = *n;
    string s;
    s.push_back(c);



    if (xI == xF && yI == yF) {
        int numSegments = 10;
        float segmentLength = 1.0/ numSegments;

        int colors[10][3] = {
                {204, 255, 0},
                {0, 0, 255},
                {0, 0, 255},
                {0, 0, 255},
                {0, 102, 153},
                {0, 204, 51},
                {0, 255, 0},
                {51, 255, 0},
                {102, 255, 0},
                {153, 255, 0}
        };

        float angleStep = 2 * M_PI / numSegments;
        int radio = 20;
        int xc = xI;
        int yc = yI-20;
        for (int i = 0; i < numSegments; ++i) {
            float startAngle = i * angleStep;
            float endAngle = (i + 1) * angleStep;

            int xStart = xc + radio * cos(startAngle);
            int yStart = yc + radio * sin(startAngle);
            int xEnd = xc + radio * cos(endAngle);
            int yEnd = yc + radio * sin(endAngle);

            color_rgb(colors[i][0], colors[i][1], colors[i][2]);
            linea(xStart, yStart, xEnd, yEnd);
        }

        texto(xc-4, yc - radio - 13, s);
    }

    else {
        int numSegments = 10;
        float segmentLength = 1.0/ numSegments;

        int colors[10][3] = {
                {0, 0, 255},
                {0, 51, 204},
                {0, 102, 153},
                {0, 153, 102},
                {0, 204, 51},
                {0, 255, 0},
                {51, 255, 0},
                {102, 255, 0},
                {153, 255, 0},
                {204, 255, 0}
        };

        for (int i = 0; i < numSegments; ++i) {
            float startRatio = i * segmentLength;
            float endRatio = (i + 1) * segmentLength;

            int xStart = xI + (xF - xI) * startRatio;
            int yStart = yI + (yF - yI) * startRatio;
            int xEnd = xI + (xF - xI) * endRatio;
            int yEnd = yI + (yF - yI) * endRatio;

            color_rgb(colors[i][0], colors[i][1], colors[i][2]);
            linea(xStart, yStart + 7, xEnd, yEnd + 7);
            if(i==9){
                DibujarFlecha(xStart, yStart + 7, xEnd, yEnd + 7);
            }
        }

        texto(((xI + xF) / 2), ((yI + yF) / 2)-5, s);
    }
}

class arista;
class vertice{

	public:
	vertice*sig;
	char*Etiqueta;
	arista*ini;
	int X_pos;
	int Y_pos;
	vertice(char*eti)
	{
		ini=NULL;
		sig=NULL;
		X_pos=Y_pos=0;
		Etiqueta=new char[strlen(eti)+1];
		strcpy(Etiqueta,eti);
	}
};

class arista{
	public:
	arista*sig;
	char*Etiqueta;
	vertice*ultimo;
	arista(vertice*ult,char*eti)
	{
		sig=NULL;
		ultimo=ult;
		Etiqueta= new char[strlen(eti)+1];
		strcpy(Etiqueta,eti);
	}
};

class grafo{
	public:
	vertice*ini;
    int numVertices;
	grafo(){
		ini=NULL;
		numVertices = 0;
	}

	void ponVertice(char*vt){
		if(ini==NULL)
		{
			ini=new vertice(vt);
		}
		else
		{
		    vertice*tmp;
			for(tmp=ini;tmp->sig!=NULL;tmp=tmp->sig);
			tmp->sig=new vertice(vt);
		}
		numVertices++;
	}

	void ponArista(char*v1,char*v2,char*eti){
		arista*tmp3;
		vertice*tmp=ini,*tmp2=ini;
		while(tmp->sig!=NULL&&strcmp(tmp->Etiqueta,v1)!=NULL)
			tmp=tmp->sig;
		while(tmp2->sig!=NULL&&strcmp(tmp2->Etiqueta,v2)!=NULL)
			tmp2=tmp2->sig;

		if(strcmp(tmp->Etiqueta,v1)==0&&strcmp(tmp2->Etiqueta,v2)==0)
		{

			if(tmp->ini==NULL)
			{    tmp->ini=new arista(tmp2,eti);
				  tmp3=tmp->ini;
			}
			else
			{
				tmp3=tmp->ini;
				while(tmp->ini->sig!=NULL)
					tmp->ini=tmp->ini->sig;
				tmp->ini->sig=new arista(tmp2,eti);
			}
			tmp->ini=tmp3;
		}
		else
		{
			cout<<"No existe nexo"<<endl;
			getch();
		}
	}

	void mostrarRelacion(){
	    cout<<endl<<"G:={";
		for(vertice *tmp=ini;tmp!=NULL;tmp=tmp->sig)
		{
			for(arista *tmp3=tmp->ini;tmp3!=NULL;tmp3=tmp3=tmp3->sig)
			{
				cout<<"("<<tmp->Etiqueta<<","<<tmp3->ultimo->Etiqueta<<")\t";
			}
			cout<<"\n";
		}
		cout<<"}"<<endl;;
	}

    char* eliminarArista(char* v1, char* v2) {
        vertice* tmp = ini;
        while (tmp != NULL && strcmp(tmp->Etiqueta, v1) != 0) {
            tmp = tmp->sig;
        }

        if (tmp == NULL) {
            cout << "El vértice de origen no existe." << endl;
            return NULL;
        }

        arista* tmp2 = NULL;
        arista* tmp3 = tmp->ini;

        while (tmp3 != NULL && strcmp(tmp3->ultimo->Etiqueta, v2) != 0) {
            tmp2 = tmp3;
            tmp3 = tmp3->sig;
        }

        if (tmp3 == NULL) {
            cout << "La arista no existe." << endl;
            return NULL;
        }

        if (tmp2 == NULL) {
            tmp->ini = tmp3->sig;
        } else {
            tmp2->sig = tmp3->sig;
        }
        char* A=tmp3->Etiqueta;
        delete[] tmp3->Etiqueta;
        delete tmp3;
        return A;
}

    char* eliminarVertice(char* v1) {
        vertice* tmp = ini;
        vertice* tmp2 = NULL;

        while (tmp != NULL && strcmp(tmp->Etiqueta, v1) != 0) {
            tmp2 = tmp;
            tmp = tmp->sig;
        }

        if (tmp == NULL) {
            cout << "No existe el vertice" << endl;
            return NULL;
        }

        for (vertice* tmp3 = ini; tmp3 != NULL; tmp3 = tmp3->sig) {
            eliminarArista(tmp3->Etiqueta, v1);
        }

        if (tmp2 == NULL) {
            ini = tmp->sig;
        } else {
            tmp2->sig = tmp->sig;
        }

        char* A = tmp->Etiqueta;
        delete[] tmp->Etiqueta;
        delete tmp;
        numVertices--;
        return A;
    }

    void CaminoMasCorto(char* v1, char* v2) {
        const int MAX_INT = 100;
        const int maxVertices = 20;

        vertice* vertices[maxVertices];
        int TotVertices = 0;
        for (vertice* tmp = ini; tmp != NULL; tmp = tmp->sig) {
            vertices[TotVertices++] = tmp;
        }

        int dist[maxVertices];
        bool procesados[maxVertices];
        vertice* previo[maxVertices];

        for (int i = 0; i < TotVertices; i++) {
            dist[i] = MAX_INT;
            procesados[i] = false;
            previo[i] = NULL;
        }

        vertice* origen = ini;
        int VertIni = -1;
        for (int i = 0; i < TotVertices; i++) {
            if (strcmp(vertices[i]->Etiqueta, v1) == 0) {
                origen = vertices[i];
                VertIni = i;
                dist[i] = 0;
                break;
            }
        }

        if (VertIni == -1) {
            cout << "El vértice inicial no existe" << endl;
            return;
        }

        /// Algoritmo de Dijkstra
        for (int i = 0; i < TotVertices - 1; i++) {
            int minDist = MAX_INT;
            vertice* u = NULL;
            int uIdx = -1;
            for (int j = 0; j < TotVertices; j++) {
                if (!procesados[j] && dist[j] <= minDist) {
                    minDist = dist[j];
                    u = vertices[j];
                    uIdx = j;
                }
            }

            if (u == NULL) break;

            procesados[uIdx] = true;

            for (arista* adj = u->ini; adj != NULL; adj = adj->sig) {
                vertice* v = adj->ultimo;
                int vIdx = -1;
                for (int j = 0; j < TotVertices; j++) {
                    if (vertices[j] == v) {
                        vIdx = j;
                        break;
                    }
                }

                int peso = 1; // Peso por defecto
                if (adj->Etiqueta != NULL && strcmp(adj->Etiqueta, " ") != 0) {
                    peso = atoi(adj->Etiqueta); // Convierte el char* a int
                }

                if (!procesados[vIdx] && dist[uIdx] != MAX_INT && dist[uIdx] + peso < dist[vIdx]) {
                    dist[vIdx] = dist[uIdx] + peso;
                    previo[vIdx] = u;
                }
            }
        }

        vertice* destino = ini;
        int destinoIdx = -1;
        for (int i = 0; i < TotVertices; i++) {
            if (strcmp(vertices[i]->Etiqueta, v2) == 0) {
                destino = vertices[i];
                destinoIdx = i;
                break;
            }
        }

        if (destinoIdx == -1) {
            cout << "El vértice destino no existe." << endl;
            return;
        }

        if (dist[destinoIdx] == MAX_INT) {
            cout << "No hay camino desde " << v1 << " a " << v2 << endl;
            return;
        }

        int camino[maxVertices];
        int caminoIdx = 0;
        vertice* tmp = destino;
        while (tmp != NULL) {
            camino[caminoIdx++] = destinoIdx;
            tmp = previo[destinoIdx];
            for (int i = 0; i < numVertices; i++) {
                if (vertices[i] == tmp) {
                    destinoIdx = i;
                    break;
                }
            }
        }
        cout << "El camino más corto desde " << v1 << " a " << v2 << " es: ";
        for (int i = caminoIdx - 1; i >= 0; i--) {
            cout << vertices[camino[i]]->Etiqueta;
            if (i > 0) cout << " --> ";
        }
        cout << " con una distancia de " << dist[camino[0]] << endl;

        color_rgb(255, 0, 0);
        for (int i = caminoIdx - 1; i > 0; i--) {
            int xStart = vertices[camino[i]]->X_pos;
            int yStart = vertices[camino[i]]->Y_pos;
            int xEnd = vertices[camino[i - 1]]->X_pos;
            int yEnd = vertices[camino[i - 1]]->Y_pos;
            linea(xStart, yStart, xEnd, yEnd);
        }
        refresca();
    }

    void DibujarGrafo() {
        vertice* tmp = ini;
        indice = 0;
        borra();
        for (tmp = ini; tmp != NULL; tmp = tmp->sig) {
            DibujarVertice(tmp->Etiqueta, numVertices);
            tmp->X_pos = xVertice;
            tmp->Y_pos = yVertice;
            indice++;
        }

        for(vertice *tmp2=ini;tmp2!=NULL;tmp2=tmp2->sig)
		{
			for(arista *tmp3=tmp2->ini;tmp3!=NULL;tmp3=tmp3->sig)
			{
			    DibujarArista(tmp2->X_pos,tmp2->Y_pos,tmp3->ultimo->X_pos,tmp3->ultimo->Y_pos,tmp3->Etiqueta);
			}
		}
		refresca();
    }

};

grafo Completo(grafo g1){
    g1.ponVertice("1");
    g1.ponVertice("2");
    g1.ponVertice("3");
    g1.ponVertice("4");

    g1.ponArista("1","2","2");
    g1.ponArista("1","3","3");
    g1.ponArista("1","4","2");

    g1.ponArista("2","1","2");
    g1.ponArista("2","3","2");
    g1.ponArista("2","4","3");

    g1.ponArista("3","1","3");
    g1.ponArista("3","2","2");
    g1.ponArista("3","4","2");

    g1.ponArista("4","1","2");
    g1.ponArista("4","2","3");
    g1.ponArista("4","3","2");

    g1.DibujarGrafo();
    return g1;
}

grafo Ejemplo(grafo g1){
    g1.ponVertice("1");
    g1.ponVertice("2");
    g1.ponVertice("3");
    g1.ponVertice("4");
    g1.ponVertice("5");

    g1.ponArista("1", "2", "1");
    g1.ponArista("1", "3", "3");
    g1.ponArista("1", "4", "7");
    g1.ponArista("2", "3", "4");
    g1.ponArista("3", "5", "7");
    g1.ponArista("4", "2", "3");
    g1.ponArista("4", "3", "2");
    g1.ponArista("4", "5", "9");
    g1.ponArista("5", "5", "8");
    g1.ponArista("1", "1", "2");
    g1.ponArista("5", "1", "1");

    g1.mostrarRelacion();
    g1.DibujarGrafo();

    getch();
    g1.eliminarVertice("1");
    g1.mostrarRelacion();
    g1.DibujarGrafo();

    getch();
    g1.eliminarArista("2", "3");
    g1.mostrarRelacion();
    g1.DibujarGrafo();

    g1.CaminoMasCorto("4", "1");
    return g1;
}

void moverConsola(int x, int y, int ancho, int alto) {
    HWND consola = GetConsoleWindow();
    SetWindowPos(consola, HWND_TOP, x, y, ancho, alto, SWP_SHOWWINDOW);
}

void moverVentanaMiniWin(int x, int y, int ancho, int alto) {
    HWND hwnd = GetForegroundWindow(); // Obtiene el identificador de la ventana activa, que debería ser la ventana de MiniWin
    if (hwnd) {
        SetWindowPos(hwnd, HWND_TOP, x, y, ancho, alto, SWP_NOZORDER | SWP_NOSIZE);
    }
}

int main() {
///Modificar las pocisiones de las ventanas
    moverConsola(100,550, 1016, 190);
    vredimensiona(1000, 550);
    moverVentanaMiniWin(100, -30, 1000, 600);

    grafo g1;

    g1 = Ejemplo(g1);
    //g1 = Completo(g1);

    int n = 0;
    int opc;
    char C1, C2, C3;
    char A[2], B[2], C[2];

    while (n == 0) {
        cout << "Desea realizar alguna operacion?: \n1:\tAgregar Vertice\n2:\tAgregar Arista\n3:\tEliminar Vertice\n4:\tEliminar Arista\n5:\tMostrar Recorrido Mas Corto\nOtro:\tSalir" << endl;
        cin >> opc;

        switch (opc) {
        case 1:
            cout << "Ingrese el identificador del vertice: ";
            cin >> C1;
            sprintf(A, "%c", C1);
            g1.ponVertice(A);
            g1.DibujarGrafo();
            break;

        case 2:
            cout << "Ingrese el primer vertice: ";
            cin >> C1;
            cout << "Ingrese el segundo vertice: ";
            cin >> C2;
            cout << "Ingrese el peso: ";
            cin >> C3;
            sprintf(A, "%c", C1);
            sprintf(B, "%c", C2);
            sprintf(C, "%c", C3);
            g1.ponArista(A, B, C);
            g1.DibujarGrafo();
            break;

        case 3:
            cout << "Ingrese el identificador del vertice a eliminar: ";
            cin >> C1;
            sprintf(A, "%c", C1);
            g1.eliminarVertice(A);
            g1.DibujarGrafo();
            break;

        case 4:
            cout << "Ingrese el primer vertice: ";
            cin >> C1;
            cout << "Ingrese el segundo vertice: ";
            cin >> C2;
            sprintf(A, "%c", C1);
            sprintf(B, "%c", C2);
            g1.eliminarArista(A, B);
            g1.DibujarGrafo();
            break;

        case 5:
            cout << "Ingrese el primer vertice: ";
            cin >> C1;
            cout << "Ingrese el segundo vertice: ";
            cin >> C2;
            sprintf(A, "%c", C1);
            sprintf(B, "%c", C2);
            g1.CaminoMasCorto(A, B);
            break;

        default:
            n = 1;
            break;
        }
        g1.mostrarRelacion();
    }
    vcierra();
    return 0;
}
