#include<iostream>
#include<string.h>
 
using namespace std;
 
int main(){
    char msg[100];                          // Message cần mã hóa
    char key[100];                          // Key để mã hóa                        
    
    cout << "Original Message:  ";
    cin.getline(msg, 100);
    cout << "Key: ";
    cin.getline(key, 100);

    int msgLen = strlen(msg), 
        keyLen = strlen(key),
        i, j;

    char newKey[msgLen],                    // Key mới có độ dài bằng tin nhắn
         encryptedMsg[msgLen],              // Message đã mã hóa
         decryptedMsg[msgLen];              // Message được giải mã
 
    //generating new key
    for(i = 0, j = 0; i < msgLen; ++i, ++j){
        if(j == keyLen)                     // Nếu j = chiều dài key thì j = 0
            j = 0;
 
        newKey[i] = key[j];                 
    }
 
    newKey[i] = '\0';                       // Kết thúc key mới để tránh in ra các ký tự không mong muốn
 
    //encryption
    for(i = 0; i < msgLen; ++i)
        encryptedMsg[i] = ((msg[i] + newKey[i]) % 26) + 'A';  // Dựa vào bảng mã ASCII
 
    encryptedMsg[i] = '\0';
 
    //decryption
    for(i = 0; i < msgLen; ++i)
        decryptedMsg[i] = (((encryptedMsg[i] - newKey[i]) + 26) % 26) + 'A';
 
    decryptedMsg[i] = '\0';
 
    cout << "\nNew Generated Key: " << newKey;
    cout << "\nEncrypted Message: " << encryptedMsg;
    cout << "\nDecrypted Message: " << decryptedMsg;
 
	return 0;
}