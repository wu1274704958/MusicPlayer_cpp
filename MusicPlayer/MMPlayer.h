//
// Created by wws on 17-7-19.
//

#ifndef FIRST_MMPLAYER_H
#define FIRST_MMPLAYER_H

#include <iostream>
#include <vector>
#include <stack>
#include "MMFile.h"
#include <bass.h>
#include "PrintFFT.h"

enum NextPattern
{
	NP_LOOP = 9,
	NP_RANDOM,
	NP_MANUAL
};

class MMPlayer {
private:
    HSTREAM chan;
    PrintFFT *pfft;

	bool allow_jump;

	NextPattern nextPattern;
	int lastIndex;

    MMPlayer(){};
    const unsigned char supportNum = 2;
    const char *supportList[2] = {
            ".mp3",
            ".flac"
    };

    std::stack<std::vector<MMFile> *> _stack;
public:

    MMPlayer(int argc,char **argv);
    void main_loop();
    virtual ~MMPlayer();

    bool isSupport(const char *s) const;
private:
    int printList();
    virtual void playMusic(int index);

    int getNextIndex();
    void stop();

	int getLoopIndex();
	void printSearchList(const char *s);

};


#endif //FIRST_MMPLAYER_H
