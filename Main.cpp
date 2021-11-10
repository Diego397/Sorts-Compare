#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <cmath>

using namespace std;

bool verifica(int v[], int inicio, int fim) 		// funcao que retorna true caso o vetor esteja ordenado e falso senao estiver
{
	for (int i = inicio + 1; i <= fim; i++)
	{
		if(v[i-1] > v[i])
			return false;
	}
	return true;
}

int pivo (int inicio, int fim) 						//Funcao que retorna o pivo fixo
{
	// return inicio;
	return (inicio + fim) / 2;
	// return fim;
}

int pivo_r (int inicio, int fim) 					//Funcao que retorna o pivo aleatorio
{
	return inicio + rand() % (fim - inicio); 
}

void troca(int* a, int* b) 							//Funcao que faz a troca entre dois inteiros
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

int particao (int v[], int inicio, int fim, bool r) //Funcao que particiona um vetor e retorna o valor do indide do pivo
{
	int p;
	if (r) //se r == true, usaremos o pivo aleatorio. Senao, usaremos o pivo fixo
		p = v[pivo_r(inicio, fim)];
	else
		p = v[pivo(inicio, fim)];
	int i = (inicio - 1);
	for (int j = inicio; j <= fim; j++)
	{
		if (v[j] < p)
		{
			i++;
			troca(&v[i], &v[j]);
		}
	}
	for(int j = inicio; j <= fim; j++)
	{
		if(v[j] == p)
		{
			i++;
			troca(&v[j], &v[i]);
			break;
		}
	}
	return i;
}

void gerar_instancia_aleatoria(int v[], int n) 		//Funcao que gera a instacia aleatoria
{
	for (int i = 0; i < n; i++)
		v[i] = (rand() % (n * n)) + 1;
}

void gerar_pior_caso (int v[], int n) 				//Funcao que gera o pior caso para o QuickSort
{
	for (int i = 0; i < n; ++i) //inicializa o vetor com zeros
		v[i] = 0;

	for (int i = 0; i < n; ++i) 
	{
		int x = pivo(0, n - 1 - i);
		int cnt = 0;
		int j;
		for (j = 0; j <= x + cnt; ++j)
			if (v[j] != 0)
				cnt++;
		v[j - 1] = i + 1;
	}
}


void HeapSort (int v[], int n) 						//Funcao do Heapsort
{
	for (int j = n / 2; j >= 1; j--) //Cria a heap
	{
		int i = j;
		while (i + i <= n)
		{
			if (i + i == n || v[i + i] > v[i + i + 1])
			{
				if (v[i] < v[i + i])
				{
					troca(&v[i], &v[i + i]);
					i = i + i;
				}
				else
				{
					break;
				}
			}
			else
			{
				if (v[i] < v[i + i + 1])
				{
					troca(&v[i], &v[i + i + 1]);
					i = i + i + 1;
				}
				else
				{
					break;
				}
			}
		}
	}
	while (n > 1) //Ordena a heap
	{
		troca(&v[1], &v[n]);
		n--;
		int i = 1;
		while (i + i <= n)
		{
			if (i + i == n || v[i + i] > v[i + i + 1])
			{
				if (v[i] < v[i + i])
				{
					troca(&v[i], &v[i + i]);
					i = i + i;
				}
				else
				{
					break;
				}
			}
			else
			{
				if (v[i] < v[i + i + 1])
				{
					troca(&v[i], &v[i + i + 1]);
					i = i + i + 1;
				}
				else
				{
					break;
				}
			}
		}
	}
}

void HeapSort(int v[], int inicio, int fim) 		//Funcao para chamar a funcao heapsort com os parametros pedidos
{
	HeapSort (v + inicio - 1, fim - inicio + 1);
}

void QuickSort(int v[], int inicio, int fim, bool r) //Funcao quickSort onde se r == true, usaremos o pivo aleatorio. Senao, usaremos o pivo fixo
{
	if (inicio < fim)
	{
		int pi = particao(v, inicio, fim, r);
		QuickSort(v, inicio, pi - 1, r);
		QuickSort(v, pi + 1, fim, r);
	}
}

void InsertionSort(int v[], int inicio, int fim) 	//Funcao InsertionSort
{

	int esq = inicio;
	int dir = fim;
  
	for (int i = esq + 1; i <= dir; i++)
	{
		int valor = v[i];
		int j = i - 1;

		while (j >= esq && v[j] > valor)
		{
			v[j + 1] = v[j];
			j = j - 1;
		}
		v[j + 1] = valor;
	}
	return;
}

void IntroSortS(int v[], int inicio, int fim, int profundidade, int profundidademax) 		//Funcao IntroSort sem InsertionSort -> usa HeapSort
{
	int n = (fim - inicio + 1);
	if (profundidade == profundidademax || n <= 1)
		HeapSort(v, inicio, fim);
	else
	{
		int pi = particao(v, inicio, fim, false);

		IntroSortS(v, inicio, pi - 1, profundidade + 1, profundidademax);
		IntroSortS(v, pi + 1, fim, profundidade + 1, profundidademax); 
	}
}

void IntroSortC(int v[], int inicio, int fim, int profundidade, int profundidademax) 		//Funcao IntroSort com InsertionSort
{
	int n = (fim - inicio + 1);
	if (profundidade == profundidademax || n <= 1)
		InsertionSort(v, inicio, fim);
	else
	{
		int pi = particao(v, inicio, fim, false);
		
		IntroSortC(v, inicio, pi - 1, profundidade + 1, profundidademax);
		IntroSortC(v, pi + 1, fim, profundidade + 1, profundidademax);
	}
}

void IntroSortC(int v[], int inicio, int fim)		//Funcao para chamar IntroSortC corretamente onde log(n) * 2 e a profundidade maxima
{
	int n = fim - inicio + 1;
	IntroSortC(v, inicio, fim, 0, (log(n) * 2));
}

void IntroSortS(int v[], int inicio, int fim)		//Funcao para chamar IntroSortS corretamente
{
	int n = fim - inicio + 1;
	IntroSortS(v, inicio, fim, 0, (log(n) * 2));
}

void gerar_instancia_crescente(int v[], int n) 		//Funcao que gera a instacia aleatoria
{
	gerar_instancia_aleatoria(v, n);
	IntroSortS(v, 0, n -1);
}

void printavetor(int v[], int size) 				//Funcao que printa o vetor
{
	for (int i = 0; i < size; i++)
		cout <<  v[i] << " ";
	cout << "\n";
}

void gerar_instancia_decrescente(int v[], int n) 	//Funcao que gera a instacia aleatoria
{
	gerar_instancia_crescente(v, n);
	for (int i = 0; i < n / 2; i ++)
		troca(&v[i], &v[n - i - 1]);
}

void tempoGasto(int inicio, int fim, char y, int k) //Funcao que calcula o tempo gasto por cada algoritmo de ordenacao em K vezes, onde a variavel x e a responsavel por decidir qual algoritmo usar
{
	int n = (fim - inicio + 1);
	int *v, *v1, *v2, *v3, *v4, *v5;

	v = new int[n];
	v1 = new int[n];
	v2 = new int[n];
	v3 = new int[n];
	v4 = new int[n];
	v5 = new int[n];

	
	float tot1 = 0;
	float tot2 = 0;
	float tot3 = 0;
	float tot4 = 0;
	float tot5 = 0;
	
	bool flag = true;
	for (int i = 0; i < k; i++)
	{   
		if (y == 'A') 		gerar_instancia_aleatoria(v, n);								//Gera uma instancia aleatoria
		else if (y == 'P') 	gerar_pior_caso(v, n); 											//Gera o pior caso para QuickSort com pivo fixo
		else if (y == 'C') 	gerar_instancia_crescente(v, n);								//Gera uma instancia aleatoria em ordem crescente
		else if (y == 'D') 	gerar_instancia_decrescente(v, n);								//Gera uma instancia aleatoria em ordem decrescente

		for (int i = 0; i < n; i++)															//Copia os vetores
		{	
			v1[i] = v[i];
			v2[i] = v[i];
			v3[i] = v[i];
			v4[i] = v[i];
			v5[i] = v[i];
		}

		std::chrono::time_point<std::chrono::high_resolution_clock> t1, t2, t3, t4, t5; 	//declaracao das variaveis para medicao de tempo
		
		t1 = std::chrono::high_resolution_clock::now();										//Ponto de Inicio
		HeapSort(v1, inicio, fim); 															//heapSort
		std::chrono::duration<float> d1 = std::chrono::high_resolution_clock::now() - t1;	//Ponto Final
		tot1 = tot1 + d1.count();															//Soma dos intervalos
		
		t2 = std::chrono::high_resolution_clock::now();										//Ponto de Inicio
		QuickSort(v2, inicio, fim, false); 													//quickSort com pivo fixo
		std::chrono::duration<float> d2 = std::chrono::high_resolution_clock::now() - t2;	//Ponto Final
		tot2 = tot2 + d2.count();															//Soma dos intervalos

		t3 = std::chrono::high_resolution_clock::now();										//Ponto de Inicio
		QuickSort(v3, inicio, fim, true); 													//quickSort com pivo aleatorio
		std::chrono::duration<float> d3 = std::chrono::high_resolution_clock::now() - t3;	//Ponto Final
		tot3 = tot3 + d3.count();															//Soma dos intervalos

		t4 = std::chrono::high_resolution_clock::now();										//Ponto de Inicio
		IntroSortS(v4, inicio, fim);														//introSort sem Insertion sort
		std::chrono::duration<float> d4 = std::chrono::high_resolution_clock::now() - t4;	//Ponto Final
		tot4 = tot4 + d4.count();															//Soma dos intervalos

		t5 = std::chrono::high_resolution_clock::now();										//Ponto de Inicio
		IntroSortC(v5, inicio, fim);														//introSort com Insertion sort
		std::chrono::duration<float> d5 = std::chrono::high_resolution_clock::now() - t5;	//Ponto Final
		tot5 = tot5 + d5.count();															//Soma dos intervalos

		if (!verifica(v1, inicio, fim) || !verifica(v2, inicio, fim) || !verifica(v3, inicio, fim) || !verifica(v4, inicio, fim) || !verifica(v5, inicio, fim)) 
				flag = false;
	}
	if (flag) cout << "Vetores corretamente ordenados\n";
	
	else cout << "Vetores nao ordenados\n";
	
	cout << "HeapSort = " << tot1 << "\n";
	cout << "QuickSort com pivo fixo = " << tot2 << "\n";
	cout << "QuickSort com pivo aleatorio = " << tot3 << "\n";
	cout << "IntroSort com HeapSort = " << tot4 << "\n";
	cout << "IntroSort com InsertionSort = " << tot5 << "\n";

	delete[] v;
	delete[] v1;
	delete[] v2;
	delete[] v3;
	delete[] v4;
	delete[] v5;
}

int main(int argc, char *argv[])
{
	srand(time(NULL));

	if (argc != 4 || (argv[1][0] != 'A' && argv[1][0] != 'C' && argv[1][0] != 'D' && argv[1][0] != 'P'))
	{
		cout << "Parametros invalidos\n";
		return 1;
	}
	char y = argv[1][0];
	int n = atoi(argv[2]);
	int k = atoi(argv[3]);

	int ini = 0;
	int fim = n - 1;
	cout << "Calculando ...\n";
	tempoGasto(ini, fim, y, k);
}
