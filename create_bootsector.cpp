#include <fstream>

static char sector[512] = { 0 };

int main()
{
    std::ifstream kernel_bin("kernel.bin", std::ios::binary);

    kernel_bin.read(sector, 512);
    sector[511] = 0xaa; sector[510] = 0x55;

    kernel_bin.close();

    std::ofstream boot_kernel_bin("kernel.bin", std::ios::binary);
    boot_kernel_bin.write(sector, 512);
}
