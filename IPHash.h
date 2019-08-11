#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include "ImageDetails.h"

using namespace std;

#ifndef IPHASH_H
#define IPHASH_H

// Started out as a hash class, but currently isn't. TODO: Rename class OR make it a hash table

class IPHash
{
private:
    unsigned int m_nTableSize;
    unsigned int m_nImageCount;
    vector<ImageDetails>* m_arrvecIDsBucket;
public:
    //int HashByFileSize(std::streamoff fileSize); // Not a wise move
    //void AddImageByHashIndex(ImageDetails ids, int index);
    void ReportData();
    void ScanForDuplicates();
    void AddImageByFileSize(ImageDetails ids);
    void SortVectorByName(vector<ImageDetails> &aVec);
    void RemoveDuplicates(vector<ImageDetails> aVec);
    IPHash();
    IPHash(int tableSize);
    ~IPHash() = default;
};

#endif // !IPHASH_H
