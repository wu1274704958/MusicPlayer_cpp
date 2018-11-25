//
// Created by wws on 17-7-19.
//

#ifndef FIRST_PRINTFFT_H
#define FIRST_PRINTFFT_H

#include "PrintFFT.h"

class CMDPrintFFT : public PrintFFT {
protected:
    char *data_print;
    int dp_len;
    short *data;
    int data_len;
	short visible_w,visible_h;

	virtual inline void init_data() override;

public:
	CMDPrintFFT();
	CMDPrintFFT(const CMDPrintFFT &pf) = delete;
	CMDPrintFFT(CMDPrintFFT &&pf) = delete;
    virtual ~CMDPrintFFT() override;
    virtual void printFFT(float *fft, int len, float l, float h) override;

	CMDPrintFFT &operator=(CMDPrintFFT &&pf) = delete;

};


#endif //FIRST_PRINTFFT_H
