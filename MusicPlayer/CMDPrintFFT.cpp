//
// Created by wws on 17-7-19.
//

#include "CMDPrintFFT.h"
#include <math.h>
#include <stdio.h>

CMDPrintFFT::CMDPrintFFT()
{
    data_print = new char[60 * 129 + 1];
    dp_len = 60 * 129 + 1;

    data = new int[128];
    data_len = 128;
	for (int i = 0; i < data_len; ++i) {
		data[i] = 0;
	}
}
/*
CMDPrintFFT::CMDPrintFFT(const CMDPrintFFT &pf)
{
    dp_len = pf.dp_len;
    data_print = new char[pf.dp_len];
    for(int i = 0;i < dp_len;i++)
    {
        data_print[i] = *(pf.data_print + i);
    }

    data_len = pf.data_len;
    data = new int[data_len];
    for(int i = 0;i < data_len;i++)
    {
        data[i] = *(pf.data + i);
    }

}
*/

/*
CMDPrintFFT::CMDPrintFFT(CMDPrintFFT &&pf)
{
    dp_len = pf.dp_len;
    data_print = pf.data_print;

    data_len = pf.data_len;
    data = pf.data;

    pf.data_print = nullptr;
    pf.data = nullptr;
}
*/


CMDPrintFFT::~CMDPrintFFT()
{
    if(data_print != nullptr)
        delete [] data_print;
    if(data != nullptr)
        delete [] data;
}
/*
CMDPrintFFT& CMDPrintFFT::operator=(CMDPrintFFT &&pf)
{
    delete [] data_print;
    data_print = pf.data_print;
    pf.data_print = nullptr;

    delete [] data;
    data = pf.data;
    pf.data = nullptr;

    data_len = pf.data_len;
    dp_len = pf.dp_len;

	return *this;
}
*/
void CMDPrintFFT::init_data()
{
    for (int i = 0; i < 60 * 129; i++)
    {
        if ((i + 1) % 129 == 0)
        {
            data_print[i] = '\n';
            continue;
        }
		data_print[i] = ' ';
    }
    data_print[60 * 129] = '\0';
}

void CMDPrintFFT::printFFT(float *fft, int len, float l, float h)
{
	init_data();
	
    for (int i = 0; i < 128; ++i)
    {
        float hh = 0;
        
        hh = fft[i];
        
        hh = 2.0f * sqrtf(hh * 4000.0f);

        //int d = (int)round(hh);
		data[i] = (int)round(hh);
        //d < data[i] ? data[i]-- : data[i] = d;


		unsigned int val = 60 - (data[i] > 60 ? 60 : data[i]);
		for (int n = 59; n >= val; --n)
		{
			data_print[n * 129 + i] = '#';
		}
    }

    printf("%s", data_print);

}