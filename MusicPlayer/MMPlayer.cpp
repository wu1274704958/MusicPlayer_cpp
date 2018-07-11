//
// Created by wws on 17-7-19.
//

#include <Windows.h>

#include "MMPlayer.h"
#include "GetFileName.h"
#include <bass.h>
#include <cstring>
#include <conio.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SEPrintFFT.h"
#include "CMDPrintFFT.h"



MMPlayer::MMPlayer(int argc, char **argv)
{
    std::vector<MMFile> *fileList = new std::vector<MMFile>();
    if(argc < 2)
    {
        GetFileName::getFileName(*fileList,"C:\\Users\\ÎâË§½Ü\\Music\\*.*",this);
    }else{
		std::string str(*(argv + 1));
		str += "\\*.*";
        GetFileName::getFileName(*fileList,str.c_str(),this);
    }

    _stack.push(fileList);

    BASS_Init(-1, 44100, 0, NULL, NULL);

    chan = 0;

	nextPattern = NP_MANUAL;

	lastIndex = 1;

	allow_jump = true;

	
	switch (*(argv + 2)[0])
	{
	case 'C':
		pfft = new CMDPrintFFT();
		break;
	case 'G':
		pfft = new SEPrintFFT();
		break;
	default:
		pfft = new CMDPrintFFT();
		break;
	}
}

MMPlayer::~MMPlayer()
{
	if (pfft != nullptr)
		delete pfft;
    for(int i = 0;i < _stack.size();i++)
    {
        delete _stack.top();
        _stack.pop();
    }
    stop();
    BASS_Free();
}

bool MMPlayer::isSupport(const char *s) const
{
    for(int i = 0;i < supportNum;i++)
    {
        if(strcmp(supportList[i],s) == 0)
            return true;
    }
    return false;
}

void gotoxy(int x, int y);
#define CLS printf( "                                                                       \n"  \
					"                                                                       \n"  \
					"                                                                       \n"  \
					"                                                                       \n"  \
					"                                                                       \n"  \
					"                                                                       \n"  \
					"                                                                       \n"  \
					"                                                                       \n"  \
					"                                                                       \n"  \
					"                                                                       \n"  \
					"                                                                       \n"  \
					"                                                                       \n"  \
					"                                                                       \n"  \
					"                                                                       \n"  \
					"                                                                       \n"  \
					"                                                                       \n"  \
					"                                                                       \n"  \
					"                                                                       \n"  \
					"                                                                       \n"  \
					"                                                                       \n"  \
					"                                                                       \n"  \
					)

int MMPlayer::printList()
{
    if(_stack.empty())
    {
        return -1;
    }
    std::vector<MMFile> *v = _stack.top();
	
	gotoxy(0, 0);
	CLS;
	gotoxy(0, 0);
	
    for(int i = 0;i < v->size();i++)
    {
        std::cout << i+1 << ". "<< v->operator[](i).getName()<<std::endl;
    }
    return 0;
}


void MMPlayer::main_loop()
{
    while(true)
    {

        if(printList() == -1)
        {
            return ;
        }

        int index = 0;

        if((index = getNextIndex()) == -1)
        {
            delete _stack.top();
            _stack.pop();
            continue;
        }


        if(_stack.top()->operator[](index - 1).getType() == 16)
        {
            auto v = new std::vector<MMFile>();
			std::string str(_stack.top()->operator[](index - 1).getAbsolutePath());
			str += "\\*.*";
            GetFileName::getFileName(*v,str.c_str(),this);
            _stack.push(std::move(v));
			lastIndex = 1;
            continue;
        }

        playMusic(index - 1);
    }
}

#define w_atoi(buf,res) if(*buf == 48)						\
						{									\
							res = 0;						\
						}else if((res = atoi(buf)) == NULL)  \
						{									\
							res = -2;						\
						}
int MMPlayer::getNextIndex()
{
	int index = 0;
	if (nextPattern == NP_LOOP)
	{
		if (lastIndex == _stack.top()->size())
			index = 1;
		else
			index = lastIndex + 1;
	}

	if (nextPattern == NP_MANUAL)
	{
		std::string str;
		std::cin >> str;
		w_atoi(str.c_str(),index)
		//std::cout << index << std::endl;
		if (index == -2) {
			printSearchList(str.c_str());
			index = getNextIndex();
		}
		if (index <= 0)
			index = -1;
		else if (index > _stack.top()->size())
			index = -1;
	}

	if (nextPattern == NP_RANDOM)
	{
		index = (rand() % _stack.top()->size()) + 1;

	}
	lastIndex = index;

	if (!allow_jump && nextPattern != NP_MANUAL && _stack.top()->operator[](index - 1).getType() == 16)
	{
		return getNextIndex();
	}

	return index;
}

void gotoxy(int x, int y)
{
	auto std_h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(std_h, COORD{ (short)x,(short)y });
}

DWORD print(const char *s, unsigned int len)
{
	auto std_h = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD res = 0;
	WriteConsoleA(std_h, s, len, &res, NULL);
	return res;
}

char CLS_BUF[8000] = { ' ' };

void cls() {
	gotoxy(0, 0);
	print(CLS_BUF, 8000);
}


void MMPlayer::playMusic(int index)
{
    stop();

    chan = BASS_StreamCreateFile(FALSE,(_stack.top()->operator[](index)).getAbsolutePath(), 0, 0, BASS_SAMPLE_FLOAT);
    if (chan == 0)
    {
        int errorCode = BASS_ErrorGetCode();
        printf("errorCode = %d    \n", errorCode);
        return ;
    }

    BASS_ChannelPlay(chan, FALSE);

    float fft[128];
	int start, end;

    while(BASS_ChannelIsActive(chan))
    {
		start = GetTickCount();
		if (_kbhit())
		{
			switch (_getch())
			{

			case 'q':
				stop();
				return;
				break;
			case 'l':
				nextPattern = NP_LOOP;
				break;
			case 'm':
				nextPattern = NP_MANUAL;
				break;
			case 'r':
				nextPattern = NP_RANDOM;
				srand(time(0));
				break;
			case 'p':
				if (BASS_ChannelIsActive(chan) == 3)
					BASS_ChannelPlay(chan, false);
				else
					BASS_ChannelPause(chan);
				break;
			case 'a':
				allow_jump = !allow_jump;
				break;
			default:
				break;
			}
		}
		
        BASS_ChannelGetData(chan, fft, BASS_DATA_FFT256);
		
		//cls();
		gotoxy(0, 0);
		
		float l = 0.5f, h = 0.5f;
		DWORD level = BASS_ChannelGetLevel(chan);
		for (int a = 27204; a > 200; a = a * 2 / 3) {
			if (LOWORD(level) >= a) l += 0.05f;
		}
		for (int a = 210; a<32768; a = a * 3 / 2) {
			if (LOWORD(level) >= a) h += 0.05f;
		}
		pfft->printFFT(fft, 128,l,h);
		
		//std::cout << nextPattern << "  "<< allow_jump <<std::endl;

		end = GetTickCount();

		//std::cout << end - start << std::endl;
		long offset = end - start;
		printf("Next Pattern = %d Allow Jump = %d  ms = %ld", nextPattern, allow_jump, offset);
        Sleep(50 - offset < 0 ? 0 : 50 - offset);
    }
}


void MMPlayer::stop()
{
    if(chan != 0)
        BASS_ChannelStop(chan);
        BASS_StreamFree(chan);
        chan = 0;
}


void MMPlayer::printSearchList(const char *s)
{
	int i = 1;
	auto it = _stack.top()->begin();
	std::cout << "·ûºÏµÄÏî : \n";
	for (; it != _stack.top()->end(); it++,i++)
	{
		if ((*it).nameIsLike(s))
		{
			std::cout << i << " " << (*it).getName() << "\n";
		}
	}
	//std::cout << "\n";
}