#include <iostream>
using namespace std;
#include <stdio.h>	
#include <stdlib.h>
#include <time.h>
#include <algorithm>

const int MAX = 1e6; //Số phần tử mà danh sách có thể chứa

int arr[MAX];

typedef struct Node { // Cấu trúc Node của danh sách liên kết đơn
	int data;
	struct Node *next;
	struct Node *prev;
}node;

node *head, *tail; // Phần tử đầu cuối của danh sách

node *GetNewNode(int x) { // Khởi tạo Node
	node *newNode = (node*)malloc(sizeof(node));
	newNode->data = x;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode; 
}

void InsertAtHead(int x, node *newNode) { // Thêm Node mới vào đầu danh sách 
	newNode = GetNewNode(x);
	if(head == NULL) {
		head = tail = newNode;
		return;
	}
	head->prev = newNode;
	newNode->next = head;
	head = newNode;
}

void InsertAtTail(int x, node *newNode) { // Thêm Node mới vào cuối danh sách
	newNode = GetNewNode(x);
	if(head == NULL) {
		head = tail = newNode;
		return;
	}
	tail->next = newNode;
	newNode->prev = tail;
	tail = newNode;
}

void DeleteNode(int x, node *p) { // Xóa Node có data là x
	if(head == NULL) {
		cout << "Nothing to delete!";
		return;
	} 
	node *preNode = p->prev;
	node *nextNode = p->next;
	preNode->next = nextNode;
	nextNode->prev = preNode;
	free(p); 
}

void DeleteAtHead() { // Xóa Node đầu
	if(head == NULL) {
		cout << "Nothing to delete!";
		return;
	} else {
		head = head->next;
		head->prev = NULL;
	}
}

void DeleteAtTail() { // Xóa Node cuối
	if(head == NULL) {
		cout << "Nothing to delete!";
		return;
	}
	tail = tail->prev;
	tail->next = NULL;
}

void Print() { // In danh sách từ dầu đến cuối
	node *temp = head;
	cout << "In clockwise: ";
	while(temp != NULL) {
		cout << temp->data <<"  ";
		temp = temp->next;
	}
	cout <<"\n";
}

void ReversePrint() { // In danh sách từ cuối lên đầu
	node *temp = tail;
	cout << "In anticlockwise: ";
	while(temp != NULL) {
		cout << temp->data <<"  ";
		temp = temp->prev;
	}
	cout <<"\n";
}

void SortAsc() { // Sắp xếp danh sách tăng dần
	node *p, *q;
	for(p = head; p != NULL; p = p->next) {
		for(q = p->next; q != NULL; q = q->next) {
			if(p->data > q->data) {
				int temp = p->data;
				p->data = q->data;
				q->data = temp;
			}
		}
	}
}

void SortDesc() { // Sắp xếp danh sách giảm dần
	node *p, *q;
	for(p = head; p != NULL; p = p->next) {
		for(q = p->next; q != NULL; q = q->next) {
			if(p->data < q->data) {
				int temp = p->data;
				p->data = q->data;
				q->data = temp;
			}
		}
	}
}

void Menu() {
	int option;
	do {
		cout << "\n-------------------MENU-------------------";
		cout << "\n1. Insert 1 node at head's list."; // Chèn 1 Node mới vào đầu ds
		cout << "\n2. Change data's node at position i to data x."; // Đổi giá trị của 1 node tại vị trí i
		cout << "\n3. Delete node containing x."; // Xóa Node chứa giá trị x
		cout << "\n4. Rotate the list clockwise."; // In danh sách theo chiều kim đồng hồ
		cout << "\n5. Rotate the list anticlockwise."; // In danh sách theo chiều ngược kim đồng hồ
		cout << "\n6. Sort the list in ascending order."; // Sắp xếp ds theo chiều tăng dần
		cout << "\n7. Sort the list in descending order."; // Sắp xếp ds theo chiều giảm dần
		cout << "\n0. The end."; // Kết thúc
		cout << "\n------------------------------------------";
		cout << "\nYour option: "; 
		cin  >> option;
		switch(option) {
			case 1: {
				int value;
				cout << "Enter inserted value: "; // Nhập giá trị của Node chèn vào đầu
				cin  >> value;
				InsertAtHead(value, head);
				break;
			}
			case 2: {
				node *p;
				int position;
				int value;
				int i = 0;
				cout << "Enter position's node: "; // Nhập vị trí cần thay đổi
				cin  >> position;
				cout << "Enter value to be changed: "; // Nhập giá trị của node cần thay đổi
				cin  >> value;
				for(p = head; p != NULL; p = p->next) {
					if (i == position) {
						cout << p->data;
						p->data = value;
						break;
					}
					i++;
				}
				break;
			}
			case 3: {
				int value;
				int check = 0;
				cout << "\nEnter node containing value to be deleted: "; // Nhập giá trị của node cần xóa
				cin  >> value;
				node *p;
				for(p = head; p != NULL; p = p->next) {
					if(p->data == value) {
						DeleteNode(value, p);
						cout << "\nDelete Successfully!";
						check = 1;
						break;
					}
				}
				if(check == 0) {
					cout << "\nDon't find node!";
				}				
				break;
			}
			case 4: {
				Print();
				break;
			}
			case 5: {
				ReversePrint();
				break;
			}
			case 6: {
				SortAsc();
				Print();
				break;
			}
			case 7: {
				SortDesc();
				Print();
				break;
			}
			default: {
				cout << "No option! Please choose again!";
			}
			case 0: {
				cout << "----------------THE END----------------";
			}
		}
	} while (option != 0);
}

int main() {
	srand(time(NULL)); // Tạo giá trị seed ngẫu nhiên
	int n;
	int t;
	cout << "Number of List: ";
	cin >> n;
	for(int i = 0; i <= 2*n; i++) {
		arr[i-0] = i;
	}	
	random_shuffle(arr, arr + 2*n);
	node *p = head;
	for(int i = 0; i < n; i++) {
		// t = rand() % (MAX + 1); // Nhảy số ngẫu nhiên trong khoảng [min, max]	
		t = arr[i];
		InsertAtTail(t, p);		
	}
	Print();
	Menu();
}