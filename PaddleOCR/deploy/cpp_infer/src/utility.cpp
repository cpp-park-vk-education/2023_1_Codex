#include <dirent.h>
#include <utility.h>

#include <vector>

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

namespace PaddleOCR {

std::vector<std::string> Utility::ReadDict(const std::string &path) {
    std::ifstream in(path);
    std::string line;
    std::vector<std::string> m_vec;
    if (in) {
        while (getline(in, line)) {
            m_vec.push_back(line);
        }
    } else {
        std::cout << "no such label file: " << path << ", exit the program..." << std::endl;
        exit(1);
    }
    return m_vec;
}

std::vector<int> Utility::argsort(const std::vector<float> &array) {
    const int array_len(array.size());
    std::vector<int> array_index(array_len, 0);
    for (int i = 0; i < array_len; ++i) array_index[i] = i;

    std::sort(array_index.begin(), array_index.end(),
              [&array](int pos1, int pos2) { return (array[pos1] < array[pos2]); });

    return array_index;
}

bool Utility::PathExists(const std::string &path) {
#ifdef _WIN32
    struct _stat buffer;
    return (_stat(path.c_str(), &buffer) == 0);
#else
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
#endif  // !_WIN32
}

}  // namespace PaddleOCR
