/*
* Base64 encoding/decoding (RFC1341)
* Copyright (c) 2005-2011, Jouni Malinen <j@w1.fi>
*
* This software may be distributed under the terms of the BSD license.
* See README for more details.
*/

// 2016-12-12 - Gaspard Petit : Slightly modified to return a std::string
// instead of a buffer allocated with malloc.
using namespace std;
#include <iostream>
#include <string>
#include <string.h>

static const unsigned char base64_table[65] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static char *decoding_table = NULL; // Bảng giải mã base64
/**
* base64_encode - Base64 encode
* @src: Data to be encoded
* @len: Length of the data to be encoded
* @out_len: Pointer to output length variable, or %NULL if not used
* Returns: Allocated buffer of out_len bytes of encoded data,
* or empty string on failure
*/
string base64_encode(const unsigned char *src, size_t len)
{
    unsigned char *out, *pos;           // Khai báo con trỏ chuỗi out và pos
    const unsigned char *end, *in;      // Khai báo chuỗi hằng end và in

    size_t olen;                        // Độ dài chuỗi ra

    olen = 4*((len + 2) / 3);           // 3-byte blocks to 4-byte 

    if (olen < len)                     // Nếu độ dài chuỗi mã hóa(encode) nhỏ hơn độ dài src
        return string();                			// integer overflow 

    string outStr;                      // Dữ liệu sau khi được mã hóa
    outStr.resize(olen);                // Thiết lập chiều dài cho chuỗi mã hóa
    out = (unsigned char*)&outStr[0];   // Con trỏ chuỗi out trỏ vào phần tử đầu của chuỗi mã hóa

    end = src + len;					// Chuỗi end có độ dài bằng chuỗi src + chiều dài src
    in = src;							// Chuỗi src gán giá trị cho chuỗi in
    pos = out;							// Chuỗi out gán giá trị cho chuỗi pos
    while (end - in >= 3) {
        *pos++ = base64_table[in[0] >> 2];                           
        *pos++ = base64_table[((in[0] & 0x03) << 4) + (in[1] >> 4)];  
        *pos++ = base64_table[((in[1] & 0x0f) << 2) + (in[2] >> 6)];
        *pos++ = base64_table[in[2] & 0x3f];
        in += 3;
        /* Example: 
        	rav = 01110010 01100001 01110110
        	in[0] = 01110010 >> 2 = 011100 (suy ra in[0] = 10)
        	in[0] = 10 << 4 = 10_ _ _ _ + in[1] = 01100001 >> 4 = 0110 (suy ra in[1] = 0001)
        		suy ra in[0] << 4 + in[1] >> 4 = 100110
        	in[1] << 2 + in[2] >> 6 = 000101
        	in[2] = 110110 
        */
    }

    if (end - in != 0) { 
        *pos++ = base64_table[in[0] >> 2];
        if (end - in == 1) {
            *pos++ = base64_table[(in[0] & 0x03) << 4];
            *pos++ = '=';
        }
        else {
            *pos++ = base64_table[((in[0] & 0x03) << 4) + (in[1] >> 4)];
            *pos++ = base64_table[(in[1] & 0x0f) << 2];
        }
        *pos++ = '=';
    }

    return outStr;
}

void build_decoding_table() {

    decoding_table = new char(255);

    for (int i = 0; i < 64; i++)
        decoding_table[(unsigned char) base64_table[i]] = i;
}

string base64_decode(string data, size_t input_length) {

    unsigned char *out;           // Khai báo con trỏ chuỗi out và pos
    size_t output_length;

    if (decoding_table == NULL) build_decoding_table(); // Lập bảng giải mã base 64

    if (input_length % 4 != 0) return NULL;

    output_length = input_length / 4 * 3;

    if (data[input_length - 1] == '=') (output_length)--;
    if (data[input_length - 2] == '=') (output_length)--;

    string decoded_data;								// Khai báo chuỗi giải mã
    decoded_data.resize(output_length);					// Thiết lập độ dài chuỗi giải mã
    out = (unsigned char*)&decoded_data[0];				
    if (input_length < output_length) return string();

    for (int i = 0, j = 0; i < input_length;) {

        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];

        uint32_t triple = (sextet_a << 3 * 6)
        + (sextet_b << 2 * 6)
        + (sextet_c << 1 * 6)
        + (sextet_d << 0 * 6);

        if (j < output_length) out[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < output_length) out[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < output_length) out[j++] = (triple >> 0 * 8) & 0xFF;
    }

    return decoded_data;
}

int main()
{
    char in[100];
    cout << "String : ";
    cin.get(in, 100);
    //char *enchar = (char*)base64_encode((const unsigned char*)in, strlen(in))[0];
    string enString = base64_encode((const unsigned char*)in, strlen(in));
    cout << "Encoded String : " << enString;
    //cout << enchar;
    string deString = base64_decode(enString, enString.size());
    cout << "\nDecoded String : " << deString;
}
