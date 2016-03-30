#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <Windows.h>

#include <windows.h>  
#include <time.h> 			//time_t time()  clock_t clock()  
#include <Mmsystem.h>             	//timeGetTime()  
#pragma comment(lib, "Winmm.lib")   	//timeGetTime()  

using namespace std;
typedef LARGE_INTEGER ll;
const int maxn = 500;
const int base = 2e4;

void run(int k){
	while (k--){k--;k++;}
}

DWORD WINAPI AssThread(LPVOID argv)
{
	for (int i = 1; i < maxn*2; i++){
		run(i*base);
	}
	return 0;
}

void OutputThread()
{
	ll begin_time, end_time;
	double time_fre;
	double time_dif;
	ll litmp;
	QueryPerformanceFrequency(&litmp);
	time_fre = (double)litmp.QuadPart;
	for (int i = 1; i < maxn; i++){
		Sleep(0);
		QueryPerformanceCounter(&begin_time);
		run(i*base);
		QueryPerformanceCounter(&end_time);
		time_dif = (end_time.QuadPart - begin_time.QuadPart) / time_fre * 1000;
		printf("%llf\n", time_dif);
	}
}

void MT(){
	HANDLE Thread;
	DWORD ThreadID;
	for (int i = 0; i < 16; i++)
		Thread = CreateThread(0, 0, AssThread, 0, 0, &ThreadID);
}

int main(){
	freopen("out.txt", "w", stdout);
	MT();
	OutputThread();
	MT();
	return 0;
}
