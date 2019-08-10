#include <Windows.h>
#include <experimental/filesystem>
#include "IPHash.h"

//std::vector<std::vector<ImageDetails>> bigListOfImages = std::vector<std::vector<ImageDetails>>();
//std::regex RemovePath("^\\(. + \\)*(. + )\.(. + )$");

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
    std::string strtmp;
    printf("Please insert path: ");
    std::cin >> strtmp;

    vector<string> fileList = get_filenames(strtmp);
    IPHash hashObj(fileList.size());

    for (const auto& name : fileList)
    {
        ImageDetails tempDetails(name);
        int index;
        index = hashObj.HashByFileSize(tempDetails.GetFileSizeInBytes());
        std::cout << "index = " << index << endl;

        hashObj.AddImageByHashIndex(tempDetails, index);
    }

    hashObj.ReportData();

    while (true)
    {

    }

    return 0;
}