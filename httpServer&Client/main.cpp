//#include "stdafx.h"
//注意找个代码，会报错 大概是因为注释导致文件终止，删除掉大段的注释。。。
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string>

#pragma comment(lib,"ws2_32")

#define HALO_S_PORT     9090

/*
LPVOID是一个没有类型的指针，也就是说你可以将LPVOID类型的变量赋值给任意类型的指针，
比如在参数传递时就可以把任意类型传递给一个LPVOID类型为参数的方法，
然后在方法内再将这个“任意类型”从传递时的“LPVOID类型”转换回来。
*/

//这个线程recv请求，处理请求，再将内容发到fd上去
static DWORD CALLBACK FdHandler(IN LPVOID lpCtx) {		//这是一个线程函数 //将fd传入到这里

	SOCKET fd = (SOCKET)lpCtx;
	char  *Buffer = new char[8193];
	int    i = recv(fd, Buffer, 8192, 0);			//从TCP的另一端接收数据，返回的是实际copy的字节数
	if (i > 0) {
		Buffer[i] = '\0';
		char *h = new char[i + 1];
		strcpy(h, Buffer);
		printf("\r\n%s\r\n", Buffer);
		//
		// http request parsing, and generate http response
		//
		i = sprintf(Buffer,
			"HTTP/1.1 200 OK\r\n"
			"Content-Type: text/html\r\n"
			"Connection: Close\r\n\r\n"
		);
		FILE *pf = fopen("halos_html.txt", "r");
		i += fread(&Buffer[i], 1, 8192 - i, pf);		//pf内容读入buffer
		/*函数原型
size_t fread ( void *buffer, size_t size, size_t count, FILE *stream) ;
buffer 用于接收数据的内存地址
size   要读的每个数据项的字节数，单位是字节
count  要读count个数据项，每个数据项size个字节.
stream 输入流
返回值 返回真实读取的项数，若大于count则意味着产生了错误。*/

		Buffer[i] = '\0';
		fclose(pf);

		char *p = strstr(Buffer, "%_HALO_%");//strstr(str1, str2) 函数用于判断字符串str2是否是str1的子串。 如果是，则该函数返回str2在str1中首次出现的地址；否则，返回NULL。
		if (p) {								//??????????????????????????

			*p = '\0';
			std::string tmp = Buffer;
			tmp += h;
			tmp += &p[0];
			i = (int)tmp.size();
			memcpy(Buffer, tmp.c_str(), i);//由src指向地址为起始地址的连续n个字节的数据复制到以destin指向地址为起始地址的空间内。

			Buffer[i] = '\0';

		}
		printf("size:%d\r\n%s\r\n", i, Buffer);			//打印halos_html.txt的内容

		i = send(fd, Buffer, i, 0);
	}
	delete[]Buffer;
	Sleep(1000);
	closesocket(fd);
	return 0;
}

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	WSAStartup(0x0202, &wsaData);
	SOCKADDR_IN addr;
	SOCKET lfd = socket(PF_INET, SOCK_STREAM, 0);
	int i;

	addr.sin_addr.S_un.S_addr = 0;
	addr.sin_family = PF_INET;
	addr.sin_port = htons(HALO_S_PORT);

	i = bind(lfd, (const sockaddr*)&addr, sizeof(SOCKADDR_IN));
	if (i != NOERROR) {
		printf("Oops, failed to bind:%d port\r\n", HALO_S_PORT);
		return 0;
	}
	listen(lfd, 1970);		//三次握手过程中等待包的最大数量，防SYN_FLOOD攻击
	do {
		i = sizeof(SOCKADDR_IN);
		SOCKET fd = accept(lfd, (sockaddr*)&addr, &i);
		if (fd != INVALID_SOCKET) {
			printf("\r\ncoming from [%s:%d]\r\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));//这行要验证一下作用 addr不是本机的吗
					//端口输出的时候要转换为host格式
			HANDLE hThread = CreateThread(NULL, 0,
				FdHandler,
				(LPVOID)fd,
				0,
				NULL);
			CloseHandle(hThread);
/*
HANDLE CreateThread(
                    LPSECURITY_ATTRIBUTES lpThreadAttributes,指向SECURITY_ATTRIBUTES的指针，用于定义新线程的安全属性，一般设置成NULL；
                    DWORD dwStackSize,分配以字节数表示的线程堆栈的大小，默认值是0；
                    LPTHREAD_START_ROUTINE lpStartAddress,指向一个线程函数地址。每个线程都有自己的线程函数，线程函数是线程具体的执行代码；
                    LPVOID lpParameter,传递给线程函数的参数；
                    DWORD dwCreationFlags,表示创建线程的运行状态，其中CREATE_SUSPEND表示挂起当前创建的线程，而0表示立即执行当前创建的进程；
                    LPDWORD lpThreadID返回新创建的线程的ID编号；
                   );
				   如果函数调用成功，则返回新线程的句柄，
*/
		}
		else {
			printf("Something is wrong\r\n");		//出现wrong 的情况 没等到第三个响应包，对方掉网了或者SYN_FLOOD攻击
		}
	} while ("Go ahead");

	WSACleanup();
	return 0;
}
//————————————————
//版权声明：本文为CSDN博主「iroy33」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
//原文链接：https://blog.csdn.net/iroy33/article/details/88802916
