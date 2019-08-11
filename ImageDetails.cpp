#include "ImageDetails.h"
#include <fstream>
#include <iostream>
#include <winsock.h>

ImageDetails::ImageDetails(std::string fullFilePath)
{
    char fileName[256];
    m_szFullFilePath = fullFilePath;
    if (_splitpath_s(fullFilePath.c_str(), NULL, 0, NULL, 0, fileName, 256, NULL, 0) == 0)
    {
        m_szFileName = fileName;
    }

    std::ifstream file(fullFilePath.c_str(), std::ios::binary | std::ios::ate);
    m_nfileSizeInBytes = file.tellg();
    //std::cout << m_szFileName << "'s size is " << m_nfileSizeInBytes << " bytes. \n";

    if (fullFilePath.find(".png") != std::string::npos)
    {
        unsigned int width = 0, height = 0;
        file.seekg(16);
        file.read((char*)& width, 4);
        file.read((char*)& height, 4);

        m_unPixelWidth = ntohl(width);
        m_unPixelHeight = ntohl(height);

        //std::cout << m_szFileName << " is " << m_unPixelWidth << " pixels wide and " << m_unPixelHeight << " pixels high.\n";
    }
    else
    {
        // JPG files require a library to uncompress in order to access the data.
        // TODO: Store image dimensions for JPG files
        //std::cout << "Program doesn't yet handle this file type.\n";
    }

    file.close();
}