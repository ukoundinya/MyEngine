#include <stdio.h>
#include <conio.h>
#include <iostream>
#include "..\NewEngine\MemoryAllocators\BlockAllocator.h"

using namespace std;



void main()
{

	int f = 2;

	/*cout.write(reinterpret_cast<const char*>(&f), sizeof(f));*/

	cout << (char)f;
	_getch();
}

