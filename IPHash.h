#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include "ImageDetails.h"

using namespace std;

#ifndef IPHASH_H
#define IPHASH_H


class IPHash
{
private:
    int m_nTableSize;
    vector<ImageDetails>* m_arrvecIDsBucket;
public:
    int HashByFileSize(std::streamoff fileSize);
    void AddImageByHashIndex(ImageDetails ids, int index);
    void ReportData();
    IPHash();
    IPHash(int tableSize);
    ~IPHash() = default;
};

#endif // !IPHASH_H
