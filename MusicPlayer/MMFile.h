//
// Created by wws on 17-7-19.
//

#ifndef FIRST_MMFILE_H
#define FIRST_MMFILE_H

#include <iostream>
#include <string>

class MMFile {
private:

    unsigned char type;
    std::string *name;
    std::string *path;
    std::string *suffix;
    std::string *absolutePath;
public:

    MMFile();
    MMFile(int type,const char *name,const char *path);
    MMFile(const MMFile &mmf);
    MMFile(MMFile &&mmf);

    int getType() const;
    void setType(unsigned char t);

    const char *getName() const;
    void setName(const char *n);

    const char *getPath() const;
    void setPath(const char *p);

    const char *getSuffix() const;
    const char *getAbsolutePath() const;

	bool nameIsLike(const char *str) const;

    virtual  ~MMFile();


private:
    void analysisSuffix();
    void analysisAbsolutePath();
};


#endif //FIRST_MMFILE_H
