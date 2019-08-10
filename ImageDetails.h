#pragma once
#include <string>

#ifndef IMAGEDETAILS_H
#define IMAGEDETAILS_H

class ImageDetails
{
private:
    std::string m_szFileName;
    std::string m_szFullFilePath;
    std::streamoff m_nfileSizeInBytes;
    unsigned int m_unPixelWidth;
    unsigned int m_unPixelHeight;
public:
    ImageDetails() = default;
    ImageDetails(std::string fullFilePath);
    ~ImageDetails() = default;

    std::string GetFullFilePath() { return m_szFullFilePath; }
    std::string GetFileName() { return m_szFileName; }
    std::streamoff GetFileSizeInBytes() { return m_nfileSizeInBytes; }
};

#endif // !IMAGEDETAILS_H