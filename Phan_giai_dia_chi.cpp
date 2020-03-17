#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>
#pragma comment(lib, "ws2_32")
using namespace std;
//hàm kiểm tra một ký tự
bool isValidCharacter(char a) {
	return (a >= 'a' && a <= 'z')
		|| (a >= 'A' && a <= 'Z')
		|| (a >= '1' && a <= '9')
		|| (a == '.')
		|| (a == '-');
}
//hàm kiểm tra chuối nhập vào
//gồm chữ cái, số, và ký tự - hoặc .
bool isValidDomain(char* s) {
	int i = 0;
	while (s[i] != '\0') {
		if (!isValidCharacter(s[i]))
			return false;
		i++;
	}
	return true;
}

int main() {
	//khởi tạo winsock
	WSADATA wsa;
	int res = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (res == 0) {
		addrinfo* info;
		sockaddr_in addr;
		//lấy chuỗi kí tự từ bàn phím
		char s[100];
		cin.getline(s, 100);
		//kiểm tra chuỗi ký tự
		if (!isValidDomain(s)) {
			printf("ten mien chua ky tu khong hop le");
			return 1;
		}
		//phân giải địa chỉ
		int ret = getaddrinfo(s, "http", NULL, &info);
		//in địa chỉ ip đã phân giải ra màn hình
		if (ret == 0) {
			//In ra cac dia chi ip
			while (info != NULL) {
				memcpy(&addr, info->ai_addr, info->ai_addrlen);
				printf("dia chi ip: %s", inet_ntoa(addr.sin_addr));
				info = info->ai_next;
			}
		}
		else {
			printf("loi khong phan giai duoc dia chi! vui long kiem tra lai");
		}
		WSACleanup();
	}


}
