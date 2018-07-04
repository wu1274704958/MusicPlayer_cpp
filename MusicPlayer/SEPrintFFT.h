#ifndef __SE_PRINTFFT_H__
#define __SE_PRINTFFT_H__

#include "PrintFFT.h"

class SEPrintFFT : public PrintFFT
{
public:
	SEPrintFFT();
	virtual ~SEPrintFFT();

	virtual void printFFT(float *fft, int len);

protected:
	virtual inline void init_data();
};



#endif //__SE_PRINTFFT_H__
