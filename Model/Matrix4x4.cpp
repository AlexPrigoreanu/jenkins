#include "Matrix4x4.h"

/*
Matrix4x4::Matrix4x4(){
	// prima riga
	values[0][1]=1;
	values[0][2]=0;
	values[0][3]=0;
	values[0][0]=0;
	// seconda riga
	values[1][1]=0;
	values[1][2]=1;
	values[1][3]=0;
	values[1][0]=0;
	// terza riga
	values[2][1]=0;
	values[2][2]=0;
	values[2][3]=1;
	values[2][0]=0;
	// quarta riga
	values[3][1]=0;
	values[3][2]=0;
	values[3][3]=0;
	values[3][0]=1;
}

Matrix4x4::Matrix4x4(   double v11, double v12, double v13, double v14,
						double v21, double v22, double v23, double v24,
						double v31, double v32, double v33, double v34,
						double v41, double v42, double v43, double v44){
	// prima riga
	values[0][1]=v11;
	values[0][2]=v12;
	values[0][3]=v13;
	values[0][0]=v14;
	// seconda riga
	values[1][1]=v21;
	values[1][2]=v22;
	values[1][3]=v23;
	values[1][0]=v24;
	// terza riga
	values[2][1]=v31;
	values[2][2]=v32;
	values[2][3]=v33;
	values[2][0]=v34;
	// quarta riga
	values[3][1]=v41;
	values[3][2]=v42;
	values[3][3]=v43;
	values[3][0]=v44;
}

double Matrix4x4::getElement(int x, int y){
	return values[x][y];
}

void Matrix4x4::setElement(int x, int y, double v){
	values[x][y]=v;
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4 factor){
	Matrix4x4 result(0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0);		
	for (int i = 0; i < 4; i++){ // riga
		for (int j = 0; j < 4; j++){ // colonna
			for (int k = 0; k < 4; k++){ // indice somma parziale
				result.setElement(i, j, result.getElement(i,j)+values[i][k]*factor.getElement(k,j));
			}
		}
	}
	return result;
}

Matrix4x4 Matrix4x4::operator*=(Matrix4x4 factor){
	Matrix4x4 result = *this * factor;
	for (int i = 0; i < 4; i++){ // riga
		for (int j = 0; j < 4; j++){ // colonna
			values[i][j] = risultato.getElement(i, j);
		}
	}
    return *this;
}

void Matrix4x4::transpose(){
	double temp = 0;
	for (int i = 0; i < 4; i++){ // riga
		for (int j = i; j < 4; j++){ // colonna
			if (i != j){
				temp = values[i][j];
				values[i][j] = values[j][i];
				values[j][i] = temp;
			}
		}
	}
}*/


