#include <fstream>

static char sector[512] = { 0 };

int main()
{
    std::ifstream boot_bin("boot.bin", std::ios::binary);

    boot_bin.read(sector, 512);
    sector[511] = 0xaa; sector[510] = 0x55;

    boot_bin.close();

    std::ofstream bootsector_bin("bootsector.bin", std::ios::binary);
    bootsector_bin.write(sector, 512);
}
