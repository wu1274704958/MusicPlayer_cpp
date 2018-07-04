//
// Created by wws on 17-7-19.
//

#include "GetFileName.h"

#include <cstring>
#include "MMPlayer.h"

void GetFileName::getFileName(std::vector<MMFile> &v, const char *d,class MMPlayer *player)
{
	_WIN32_FIND_DATAA ffd;
	HANDLE han = nullptr;

	std::string dir(d);
	dir = dir.substr(0, strlen(d) - 4);

	std::cout << dir << std::endl;
    
	if ((han = FindFirstFile(d, &ffd)) != nullptr)
	{
		
		while(FindNextFile(han, &ffd))
		{
			if (strcmp(ffd.cFileName, ".") == 0 || strcmp(ffd.cFileName, "..") == 0)
				continue;
			//std::cout << ffd.dwFileAttributes << "  " << ffd.cFileName <<  std::endl;
			MMFile tempFile(ffd.dwFileAttributes, ffd.cFileName, dir.c_str());
			if (player->isSupport(tempFile.getSuffix()) || tempFile.getType() == 16)
				v.push_back(std::move(tempFile));
			
		}
	}
    
   
}
