#include <fstream>

int main(int argc, char* argv[])
{
    std::ifstream bootsector(argv[1], std::ios::binary);
    std::ifstream kernel(argv[2], std::ios::binary);

    std::ofstream img(argv[3], std::ios::binary); 

    img << bootsector.rdbuf();
    img << kernel.rdbuf();
}
