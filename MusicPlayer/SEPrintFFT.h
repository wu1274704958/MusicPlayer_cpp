#ifndef __SE_PRINTFFT_H__
#define __SE_PRINTFFT_H__

#include "PrintFFT.h"

class SEPrintFFT : public PrintFFT
{
public:
	SEPrintFFT();
	virtual ~SEPrintFFT() override;
	virtual void printFFT(float *fft, int len, float l, float h) override;

protected:
	virtual inline void init_data() override;
};



#endif //__SE_PRINTFFT_H__
