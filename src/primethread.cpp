//This program is a multithreaded prime-finder that uses two threads
//to efficiently close in on a prime from two sides.
//Note that this program runs best on a P4 with Hyperthreading, or one
//of Intel's new Dual Core processors.
//Also note that this program is NOT compatible with Linux/UNIX...
#include <iostream>
#include <fstream>
#include <windows.h>
#include <cmath>
using namespace std;
int oneprime = 0;
int twoprime = 0;
int onecomplete = 0;
int twocomplete = 0;
DWORD WINAPI isprimehi(LPVOID);
DWORD WINAPI isprimelo(LPVOID);
HANDLE g_handles[2]; // Storage for thread g_handles
DWORD g_ids[2]; // Storage for thread g_ids
int main()
{
long long int val;
long long int test = 1;
int option = 0;
ofstream outputfile;
outputfile.open("output.txt");
outputfile << "Results of prime search:\n";
if (val < 0)
{
return 0;
}
//cout << "Enter 1 to save to file, enter 2 to print to screen:\n";
//cin >> option;
option = 2;
cout << "Enter High Limit:\n";
cin >> val;
system("cls");
if (option == 2)
{
cout << "List of Primes:\n";
while (test < val)
{
//cout << "testing : " << test << endl;
oneprime = 0;
twoprime = 0;
onecomplete = 0;
twocomplete = 0;
g_handles[0] = CreateThread(0, 0, isprimehi, (LPVOID)test, 0,
&g_ids[0]);
g_handles[1] = CreateThread(0, 0, isprimelo, (LPVOID)test, 0,
&g_ids[1]);
while (!onecomplete || !twocomplete)
{
WaitForMultipleObjects(2, g_handles, true, INFINITE);
}
if (oneprime && twoprime)
{
cout << test << endl;
}
oneprime = 0;
twoprime = 0;
onecomplete = 0;
twocomplete = 0;
++test;
}
}
cin.get();
val = 0;
test = 0;
option = 0;
cout << "Number of seconds Program has been running:\n";
cout << clock() / CLOCKS_PER_SEC;
cout << "\n\nHit enter to exit.\n";
cin.get();
outputfile.close();
CloseHandle(g_handles[0]);
CloseHandle(g_handles[1]);
return 0;
}
//-------------------------------------------------------------------------
DWORD WINAPI isprimehi(LPVOID test)
{
int val = (int)test;
if (!(val % 2) && val > 2)
{
oneprime = 0;
onecomplete = 1;
return (DWORD)0;
}
if (!(val % 5) && val > 5)
{
oneprime = 0;
onecomplete = 1;
return (DWORD)0;
}
for (int i = (ceil(sqrt(val)) / 2+1); i < val; ++i)
{
if (!(val % i))
{
oneprime = 0;
onecomplete = 1;
return (DWORD)0;
}
}
onecomplete = 1;
oneprime = 1;
ExitThread(0);
return (DWORD)1;
}
DWORD WINAPI isprimelo(LPVOID test)
{
int val = (int)test;
if (!(val % 2) && val > 2)
{
twoprime = 0;
twocomplete = 1;
return (DWORD)0;
}
if (!(val % 5) && val > 5)
{
twoprime = 0;
twocomplete = 1;
return (DWORD)0;
}
for (int i = 2; i < floor(sqrt(val)) / 2; ++i)
{
if (!(val % i))
{
twoprime = 0;
twocomplete = 1;
return (DWORD)0;
}
}
twocomplete = 1;
twoprime = 1;
ExitThread(0);
return (DWORD)1;
}