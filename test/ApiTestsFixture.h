#if defined(_WIN32) || defined(__CYGWIN__)
#include <Windows.h>
#endif
#include <fstream>
#include <Api.h>

#ifndef TESSERACT_NATIVE_APITESTSFIXTURE_H
#define TESSERACT_NATIVE_APITESTSFIXTURE_H


class ApiTestsFixture : public ::testing::Test
{
protected:
    __inline void SetUp() override {
        std::string exeDir = GetExeDir();
        filePaths.push_back(exeDir + "\\resources\\test.bmp");
        filePaths.push_back(exeDir + "\\resources\\test.jpg");
        filePaths.push_back(exeDir + "\\resources\\test.png");
        filePaths.push_back(exeDir + "\\resources\\test.tif");

        api = new Api();
    }

    __inline void TearDown() override {
        filePaths.clear();
        delete(api);
    }

    std::vector<std::string > filePaths;

    __inline bool exists(const std::string& name) {
        std::ifstream file(name.c_str());
        bool result = file.good();
        file.close();
        return result;
    }

    /**
     * Get executable directory for current executable.
     * @return Executable dir as string.
     */
    std::string GetExeDir()
    {
#if defined(_WIN32) || defined(__CYGWIN__)
        CHAR buf[1024] = { 0 };
        GetModuleFileName(nullptr, buf, sizeof(buf));
        auto res = std::string(buf);

#elif defined(__linux)
        #include <limits.h>
#include <unistd.h>
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    auto res std::wstring(result, (count > 0) ? count : 0);
#else
#error Invalid OS version. Currently the Test application only supports Windows and Linux.
#endif
        return res.substr(0, res.find_last_of('\\'));
    }

    Api* api;

};


#endif //TESSERACT_NATIVE_APITESTSFIXTURE_H
