#include "IPHash.h"

IPHash::IPHash()
{
    m_nTableSize = 100;
    m_arrvecIDsBucket = new vector<ImageDetails>[m_nTableSize];

    for (int i = 0; i < m_nTableSize; i++)
    {
        m_arrvecIDsBucket[i] = vector<ImageDetails>();
    }
}

IPHash::IPHash(int tableSize)
{
    m_nTableSize = tableSize;
    m_arrvecIDsBucket = new vector<ImageDetails>[m_nTableSize];

    for (int i = 0; i < m_nTableSize; i++)
    {
        m_arrvecIDsBucket[i] = vector<ImageDetails>();
    }
}

int IPHash::HashByFileSize(std::streamoff fileSize) // Hashing by fize size may not be the best method
{
    int index = 0;

    index = fileSize % m_nTableSize;

    return index;
}

void IPHash::AddImageByHashIndex(ImageDetails ids, int index)
{
    if (index <= (m_nTableSize - 1))
    {
        m_arrvecIDsBucket[index].push_back(ids);
    }
    else
    {
        cout << "Image couldn't be added to Hash table. Index out of range." << endl;
    }
}

void IPHash::ReportData()
{
    cout << "Image Count = " << m_nTableSize << endl;

    for (int i = 0; i < m_nTableSize; i++)
    {
        cout << "Hash bucket at index " << i << " contains " << m_arrvecIDsBucket[i].size() << " elements." << endl;
    }
}
