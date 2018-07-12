#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef struct node* refnode; //Con trỏ đến cấu trúc Node

struct node //Một nút trong danh sách liên kết kép
{
	short *a; //Mảng số tượng trưng cho số cực lớn
	int N; //Số chữ số của số
	refnode pre; //Con trỏ đến nút trước đó
	refnode next; //Con trỏ đến nút tiếp theo
};

struct list //Danh sách liên kết kép
{
	refnode head; //Con trỏ đến nút đầu
	refnode tail; //Con trỏ đến nút cuối
};

void createList(list &l) //Khởi tạo danh sách rỗng
{
	l.head = l.tail = NULL;
}

short* delete0InTheHeadOfNumber(short *&a, int &N) //Xóa các số 0 ở đằng trước
{
	int dem = 0;
	for (int i = 1; i <= N; i++)
	{
		if (a[i] == 0)
		{
			dem++;
		}
		else break;
	}
	N -= dem;
	if (dem == 0)
	{
		return a;
	}
	else
	{
		short* b = new short[N + 1];
		b[0] = a[0];
		for (int i = 1; i <= N; i++)
		{
			b[i] = a[i + dem];
		}
		delete[]a;
		return b;
	}
}

refnode createNode() //Tạo một node có giá trị bất kì
{
	refnode q = new node;
	if (q)
	{
		q->a = NULL;
		q->N = 1 + rand() % 19; //Số lượng phần tử có thể từ 1 đến 19
		q->a = new short[q->N + 1];
		*(q->a) = rand() % 2; //Quy ước 1 là dương, 0 là âm
		for (int i = 1; i <= q->N; i++)
		{
			*(q->a + i) = rand() % 10; //Ngẫu nhiên số từ 0 đến 9
		}
		q->a = delete0InTheHeadOfNumber(q->a, q->N);
		q->next = q->pre = NULL;
		return q;
	}
	else
	{
		cout << "Loi cap phat!" << endl; //Lỗi cấp phát bộ nhớ
		exit(0); //Thoát chương trình
	}
}

void addTail(list &l, refnode &q) //Thêm node vào cuối
{
	if (l.head) //Danh sách không rỗng
	{
		q->pre = l.tail;
		l.tail->next = q;
		l.tail = q;
	}
	else //Danh sách rỗng
	{
		l.head = l.tail = q;
	}
}

void createRandomListWithNNode(list &l, int n) //Tạo danh sách ngẫu nhiên N số nguyên
{
	for (int i = 0; i < n; i++)
	{
		refnode q = createNode();
		addTail(l, q);
	}
}

void printList(list l) //In danh sách
{
	while (l.head)
	{
		if (l.head->N != 0)
		{
			if (*(l.head->a))
			{
				for (int i = 1; i <= l.head->N; i++)
				{
					cout << *(l.head->a + i);
				}
			}
			else
			{
				cout << "-";
				for (int i = 1; i <= l.head->N; i++)
				{
					cout << *(l.head->a + i);
				}
			}
			cout << " ";
			l.head = l.head->next;
		}
		else
		{
			cout << "0 ";
			l.head = l.head->next;
		}
	}
	cout << endl;
}

void deleteList(list &l) //Xóa danh sách theo kiểu xóa đầu
{
	while (l.head)
	{
		if (l.head == l.tail)
		{
			delete[] l.head->a;
			delete l.head;
			l.head = l.tail = NULL;
		}
		else
		{
			refnode q = l.head;
			l.head->next->pre = NULL;
			l.head = l.head->next;
			delete[] q->a;
			delete q;
		}
	}
}

/*void main()
{
	srand(time(NULL)); //Lần chạy sau tạo danh sách ngẫu nhiên không giống như lần chạy trước
	int N;
	cout << "Nhap so N: ";
	cin >> N;
	while (N < 1)
	{
		cout << "N khong duoc nho hon 1: ";
		cin >> N;
	}
	list l;
	createList(l);
	createRandomListWithNNode(l, N);
	printList(l);
	deleteList(l);
}*/

/*void ShellSort(short** &a, int n, int h[], int k)    // chọn được các k  khoảng cách sắp xếp 
{                                  //các khoảng cách nằm trong mảng h
	for (int i = 0; i < k; i++) //duyệt qua các bước sắp xếp
	for (int j = h[i]; j < n; j++) //xét mảng từ vị trí h[i] 
	{
		short* x = a[j]; //lưu phần tử đang xét để tránh ghi đè
		int l = j - h[i];
		while (l >= 0 && Larger(a[l], x)) //tìm vị trí thích hợp đồng thời 	                               {    //dời chỗ mảng về bên phải để chừa chỗ cho a[i]       
		{
			a[l + h[i]] = a[l];
			l = l - h[i];
		}
		a[l + h[i]] = x; //gán a[i] vào vị trí thích hợp tìm được
	}
}*/

short GetMax(short** a, int N)
{
	short mx = a[0][1];
	for (int i = 1; i < N; i++)
	{
		if (a[i][1]>mx)
			mx = a[i][1];
	}
	return mx;
}

// A utility function to get maximum value in arr[]
int getMax(int arr[], int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
	if (arr[i] > mx && )
		mx = arr[i];
	return mx;
}

void CountSort(short** a, int N, short exp)
{
	short** output = new short*[N];
	short n;
	int i, count[10] = { 0 };
	for (i = 0; i < N; i++)
	{
		n = a[i][1];
		if (n + exp < 2) count[0]++;
		else
		count[a[i][n + exp]]++;
	}

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = N - 1; i >= 0; i--)
	{
		output[count[a[i][n + exp]] - 1] = a[i];
		count[a[i][n + exp]]--;
	}
	for (i = 0; i < n; i++)
		a[i] = output[i];
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(int arr[], int n, int exp)
{
	int output[n]; // output array
	int i, count[10] = { 0 };

	// Store count of occurrences in count[]
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	// Change count[i] so that count[i] now contains actual
	//  position of this digit in output[]
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array
	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	// Copy the output array to arr[], so that arr[] now
	// contains sorted numbers according to current digit
	for (i = 0; i < n; i++)
		arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using 
// Radix Sort
void radixsort(int arr[], int n)
{
	// Find the maximum number to know number of digits
	int m = getMax(arr, n);

	// Do counting sort for every digit. Note that instead
	// of passing digit number, exp is passed. exp is 10^i
	// where i is current digit number
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, n, exp);
}

void RadixSort(short** a, int N)
{
	short m = GetMax(a, N);
	for (short exp = 1; m + exp >= 2; exp--)
		CountSort(a, N, exp);
}