#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LENGTH 23 //Độ dài của số

void Normalize(short* &a)
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

short* RandomNum()
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

void RandomArray(short** &a,int N)
{
	a = (short**)malloc(sizeof(short*)*N);
	for (int i = 0; i < N; i++)
	{
		*(a + i) = RandomNum();
	}
}

void printArray(short** a,int N)
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

void InsertionSort(short** &a,int N)
{
	short n;
	int j;
	short* x;
	for (int i = 0; i < N; i++)
	{
		n = a[i][1] + 2;
			x = a[i];
			j = i - 1;
			while ((j >= 0) && (Larger(a[j], x)))
			{
				a[j + 1] = a[j];
				j--;
			}
			a[j + 1] = x;
	}
}

void swap(short* &a, short* &b)
{
	short* temp = a;
	a = b;
	b = temp;
}

void BubbleSort(short** &a, int N)
{
	for (int i = 1; i < N; i++)
	for (int j = N - 1; j >= i;j--)
	if (Larger(a[j - 1], a[j]))
		swap(a[j - 1], a[j]);
}

void ShakeSort(short** &a, int N)
{
	int left = 1, right = N - 1, j, k;
	do
	{
		for (j = right; j >= left;j--)
		if (Larger(a[j - 1], a[j]))
		{
			swap(a[j], a[j - 1]);
			k = j;
		}
		left = k + 1;
		for (j = left; j <= right; j++)
		if (Larger(a[j - 1], a[j]))
		{
			swap(a[j], a[j - 1]);
			k = j;
		}
		right = k - 1;
	} while (left <= right);
}

void QuickSort(short** &a, int l, int r)
{
	int i = l;int j = r;short* x = a[(l + r) / 2];
	do {
		while (Larger(x,a[i])) i++;
		while (Larger(a[j],x)) j--;
		if (i <= j){
			swap(a[i], a[j]);
			i++; j--;
		}
	} while (i < j);
	if (l < j)
		QuickSort(a, l, j);
	if (i < r)
		QuickSort(a, i, r);
}

void ShellSort(short** arr, int n)
{
	// Bắt đầu với khoảng cách lớn, sau đó rút khoảng cách lại
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		// Xét mảng với khoảng cách gap hiện tại.
		// The first gap elements a[0..gap-1] are already in gapped order
		// keep adding one more element until the entire array is
		// gap sorted 
		for (int i = gap; i < n; i += 1)
		{
			// add a[i] to the elements that have been gap sorted
			// save a[i] in temp and make a hole at position i
			short* temp = arr[i];

			// shift earlier gap-sorted elements up until the correct 
			// location for a[i] is found
			int j;
			for (j = i; j >= gap && Larger(arr[j - gap],temp); j -= gap)
				arr[j] = arr[j - gap];

			//  put temp (the original a[i]) in its correct location
			arr[j] = temp;
		}
	}
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void Merge(short** &arr, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	short** L = (short**)malloc(sizeof(short*)*(n1));
	short** R = new short*[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2)
	{
		if (!Larger(L[i],R[j]))
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void MergeSort(short** arr, int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l + (r - l) / 2;

		// Sort first and second halves
		MergeSort(arr, l, m);
		MergeSort(arr, m + 1, r);

		Merge(arr, l, m, r);
	}
}

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void Heapify(short** arr, int n, int i)
{
	int largest = i;  // Initialize largest as root
	int l = 2 * i + 1;  // left = 2*i + 1
	int r = 2 * i + 2;  // right = 2*i + 2

	// If left child is larger than root
	if (l < n && Larger(arr[l], arr[largest]))
		largest = l;

	// If right child is larger than largest so far
	if (r < n && Larger(arr[r], arr[largest]))
		largest = r;

	// If largest is not root
	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		// Recursively heapify the affected sub-tree
		Heapify(arr, n, largest);
	}
}

// main function to do heap sort
void HeapSort(short** arr, int n)
{
	// Build heap (rearrange array)
	for (int i = n / 2 - 1; i >= 0; i--)
		Heapify(arr, n, i);

	// One by one extract an element from heap
	for (int i = n - 1; i >= 0; i--)
	{
		// Move current root to end
		swap(arr[0], arr[i]);

		// call max heapify on the reduced heap
		Heapify(arr, i, 0);
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

void CountSort(short** &a, int N, short exp)
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
			count[0]--;
		}

		else{
			m = a[i][n + exp];
			output[count[m] - 1] = a[i];
			count[m]--;
		}
	}

	for (i = 0; i < N; i++)
		a[i] = output[i];
	free(output);
}

void Linking(short** a, short** pos, short** neg, int m, int n)
{
	int k = 0;
	for (int i = m - 1; i >= 0; i--)
	{
		a[k] = neg[i];
		k++;
	}
	for (int j = 0; j < n; j++)
	{
		a[k]=pos[j];
		k++;
	}
}

void RadixSort(short** a, int N)
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
		CountSort(L, neg, exp1);
	for (short exp2 = 1; n + exp2 >= 2; exp2--)
		CountSort(R, pos, exp2);
	Linking(a, R, L, neg, pos);
	free(L);
	free(R);
}

void main()
{
	srand(time(NULL));
	short** a;
	int N = 1000000;
	RandomArray(a, N);
	clock_t begin = clock();
	//InsertionSort(a, N);
	//BubbleSort(a, N);
	//ShakeSort(a, N);
	//QuickSort(a, 0, N - 1);
	//ShellSort(a, N);
	//MergeSort(a, 0, N - 1);
	//HeapSort(a, N);
	RadixSort(a, N);
	clock_t end = clock();
	float sec = (float)(end - begin) / CLOCKS_PER_SEC;
	//printArray(a, N);
	printf("Time run: %0.14f sec\n", sec);
	free(a);
}
