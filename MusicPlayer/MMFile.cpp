//
// Created by wws on 17-7-19.
//

#include "MMFile.h"
#include <memory>

MMFile::MMFile()
{
    this->type = -1;
    this->name = nullptr;
    this->path = nullptr;
    this->suffix = nullptr;
    this->absolutePath = nullptr;
}

MMFile::MMFile(int type,const char *name, const char *path)
{
    this->type = type;
    this->name = new std::string(name);
    this->path = new std::string(path);
    analysisSuffix();
    analysisAbsolutePath();
}

MMFile::MMFile(const MMFile &mmf)
{
    this->type = mmf.type;
    this->name = new std::string(*(mmf.name));
    this->path = new std::string(*(mmf.path));
    if(mmf.suffix != nullptr)
        this->suffix = new std::string(*(mmf.suffix));
    else
        analysisSuffix();
    if(mmf.absolutePath != nullptr)
        this->absolutePath = new std::string(*(mmf.absolutePath));
    else
        analysisAbsolutePath();
}

MMFile::MMFile(MMFile &&mmf)
{
    this->type = mmf.type;

    this->name = mmf.name;
    this->path = mmf.path;
    this->suffix = mmf.suffix;
    this->absolutePath = mmf.absolutePath;
    mmf.name = nullptr;
    mmf.path = nullptr;
    mmf.suffix = nullptr;
    mmf.absolutePath = nullptr;
}

MMFile::~MMFile()
{
    if(this->name != nullptr)
        delete this->name;
    if(this->path != nullptr)
        delete this->path;
    if(this->suffix != nullptr)
        delete this->suffix;
    if(this->absolutePath != nullptr)
        delete this->absolutePath;
}

int MMFile::getType() const
{
        return this->type;
}

void MMFile::setType(unsigned char t)
{
    type = t;
}

const char* MMFile::getName() const
{
    return name->data();
}

void MMFile::setName(const char *n)
{
    *(name) = n;
}

const char* MMFile::getPath() const
{
    return path->data();
}

void MMFile::setPath(const char *p)
{
    *(path) = p;
}


const char *MMFile::getSuffix() const
{
    return suffix->data();
}

void MMFile::analysisSuffix()
{
    //printf("%s\t",name->c_str());
    int i = 0;
    for(i = name->size() - 1;i >= 0;i--)
    {
        if(*(name->data() + i) == '.')
            break;
    }
    if(i > 0)
    {
        //printf("%d  %s\n", i,temp.c_str());
        suffix = new std::string(name->substr(i));
    }else{
        suffix = new std::string();
    }
}


const char* MMFile::getAbsolutePath() const
{
    return absolutePath->c_str();
}

void MMFile::analysisAbsolutePath()
{
    absolutePath = new std::string();
    absolutePath->operator+=(path->c_str());
    absolutePath->operator+=("\\");
    absolutePath->operator+=(name->c_str());
}


bool MMFile::nameIsLike(const char * str) const
{
	return  name->find(str) != 4294967295;
}
