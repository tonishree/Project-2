#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#define MAX_LENGTH 23 //Độ dài của số

void Normalize(short* &a) //Hàm chuẩn hóa các số nguyên "lớn" (xóa cái số 0 ở đầu mảng)
{
	int count = 0;
	for (int i = 2; i < *(a + 1); i++)
		{
			if (*(a + i) == 0)
			{
				count++;
			}
			else break;
		}
	if (*(a + 1) == count)
	{
		*(a + 0) = *(a + 1) = 1;
		*(a + 2) = 0;
		a = (short*)realloc(a, sizeof(short)* 3);
	}
	else
	{
		*(a + 1) -= count;
		int m = *(a + 1) + 2;
		for (int i = 2; i < m; i++)
		{
			*(a + i) = *(a + i + count);
		}
		a = (short*)realloc(a, sizeof(short)*m);
	}
}

short* RandomNum() //Hàm phát sinh ngẫu nhiên 1 số nguyên "lớn"
{
	short* nb;
	int n = 1 + rand() % MAX_LENGTH; //Độ dài số từ 1 - MAX_LENGTH đơn vị
	nb = (short*)malloc(sizeof(short)*(n + 2));
	*(nb) = rand() % 2; //Quy ước 0 là âm, 1 là dương
	*(nb + 1) = n;
	for (int i = 2; i < n + 2; i++)
	{
		*(nb + i) = rand() % 10; //Mỗi đơn vị của số ngẫu nhiên từ 0 - 9
	}
	Normalize(nb);
	return nb;
}

void RandomArray(short** &a,int N) //Hàm phát sinh mảng số nguyên "lớn"
{
	a = (short**)malloc(sizeof(short*)*N);
	for (int i = 0; i < N; i++)
	{
		*(a + i) = RandomNum();
	}
}

void printArray(short** a,int N) //Hàm in mảng số nguyên (mỗi phần tử cách nhau 1 khoảng trắng "_")
{
	int M;
	for (int i = 0; i < N; i++)
	{
		if (a[i][0])
		{
			M = a[i][1];
			for (int j = 2; j < M + 2; j++)
			{
				printf("%d", a[i][j]);
			}
		}
		else
		{
			printf("-");
			M = a[i][1];
			for (int j = 1; j < M + 2; j++)
			{
				printf("%d", a[i][j]);
			}
		}
		printf(" ");
	}
	printf("\n");
}

bool Larger(short* a, short* b) //Quy ước a>b = true, a<=b = false
{
	int n = a[1] + 2;
	if (a[0] > b[0]) return true;
	else {
		if (a[0] < b[0]) return false;
		else
		if (a[0] == 1){
			if (a[1] > b[1]) return true;
			else
			{
				if (a[1] < b[1]) return false;
				else
				{
					for (int i = 2; i < n; i++)
					{
						if (a[i] > b[i])
							return true;
						else
						if (a[i] < b[i])
							return false;
					}
				}
			}
		}
		else
		{
			if (a[1] < b[1]) return true;
			else
			{
				if (a[1] > b[1]) return false;
				else
				{
					for (int i = 2; i < n; i++)
					{
						if (a[i] < b[i])
							return true;
						else
						if (a[i] > b[i])
							return false;
					}
				}
			}
		}
	}
	return false;
}

void InsertionSort(short** &a,int N,unsigned long long &Giving,unsigned long long &Compare)
{
	short n;
	int j;
	short* x;
	for (int i = 0; i < N; i++)
	{
		n = a[i][1] + 2;
			x = a[i];
			j = i - 1;
			Compare++;
			while ((j >= 0) && (Larger(a[j], x)))
			{
				a[j + 1] = a[j];
				Giving++;
				j--;
			}
			a[j + 1] = x;
			Giving++;
	}
}

void swap(short* &a, short* &b)
{
	short* temp = a;
	a = b;
	b = temp;
}

void BubbleSort(short** &a, int N,unsigned long long &giving, unsigned long long &compare)
{
	for (int i = 1; i < N; i++)
	for (int j = N - 1; j >= i; j--)
	{
		compare++;
		if (Larger(a[j - 1], a[j]))
		{
			swap(a[j - 1], a[j]);
			giving += 3;
		}
	}
}

void ShakeSort(short** &a, int N,unsigned long long &giving,unsigned long long &compare)
{
	int left = 1, right = N - 1, j, k;
	do
	{
		for (j = right; j >= left; j--){
			compare++;
			if (Larger(a[j - 1], a[j]))
			{
				swap(a[j], a[j - 1]);
				giving += 3;
				k = j;
			}
		}
		left = k + 1;
		for (j = left; j <= right; j++){
			compare++;
			if (Larger(a[j - 1], a[j]))
			{
				swap(a[j], a[j - 1]);
				giving += 3;
				k = j;
			}
		}
		right = k - 1;
	} while (left <= right);
}

void QuickSort(short** &a, int l, int r,unsigned long long &giving,unsigned long long &compare)
{
	int i = l;int j = r;short* x = a[(l + r) / 2];
	do {
		compare++;
		while (Larger(x, a[i])) {
			compare++; i++;
		}
		compare++;
		while (Larger(a[j], x)) {
			compare++; j--;
		}
		if (i <= j){
			swap(a[i], a[j]);
			i++; j--; giving += 3;
		}
	} while (i < j);
	if (l < j)
		QuickSort(a, l, j,giving,compare);
	if (i < r)
		QuickSort(a, i, r,giving,compare);
}

void ShellSort(short** arr, int n,unsigned long long &giving, unsigned long long &compare)
{
	// Bắt đầu với khoảng cách lớn, sau đó rút khoảng cách lại
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		// Xét mảng với khoảng cách gap hiện tại.

		for (int i = gap; i < n; i += 1)
		{
			 
			short* temp = arr[i];
			giving++;

			int j;
			compare++;
			for (j = i; j >= gap && Larger(arr[j - gap], temp); j -= gap)
			{
				arr[j] = arr[j - gap];
				giving++;
				compare++;
			}

			arr[j] = temp;
			giving++;
		}
	}
}

// Merge 2 mảng con của a.
// Mảng con đầu tiên là a[l..m]
// Mảng thứ hai là a[m+1..r]
void Merge(short** &arr, int l, int m, int r, unsigned long long &giving, unsigned long long &compare)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* Tạo các mảng tạm thời */
	short** L = (short**)malloc(sizeof(short*)*(n1));
	short** R = new short*[n2];

	/* Gán giá trị cho các mảng L, R */
	for (i = 0; i < n1; i++)
	{
		L[i] = arr[l + i];
		giving++;
	}
	for (j = 0; j < n2; j++)
	{
		R[j] = arr[m + 1 + j];
		giving++;
	}

	/* Hợp nhất các mảng tạm thời thành mảng a*/
	i = 0; 
	j = 0; 
	k = l; 
	while (i < n1 && j < n2)
	{
		compare++;
		if (!Larger(L[i],R[j]))
		{
			arr[k] = L[i];
			giving++;
			i++;
		}
		else
		{
			arr[k] = R[j];
			giving++;
			j++;
		}
		k++;
	}

	/* Copy các phần tử còn lại của L, nếu còn */
	while (i < n1)
	{
		arr[k] = L[i];
		giving++;
		i++;
		k++;
	}

	/* Copy các phần tử còn lại của R, nếu còn */
	while (j < n2)
	{
		arr[k] = R[j];
		giving++;
		j++;
		k++;
	}
}

void MergeSort(short** arr, int l, int r, unsigned long long &giving, unsigned long long &compare)
{
	if (l < r)
	{

		int m = l + (r - l) / 2;

		MergeSort(arr, l, m,giving,compare);
		MergeSort(arr, m + 1, r,giving,compare);

		Merge(arr, l, m, r,giving,compare);
	}
}

void Heapify(short** arr, int n, int i, unsigned long long &giving, unsigned long long &compare)
{
	int largest = i;  // Initialize largest as root
	int l = 2 * i + 1;  // left = 2*i + 1
	int r = 2 * i + 2;  // right = 2*i + 2

	// If left child is larger than root
	compare++;
	if (l < n && Larger(arr[l], arr[largest]))
		largest = l;

	// If right child is larger than largest so far
	compare++;
	if (r < n && Larger(arr[r], arr[largest]))
		largest = r;

	// If largest is not root
	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		giving += 3;

		Heapify(arr, n, largest,giving,compare);
	}
}

// main function to do heap sort
void HeapSort(short** arr, int n, unsigned long long &giving, unsigned long long &compare)
{
	// Build heap (rearrange array)
	for (int i = n / 2 - 1; i >= 0; i--)
		Heapify(arr, n, i,giving,compare);

	// One by one extract an element from heap
	for (int i = n - 1; i >= 0; i--)
	{
		// Move current root to end
		swap(arr[0], arr[i]);
		giving += 3;
		// call max heapify on the reduced heap
		Heapify(arr, i, 0,giving,compare);
	}
}

short GetMax(short** a, int N)
{
	short mx = a[0][1];
	for (int i = 1; i < N; i++)
	{
		if (a[i][1] > mx)
			mx = a[i][1];
	}
	return mx;
}

void Count(short** a, int N, int &pos, int &neg)
{
	for (int i = 0; i < N; i++)
	{
		if (a[i][0] == 1) pos++;
		else neg++;
	}
}

void createSubArray(short** a, int N, short** pos, short** neg)
{
	int m = 0, n = 0;
	for (int i = 0; i < N; i++)
	{
		if (a[i][0] == 1)
		{
			pos[m] = new short[a[i][1] + 2];
			for (int j = 0; j < a[i][1] + 2; j++)
			{
				pos[m][j] = a[i][j];
			}
			m++;
		}
		else
		{
			neg[n] = new short[a[i][1] + 2];
			for (int j = 0; j < a[i][1] + 2; j++)
			{
				neg[n][j] = a[i][j];
			}
			n++;
		}
	}
}

void CountSort(short** &a, int N, short exp, unsigned long long &giving, unsigned long long &compare)
{
	short** output = (short**)malloc(sizeof(short*)*N);
	short n, m;
	int i, count[10] = { 0 };
	for (i = 0; i < N; i++)
	{
		n = a[i][1];
		if (n + exp < 2) count[0]++;
		else
		{
			m = a[i][n + exp];
			count[m]++;
		}
	}

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = N - 1; i >= 0; i--)
	{
		n = a[i][1];
		if (n + exp < 2)
		{
			output[count[0] - 1] = a[i];
			giving++;
			count[0]--;
		}

		else{
			m = a[i][n + exp];
			output[count[m] - 1] = a[i];
			giving++;
			count[m]--;
		}
	}

	for (i = 0; i < N; i++){
		a[i] = output[i];
		giving++;
	}
	free(output);
}

void Linking(short** a, short** pos, short** neg, int m, int n, unsigned long long &giving, unsigned long long &compare)
{
	int k = 0;
	for (int i = m - 1; i >= 0; i--)
	{
		a[k] = neg[i];
		giving++;
		k++;
	}
	for (int j = 0; j < n; j++)
	{
		a[k]=pos[j];
		giving++;
		k++;
	}
}

void RadixSort(short** a, int N, unsigned long long &giving, unsigned long long &compare)
{
	int pos, neg;
	pos = neg = 0;
	Count(a, N, pos, neg);
	short**L = (short**)malloc(sizeof(short*)*neg);
	short**R = (short**)malloc(sizeof(short*)*pos);
	createSubArray(a, N, R, L);
	short m = GetMax(L, neg);
	short n = GetMax(R, pos);
	for (short exp1 = 1; m + exp1 >= 2; exp1--)
		CountSort(L, neg, exp1,giving,compare);
	for (short exp2 = 1; n + exp2 >= 2; exp2--)
		CountSort(R, pos, exp2,giving,compare);
	Linking(a, R, L, neg, pos,giving,compare);
	free(L);
	free(R);
}

void chooseN(int &N){
	int temp;
	printf("Chon so luong phan tu N\n");
	printf("1.N=100\n");
	printf("2.N=1000\n");
	printf("3.N=10000\n");
	printf("4.N=100000\n");
	printf("5.N=1000000\n");
	while (1)
	{
		temp = toupper(_getch());
		if (temp == '1')
		{
			N = 100;
			system("cls");
			break;
		}
		else if (temp == '2')
		{
			N = 1000;
			system("cls");
			break;
		}
		else if (temp == '3')
		{
			N = 10000;
			system("cls");
			break;
		}
		else if (temp == '4')
		{
			N = 100000;
			system("cls");
			break;
		}
		else if (temp == '5')
		{
			N = 1000000;
			system("cls");
			break;
		}
	}
}

void chooseSort(short** a,int N,unsigned long long &giving,unsigned long long &compare,clock_t &begin,clock_t &end)
{
	int temp;
	printf("Thuat toan ap dung de sap xep: %d PHAN TU\n",N);
	printf("1.Insertion Sort\n");
	printf("2.Bubble Sort\n");
	printf("3.Shake Sort\n");
	printf("4.Quick Sort\n");
	printf("5.Shell Sort\n");
	printf("6.Merge Sort\n");
	printf("7.Heap Sort\n");
	printf("8.Radix Sort\n");
	while (1)
	{
		temp = toupper(_getch());
		if (temp == '1')
		{
			system("cls");
			begin = clock();
			InsertionSort(a, N, giving, compare);
			end = clock();
			break;
		}
		else if (temp == '2')
		{
			system("cls");
			begin = clock();
			BubbleSort(a, N, giving, compare);
			end = clock();
			break;
		}
		else if (temp == '3')
		{
			system("cls");
			begin = clock();
			ShakeSort(a, N, giving, compare);
			end = clock();
			break;
		}
		else if (temp == '4')
		{
			system("cls");
			begin = clock();
			QuickSort(a, 0, N - 1, giving, compare);
			end = clock();
			break;
		}
		else if (temp == '5')
		{
			system("cls");
			begin = clock();
			ShellSort(a, N, giving, compare);
			end = clock();
			break;
		}
		else if (temp == '6')
		{
			system("cls");
			begin = clock();
			MergeSort(a, 0, N - 1, giving, compare);
			end = clock();
			break;
		}
		else if (temp == '7')
		{
			system("cls");
			begin = clock();
			HeapSort(a, N, giving, compare);
			end = clock();
			break;
		}
		else if (temp == '8')
		{
			system("cls");
			begin = clock();
			RadixSort(a, N, giving, compare);
			end = clock();
			break;
		}
	}
}

void truePrint(short** a, int N)
{
	int temp;
	printf("Da sap xep xong! Ban co muon in mang ra?\n");
	printf("0.Khong - 1.Co\n");
	while (1)

	{
		temp = toupper(_getch());
		if (temp == '1')
		{
			system("cls");
			printArray(a, N);
			break;
		}
		else if (temp == '0')
		{
			system("cls");
			break;
		}
	}
}

void main()
{
	srand(time(NULL));
	short** a;
	int N;
	unsigned long long giving = 0;
	unsigned long long compare = 0;
	chooseN(N);
	RandomArray(a, N);
	clock_t begin, end;
	chooseSort(a, N, giving, compare, begin, end);
	truePrint(a, N);
	float sec = (float)(end - begin) / CLOCKS_PER_SEC;
	printf("Time run: %0.14f sec\n", sec);
	printf("So phep gan: %ld\n", giving);
	printf("So phep so sanh: %ld\n", compare);
	free(a);
}
