#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-9;
double min_ratio = 1e18;

//PLANTILLAS DE FUNCIONES
void imprimirTabla(vector<vector<double>>&, short&, short&);
int calcularColP(vector<vector<double>>&);
int calcularFilP(vector<vector<double>>&, int&);
vector<vector<double>> nuevaT(vector<vector<double>>&, double&, int&, int&);

int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    short n, m;
    cin>>n >>m;

    vector<vector<double>> datos (m, vector<double>(n+1, 0));
    vector<double> funcion;
    funcion.resize(n+1);
    string des;

    //ENTRADA DE DATOS
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin>>datos[i][j];
        }
        cin>>des;
        cin>>datos[i][n];
         
        if (des == ">=") {
            for (int j = 0; j < n+1; j++) {
                datos[i][j] *= -1;
            }
        }
    }
    //INGRESA FUNCIÓN
    funcion[0] = 1;
    for (int k = 1; k < n+1; k++) {
        cin>>funcion[k];
        funcion[k] *= -1;
    }

    //Llenamos la matriz
    vector<vector<double>> tabla(m+1, vector<double>(n+m+2,0));
    vector<vector<double>> MatPart2(m, vector<double>(m+1,0));

    for(int i=0;i<m;i++){
        for(int j=0;j<m+1;j++){
            if(i==j){
                MatPart2[i][j]=1;
            }else if(j==(m)){
                MatPart2[i][j]=datos[i][n];
            }
        }
    }

    tabla[0][0]=1;
    for(int i=0;i<m+1;i++) {
        for(int j=1; j<n+1;j++) {
            if(i != 0) {
                tabla[i][j] = datos[i-1][j-1];
            } else {
                tabla[i][j] = funcion[j];
            }
        }
    }

    for (int i=1;i<m+1;i++) {
        for (int j=n+1; j<n+m+2; j++) {
            tabla[i][j]=MatPart2[i-1][j-n-1];
        }
    }
    //Terminamos de llenar la matriz

    //imprimirTabla(tabla, m, n);

    int count=0;
    vector<double> solu;
    for (int i = 1; i < tabla.size(); i++) {
        count++;
        bool bandera = false;
        int c = calcularColP(tabla);
        int f = calcularFilP(tabla, c);
        double elementoP = tabla[f][c];

        tabla = nuevaT(tabla, elementoP, f, c);
        //imprimirTabla(tabla, m, n);

        for (int j = 1; j < n+1; j++) {
            if (tabla[0][j] == 0) {
                bandera = true;
            } else {
                bandera = false;
            }
        }

        if (bandera) {
            for (int k = 0; k < n + 1; k++) { //col
                for (int l = 0; l < tabla.size(); l++) { //filas
                    if (tabla[l][k] == 1) {
                        solu.push_back(tabla[l][tabla[0].size() - 1]);
                    }
                }
            }
            break;
        }
    }

    //cout<< "Count = " <<count <<'\n';
    for (int i = 1; i < count+1; i++) {
        cout<< fixed <<setprecision(9) <<solu[i] <<'\n';
    }
    cout<< fixed <<setprecision(9) <<solu[0] <<'\n';

   return 0;
}


void imprimirTabla(vector<vector<double>> &tabla, short &m, short &n) {
    //IMPRIMIMOS TABLA
    cout<<"\n";
    for(int i=0;i<m+1;i++){
        for(int j=0;j<n+m+2;j++){
            cout<<tabla[i][j]<<'\t';
        }
        cout<<"\n";
    }
}

int calcularColP(vector<vector<double>> &matriz) {
    int indiceC = 1;

    for (int i = 1; i < matriz[0].size()-1; i++) {
        if (matriz[0][i] < matriz[0][indiceC]) {
            indiceC = i;
        }
    }

    return indiceC;
}

int calcularFilP(vector<vector<double>> &matriz, int &indiceC) {
    int indiceF = 1;
    float menorP = 0, divi;
    for (int i = 1; i < matriz.size(); i++) {
        if (matriz[i][matriz[0].size()-1] != 0) {
            divi = matriz[i][matriz[0].size()-1] / matriz[i][indiceC];
            if (divi > 0 && i == 1) {
                menorP = divi;
                indiceF = i;
            } else if (divi > 0 && divi < menorP) {
                menorP = divi;
                indiceF = i;
            }
        }
    }

    return indiceF;
}

vector<vector<double>> nuevaT(vector<vector<double>> &matriz, double &elementoP, int &f, int &c) {
    vector<vector<double>> nMatriz = matriz;
    double coef = 0;

    for (int j = 0; j < nMatriz[f].size(); j++) {
        if (nMatriz[f][j] != 0) {
            nMatriz[f][j] = nMatriz[f][j] / elementoP;
        } else {
            nMatriz[f][j] = 0;
        }
    }

    for (int i = 0; i < nMatriz.size(); i++) {
        coef = nMatriz[i][c];
        for(int j = 0; j < nMatriz[f].size(); j++) {
            if (i != f) {
                nMatriz[i][j] = nMatriz[i][j] - (coef * nMatriz[f][j]);
            }
        }
    }

    return nMatriz;
}
