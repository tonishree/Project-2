#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

unsigned int RandomNum() //Hàm phát sinh ngẫu nhiên 1 số nguyên "lớn"
{
	unsigned int n = rand(); //Độ dài số từ 1 - MAX_LENGTH đơn vị
	return n;
}

void RandomArray(unsigned int* &a, int N) //Hàm phát sinh mảng số nguyên "lớn"
{
	a = (unsigned int*)malloc(sizeof(unsigned int)*N);
	for (int i = 0; i < N; i++)
	{
		*(a + i) = RandomNum();
	}
}

void printArray(unsigned int* a, int N) //Hàm in mảng số nguyên (mỗi phần tử cách nhau 1 khoảng trắng "_")
{
	int M;
	for (int i = 0; i < N; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void InsertionSort(unsigned int* &a, int N, unsigned long long &Giving, unsigned long long &Compare)
{
	int j;
	int x;
	for (int i = 0; i < N; i++)
	{
		x = a[i];
		j = i - 1;
		Compare++;
		while ((j >= 0) && (a[j]> x))
		{
			a[j + 1] = a[j];
			Giving++;
			j--;
		}
		a[j + 1] = x;
		Giving++;
	}
}

void swap(unsigned int &a, unsigned int &b)
{
	unsigned int temp = a;
	a = b;
	b = temp;
}

void BubbleSort(unsigned int* &a, int N, unsigned long long &giving, unsigned long long &compare)
{
	for (int i = 1; i < N; i++)
	for (int j = N - 1; j >= i; j--)
	{
		compare++;
		if (a[j - 1]> a[j])
		{
			swap(a[j - 1], a[j]);
			giving++;
		}
	}
}

void ShakeSort(unsigned int* &a, int N, unsigned long long &giving, unsigned long long &compare)
{
	int left = 1, right = N - 1, j, k;
	do
	{
		for (j = right; j >= left; j--){
			compare++;
			if (a[j - 1]> a[j])
			{
				swap(a[j], a[j - 1]);
				giving++;
				k = j;
			}
		}
		left = k + 1;
		for (j = left; j <= right; j++){
			compare++;
			if (a[j - 1]> a[j])
			{
				swap(a[j], a[j - 1]);
				giving++;
				k = j;
			}
		}
		right = k - 1;
	} while (left <= right);
}

void QuickSort(unsigned int* &a, int l, int r, unsigned long long &giving, unsigned long long &compare)
{
	int i = l; int j = r; unsigned int x = a[(l + r) / 2];
	do {
		compare++;
		while (x > a[i]) {
			compare++; i++;
		}
		compare++;
		while (a[j] > x) {
			compare++; j--;
		}
		if (i <= j){
			swap(a[i], a[j]);
			i++; j--; giving++;
		}
	} while (i < j);
	if (l < j)
		QuickSort(a, l, j, giving, compare);
	if (i < r)
		QuickSort(a, i, r, giving, compare);
}

void ShellSort(unsigned int* arr, int n, unsigned long long &giving, unsigned long long &compare)
{
	// Bắt đầu với khoảng cách lớn, sau đó rút khoảng cách lại
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		// Xét mảng với khoảng cách gap hiện tại.

		for (int i = gap; i < n; i += 1)
		{

			unsigned int temp = arr[i];
			giving++;

			int j;
			compare++;
			for (j = i; j >= gap && arr[j - gap]> temp; j -= gap)
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
void Merge(unsigned int* &arr, int l, int m, int r, unsigned long long &giving, unsigned long long &compare)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* Tạo các mảng tạm thời */
	unsigned int* L = (unsigned int*)malloc(sizeof(unsigned int)*(n1));
	unsigned int* R = new unsigned int[n2];

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
		if (R[j]>L[i])
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

void MergeSort(unsigned int* arr, int l, int r, unsigned long long &giving, unsigned long long &compare)
{
	if (l < r)
	{

		int m = l + (r - l) / 2;

		MergeSort(arr, l, m, giving, compare);
		MergeSort(arr, m + 1, r, giving, compare);

		Merge(arr, l, m, r, giving, compare);
	}
}

void Heapify(unsigned int* arr, int n, int i, unsigned long long &giving, unsigned long long &compare)
{
	int largest = i;  // Initialize largest as root
	int l = 2 * i + 1;  // left = 2*i + 1
	int r = 2 * i + 2;  // right = 2*i + 2

	// If left child is larger than root
	compare++;
	if (l < n && arr[l]> arr[largest])
		largest = l;

	// If right child is larger than largest so far
	compare++;
	if (r < n && arr[r]> arr[largest])
		largest = r;

	// If largest is not root
	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		giving++;

		Heapify(arr, n, largest, giving, compare);
	}
}

// main function to do heap sort
void HeapSort(unsigned int* arr, int n, unsigned long long &giving, unsigned long long &compare)
{
	// Build heap (rearrange array)
	for (int i = n / 2 - 1; i >= 0; i--)
		Heapify(arr, n, i, giving, compare);

	// One by one extract an element from heap
	for (int i = n - 1; i >= 0; i--)
	{
		// Move current root to end
		swap(arr[0], arr[i]);
		giving++;
		// call max heapify on the reduced heap
		Heapify(arr, i, 0, giving, compare);
	}
}

unsigned int GetMax(unsigned int* a, int N)
{
	unsigned int mx = a[0];
	for (int i = 1; i < N; i++)
	{
		if (a[i] > mx)
			mx = a[i];
	}
	return mx;
}

void CountSort(unsigned int* &a, int N, short exp, unsigned long long &giving, unsigned long long &compare)
{
	unsigned int* output = (unsigned int*)malloc(sizeof(unsigned int)*N);
	int i, count[10] = { 0 };
	for (i = 0; i < N; i++)
	{
		count[(a[i]/exp)%10]++;
	}

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = N - 1; i >= 0; i--)
	{
			output[count[(a[i]/exp)%10] - 1] = a[i];
			count[(a[i] / exp) % 10]--;
			giving++;
	}

	for (i = 0; i < N; i++){
		a[i] = output[i];
		giving++;
	}
	free(output);
}

void RadixSort(unsigned int* a, int N, unsigned long long &giving, unsigned long long &compare)
{
	int m = GetMax(a, N);
	for (int exp = 1; (m / exp)>0; exp *= 10)
		CountSort(a, N, exp, giving, compare);
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

void chooseSort(unsigned int* a, int N, unsigned long long &giving, unsigned long long &compare, clock_t &begin, clock_t &end)
{
	int temp;
	printf("Thuat toan ap dung de sap xep: %d PHAN TU\n", N);
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

void truePrint(unsigned int* a, int N)
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
	unsigned int* a;
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
	printf("So phep gan: %ul\n", giving);
	printf("So phep so sanh: %ul\n", compare);
	free(a);
}