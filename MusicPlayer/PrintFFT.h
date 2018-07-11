#ifndef PRINT_FFT_ABSTRACT
#define PRINT_FFT_ABSTRACT

class PrintFFT{
public:
	virtual ~PrintFFT() {};
	virtual void printFFT(float *fft, int len,float l,float h) = 0;
	virtual void init_data() = 0;
};

#endif //PRINT_FFT_ABSTRACT