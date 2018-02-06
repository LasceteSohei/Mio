// Mio.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

extern "C"
{
#include "libavcodec\avcodec.h"

}

#pragma comment(lib, "avcodec.lib")

using namespace std;

int main()
{
	cout << "Testing ffmpeg library...." << endl;

	avcodec_register_all();
	
	cout << "Done..." << endl;
    return 0;
}

