#include <Windows.h>
#include <experimental/filesystem>
#include "IPHash.h"

// Author: Brandon Mason
// Purpose: This program has a very specific purpose and is made to suit my needs.
// Scenario: I have a meme folder that I've been saving images into for years. Over time I've saved the same image into this folder multiple times.
// 1. You have to type in the folder path manually, which I have no problem with.
// 2. This program doesn't doesn't search in sub-folders.
// 3. The hash key generation is based on fize sizes which best suited the original needs of this program.

std::vector<std::string> get_filenames(std::experimental::filesystem::path path)
{
    namespace stdfs = std::experimental::filesystem;

    std::vector<std::string> filenames;

    const stdfs::directory_iterator end{};

    for (stdfs::directory_iterator iter{ path }; iter != end; ++iter)
    {
        if (stdfs::is_regular_file(*iter))
        {
            filenames.push_back(iter->path().string());
        }
    }

    return filenames;
}

int main(int argc, char *argv[])
{
    string strtmp;
    cout << ("Please insert folder's path: ");
    cin >> strtmp;

    vector<string> fileList = get_filenames(strtmp);
    IPHash hashObj(fileList.size());

    for (const auto& name : fileList)
    {
        ImageDetails tempDetails(name);
        hashObj.AddImageByFileSize(tempDetails);
    }


    while (true)
    {
        hashObj.ReportData();
        unsigned int selection;
        cout << "*** Please Select an option ***" << endl;
        cout << "1. Scan for duplicate files." << endl;
        cout << "2. <Incomplete> Prune based on dimensions." << endl; // TODO
        cout << "3. Exit." << endl;
        cin >> selection;

        if (selection == 1)
        {
            hashObj.ScanForDuplicates();
        }
        else if (selection == 3)
        {
            exit(EXIT_SUCCESS);
        }
    }

    return 0;
}