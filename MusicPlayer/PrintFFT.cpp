//
// Created by wws on 17-7-19.
//

#include "PrintFFT.h"
#include <math.h>
#include <stdio.h>

PrintFFT::PrintFFT()
{
    data_print = new char[60 * 129 + 1];
    dp_len = 60 * 129 + 1;

    data = new int[128];
    data_len = 128;
}

PrintFFT::PrintFFT(const PrintFFT &pf)
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

PrintFFT::PrintFFT(PrintFFT &&pf)
{
    dp_len = pf.dp_len;
    data_print = pf.data_print;

    data_len = pf.data_len;
    data = pf.data;

    pf.data_print = nullptr;
    pf.data = nullptr;
}

PrintFFT::~PrintFFT()
{
    if(data_print != nullptr)
        delete [] data_print;
    if(data != nullptr)
        delete [] data;
}

PrintFFT& PrintFFT::operator=(PrintFFT &&pf)
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

void PrintFFT::init_data()
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

void PrintFFT::printFFT(float *fft, int len)
{
	init_data();

    for (int i = 0; i < 128; i++)
    {
        float hh = 0;
        for (int j = 0; j < 8; j++)
        {
            hh += fft[(8 * i) + j];
        }
        float hhh = 2.0f * sqrtf((hh / 8.0f) * 4000.0f);

        int d = (int)round(hhh);
        d < data[i] ? data[i]-- : data[i] = d;


		int mrow = 59;
		for (int n = 0; n < (data[i] > 60 ? 60 : data[i]); n++)
		{
			data_print[mrow * 129 + i] = '#';
			mrow--;
		}
    }

    printf("%s", data_print);

}