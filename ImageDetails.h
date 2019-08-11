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

    friend bool operator< (const ImageDetails& leftComp, const ImageDetails& rightComp) // Since the helper functions I'm using don't return a const, I must const cast these calls.
    {
        return const_cast<ImageDetails&>(leftComp).GetFileName().length() < const_cast<ImageDetails&>(rightComp).GetFileName().length(); // by name length
        //return const_cast<ImageDetails&>(leftComp).GetFileSizeInBytes() < const_cast<ImageDetails&>(rightComp).GetFileSizeInBytes(); // by file size
    }
};

#endif // !IMAGEDETAILS_H