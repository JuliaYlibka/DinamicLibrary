#include <windows.h>
#include <iostream>
using namespace std;
int main() {
	HMODULE hDll; // дескриптор DLL
	int (*Add)(int); // указатель на функцию Add из DLL
	int (*Sub)(int); // указатель на функцию Sub из DLL
	int* pCount; // указатель на переменную count из DLL
	// загружаем динамически подключаемую библиотеку
	hDll = LoadLibrary("Dynamic.dll");
	if (!hDll) 
	{
		cerr << "Load library failed." << endl;
		return GetLastError();
	}
	// настраиваем адрес переменной count из DLL
	pCount = (int*)GetProcAddress(hDll, "count");
	if (!pCount) 
	{
		cerr << "Get variable address failed." << endl;
		return GetLastError();
	}
	// выводим начальное значение переменной count
	cout << "Initial count = " << (*pCount) << endl;
	// настраиваем адреса функций
	Add = (int (*)(int))GetProcAddress(hDll, "Add");
	Sub = (int (*)(int))GetProcAddress(hDll, "Sub");
	if (!Add || !Sub) {
		cerr << "Get procedure address failed." << endl;
		return GetLastError();
	}
	// изменяем значение счетчика
	cout << "count = " << Add(30) << endl;
	cout << "count = " << Sub(20) << endl;
	cout << "count = " << Sub(10) << endl;
	// отключаем библиотеку
	if (!FreeLibrary(hDll)) {
		cerr << "Free library failed." << endl;
		return GetLastError();
	}
	// выходим из программы
	cout << "Press any key to exit ";
	cin.get();
	return 0;
}