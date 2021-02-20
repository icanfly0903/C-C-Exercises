#include <iostream>
using namespace std;
#include <math.h>
#include <string.h>

char a[100];

long convertDecima(char a[]) { // Chuyển từ hệ 16 sang hệ 10
	long dec = 0;
	long temp;
	long j = 0;
	for(int i = strlen(a)-1; i >= 0; i--) {
		if(a[i] == 'A' || a[i] == 'a') 
			temp = 10;
		else if(a[i] == 'B' || a[i] == 'b')
			temp = 11;
		else if(a[i] == 'C' || a[i] == 'c')
			temp = 12;
		else if(a[i] == 'D' || a[i] == 'd')
			temp = 13;
		else if(a[i] == 'E' || a[i] == 'e')
			temp = 14;
		else if(a[i] == 'F' || a[i] == 'f')
			temp = 15;
		else {
			temp = a[i];
			temp -= 48;
		}
		dec += temp * pow(16, j);
		j++;
	}
	return dec;
}

void convertBinary(char a[]) { // Chuyển từ hệ 16 sang hệ cơ số 2
	int bin[100];
	int i = 0;
	long dec = convertDecima(a); 
	 while (dec > 0) {  
        bin[i] = dec % 2; // Dùng mảng chứa số dư(remainder) khi chia cho 2
        dec = dec / 2; 
        i++; 
    } 
 	cout << "\nBinary : ";
    for (int j = i - 1; j >= 0; j--) // In ra mảng chứa số dư từ cuối lên
        cout << bin[j]; 
}

// long convertOctal(char a[]) { // Chuyển từ hệ 16 sang hệ cơ số 8
// 	long remainder, i = 1, oct = 0;
// 	long dec = convertDecima(a);
// 	do {
// 		remainder = dec % 8;
// 		dec = dec / 8;
// 		oct += (remainder * i);
// 		i *= 10;
// 	} while (dec > 0);
// 	return oct;
// }

void convertOctal(char a[]) {
	int oct[100];
	int i = 0;
	long dec = convertDecima(a);
	while (dec > 0) {
		oct[i] = dec % 8;
		dec = dec / 8;
		i++;
	}
	cout << "\nOctal  : ";
	for(int j = (i-1); j >= 0; j--)
		cout << oct[j];
}

int main() {
	cout << "Enter hex number: ";
	cin  >> a;
	convertBinary(a);
	long dec = convertDecima(a);
	cout << "\nDecima : " << dec;
	convertOctal(a);
}