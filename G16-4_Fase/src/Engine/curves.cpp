#include <stdlib.h>
#include "translateT.cpp"
#define _USE_MATH_DEFINES
#include <math.h>


// contruir uma matriz de rotacao
void buildRotMatrix(float* x, float* y, float* z, float* m) {
	
	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

// calcular normal de dois vectores
void cross(float* a, float* b, float* res) {

	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}

// Normalizar um vector
void normalize(float* a) {

	float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0] / l;
	a[1] = a[1] / l;
	a[2] = a[2] / l;
}

// Tamanho de um vector
float length(float* v) {

	float res = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	return res;

}

// Multiplicacao de uma matriz com um vector
void multMatrixVector(float* m, float* v, float* res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}
// Multiplicacao de um vector com um vector
void multVectorVector(float* m, float* v, float* res) {

	res[0] = 0;
	for (int k = 0; k < 4; ++k) {
		res[0] += v[k] * m[k];
	}

}


void getCatmullRomPoint(float t, float* p0, float* p1, float* p2, float* p3, float* pos, float* deriv) {

	// catmull-rom matrix
	float m[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f} };

	for (int i = 0; i < 3; i++)
	{
		// Compute A = M * P
		float a[4];
		float p[4] = { p0[i], p1[i], p2[i], p3[i] };
		multMatrixVector(reinterpret_cast<float(&)[16]>(m), p, a);

		// Compute pos = T * A
		float T[4] = { pow(t,3), pow(t,2), t, 1 };
		multVectorVector(T, a, pos + i);

		// compute deriv = T' * A
		float Tl[4] = { 3 * pow(t,2), 2 * t, 1, 0 };
		multVectorVector(Tl, a, deriv + i);
	}
}

// given global t, returns the point in the curve
void getGlobalCatmullRomPoint(float gt, float* pos, float* deriv, TranslateT tt) {
	int point_count = tt.points.size();
	float t = gt * point_count; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within the segment
	
	// indices store the points
	int indices[4];
	indices[0] = (index + point_count - 1) % point_count;
	indices[1] = (indices[0] + 1) % point_count;
	indices[2] = (indices[1] + 1) % point_count;
	indices[3] = (indices[2] + 1) % point_count;
	getCatmullRomPoint(t, tt.pointmatrix[indices[0]].p, tt.pointmatrix[indices[1]].p, tt.pointmatrix[indices[2]].p, tt.pointmatrix[indices[3]].p, pos, deriv);
}

