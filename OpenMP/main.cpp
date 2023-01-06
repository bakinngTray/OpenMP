#include <iostream>
#include <omp.h>
#include <time.h>
#include <math.h>
using namespace std;


void mul_matrix_parallel(float** A, float** B, float** C, int N) {
#pragma omp parallel for shared(A, B, C)
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			C[i][j] = 0.0;
			for (int k = 0; k < N; k++) C[i][j] += A[i][k] * B[k][j];
		}
	}
}


int get_matrix_size() {
	int matrix_size;
	cout << "¬ведите размер матрицы:";
	cin >> matrix_size;
	return matrix_size;
}


int get_threads_number() {
	int num_of_threads;
	string input;
	bool exit = false;
	int max_threads = omp_get_num_procs();
	cout << "—истеме доступно " << max_threads << " потоков" << endl;
	cout << "¬ведите кол-во потоков дл€ работы:";
	cin >> num_of_threads;
	num_of_threads = min(max_threads, max(1, num_of_threads));
	return num_of_threads;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	int N;
	float t_start;

	N = 1500;
	cout << "" << endl;
	omp_set_num_threads(get_threads_number());
	cout << "" << endl;

	float** a, ** b, ** c;
	a = new float* [N];
	for (int i = 0; i < N; i++)
		a[i] = new float[N];
	b = new float* [N];
	for (int i = 0; i < N; i++)
		b[i] = new float[N];
	c = new float* [N];
	for (int i = 0; i < N; i++)
		c[i] = new float[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			a[i][j] = 2.0;
			b[i][j] = 5.0;
		}

	t_start = omp_get_wtime();
	mul_matrix_parallel(a, b, c, N);
	cout << "¬рем€ вычислени€ = " << omp_get_wtime() - t_start << endl;
}