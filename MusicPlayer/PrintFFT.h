//
// Created by wws on 17-7-19.
//

#ifndef FIRST_PRINTFFT_H
#define FIRST_PRINTFFT_H


class PrintFFT {
protected:
    char *data_print;
    int dp_len;
    int *data;
    int data_len;

	virtual inline void init_data();

public:
    PrintFFT();
    PrintFFT(const PrintFFT &pf);
    PrintFFT(PrintFFT &&pf);
    virtual ~PrintFFT();

    
    virtual void printFFT(float *fft,int len);

    PrintFFT &operator=(PrintFFT &&pf);

};


#endif //FIRST_PRINTFFT_H
