#include "IPHash.h"
#include <algorithm>

IPHash::IPHash()
{
    m_nTableSize = 100;
    m_nImageCount = 0;
    m_arrvecIDsBucket = new vector<ImageDetails>[m_nTableSize];

    for (unsigned int i = 0; i < m_nTableSize; i++)
    {
        m_arrvecIDsBucket[i] = vector<ImageDetails>();
    }
}

IPHash::IPHash(int tableSize)
{
    m_nTableSize = tableSize;
    m_nImageCount = 0;
    m_arrvecIDsBucket = new vector<ImageDetails>[m_nTableSize];

    for (unsigned int i = 0; i < m_nTableSize; i++)
    {
        m_arrvecIDsBucket[i] = vector<ImageDetails>();
    }
}

//int IPHash::HashByFileSize(std::streamoff fileSize) // Hashing by fize size is NOT the best method
//{
//    int index = 0;
//
//    index = fileSize % m_nTableSize;
//
//    return index;
//}

void IPHash::AddImageByFileSize(ImageDetails ids)
{
    for (unsigned int i = 0; i < m_nTableSize; i++)
    {
        if (m_arrvecIDsBucket[i].size() == 0)
        {
            m_arrvecIDsBucket[i].push_back(ids);
            ++m_nImageCount;
            return;
        }
        else if (m_arrvecIDsBucket[i][0].GetFileSizeInBytes() == ids.GetFileSizeInBytes())
        {
            m_arrvecIDsBucket[i].push_back(ids);
            ++m_nImageCount;
            return;
        }
    }

    cout << "Image " << ids.GetFileName() << " not added to bucket." << endl;
}

//void IPHash::AddImageByHashIndex(ImageDetails ids, int index)
//{
//    if (index >= 0 && index <= (m_nTableSize - 1))
//    {
//        m_arrvecIDsBucket[index].push_back(ids);
//        ++m_nImageCount;
//    }
//    else
//    {
//        cout << "Image couldn't be added to Hash table. Index out of range." << endl;
//    }
//}

void IPHash::ReportData()
{
    cout << "Image Count = " << m_nImageCount << endl;

    //for (int i = 0; i < m_nTableSize; i++)
    //{
    //    cout << "Hash bucket at index " << i << " contains " << m_arrvecIDsBucket[i].size() << " elements." << endl;
    //}
}

void IPHash::RemoveDuplicates(vector<ImageDetails> aVec)
{

}

void IPHash::SortVectorByName(vector<ImageDetails> &aVec)
{
    sort(aVec.begin(), aVec.end());
}

// Scanning for duplicates currently only looks a the file size.
// TODO:
// 1. Compare file types
// 2. Compare file dimensions
// 3. After the program is certain that it has found a duplicate, open/display them.

void IPHash::ScanForDuplicates()
{
    // First find files that share the same size in bytes
    for (unsigned int i = 0; i < m_nTableSize; i++)
    {
        if (m_arrvecIDsBucket[i].size() > 1)
        {
            // extra code to save time/memory
            if (m_arrvecIDsBucket[i].size() == 2 && m_arrvecIDsBucket[i][0].GetFileSizeInBytes() == m_arrvecIDsBucket[i][1].GetFileSizeInBytes())
            {
                cout << m_arrvecIDsBucket[i][0].GetFileName() << " is the same size as " << m_arrvecIDsBucket[i][1].GetFileName() << ".\n";
                char input;
                cout << "Delete file with the longer name? Y/N" << endl;
                cin >> input;
                if (input == 'Y' || input == 'y')
                {
                    if (m_arrvecIDsBucket[i][0].GetFileName().length() > m_arrvecIDsBucket[i][1].GetFileName().length())
                    {
                        if (remove(m_arrvecIDsBucket[i][0].GetFullFilePath().c_str()) == 0)
                        {
                            --m_nImageCount;
                            m_arrvecIDsBucket[i].erase(m_arrvecIDsBucket[i].begin());
                        }
                    }
                    else
                    {
                        if (remove(m_arrvecIDsBucket[i][1].GetFullFilePath().c_str()) == 0)
                        {
                            --m_nImageCount;
                            m_arrvecIDsBucket[i].erase(m_arrvecIDsBucket[i].begin() + 1);
                        }
                    }
                }
            }
            else
            {
                SortVectorByName(m_arrvecIDsBucket[i]); // Sort by the name's length in ascending order
                
                cout << "The following images are suspected to be identical: " << endl;
                for (size_t identical = 0; identical < m_arrvecIDsBucket[i].size(); identical++)
                {
                    cout << m_arrvecIDsBucket[i][identical].GetFileName() << endl;
                }

                char input;
                cout << endl << "Delete file(s) with longest name(s)? Y/N" << endl;
                cin >> input;
                if (input == 'Y' || input == 'y')
                {
                    while (m_arrvecIDsBucket[i].size() != 1)
                    {
                        size_t currSize = m_arrvecIDsBucket[i].size() - 1;
                        if (remove(m_arrvecIDsBucket[i][currSize].GetFullFilePath().c_str()) == 0)
                        {
                            --m_nImageCount;
                            m_arrvecIDsBucket[i].pop_back();
                        }
                    }
                }
            }
        }
    }
}
