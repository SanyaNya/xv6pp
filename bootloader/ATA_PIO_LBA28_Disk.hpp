#ifndef ATA_PIO_LBA28_DISK_HPP
#define ATA_PIO_LBA28_DISK_HPP

#include "../libcpp/type_traits.hpp"
#include "../libcpp/cstdint.hpp"
#include "../libcpp/ios.hpp"
#include "x86.hpp"

inline constexpr std::uint32_t SECTOR_SIZE = 512;

class ATA_PIO_LBA28_Disk
{
public:
    using pos_type = std::uint32_t;
    using off_type = pos_type;

    template<typename T>
        requires requires{ std::is_trivial_v<T>; }
    void operator>>(T& t)
    {
        constexpr std::uint32_t sectors_count = (sizeof(T) / SECTOR_SIZE) + 
                                                (sizeof(T) % SECTOR_SIZE ? 1 : 0);
        constexpr std::uint32_t words_count   = sizeof(T)/sizeof(std::uint16_t);

        static_assert(sizeof(T) % 2 == 0);
        static_assert(sectors_count < 256);

        waitdisk();
        x86::outb(std::to_underlying(Port::SECTOR_COUNT), static_cast<std::uint8_t>(sectors_count));
        x86::outb(std::to_underlying(Port::CMD), std::to_underlying(Command::READ_SECTORS));

        waitdisk();
        x86::insd_skip(std::to_underlying(Port::DATA), cur_pos % SECTOR_SIZE);
        x86::insd(std::to_underlying(Port::DATA), reinterpret_cast<unsigned char*>(&t), words_count);

        cur_pos += sizeof(T);
    }

    pos_type tellg() const
    {
        return cur_pos;
    }

    void seekg(pos_type pos)
    {
        cur_pos = pos;
        pos /= SECTOR_SIZE; //sector pos

        waitdisk();

        unsigned char* bytes = reinterpret_cast<unsigned char*>(&pos);
        x86::outb(std::to_underlying(Port::LBA_LO), bytes[0]);
        x86::outb(std::to_underlying(Port::LBA_MID), bytes[1]);
        x86::outb(std::to_underlying(Port::LBA_HI), bytes[2]);
        x86::outb(std::to_underlying(Port::DRIVE_HEAD_LBA_EXT), bytes[3] | 0XE0);
    }

    void seekg(off_type offset, std::ios_base::seekdir dir)
    {
        switch(dir)
        {
            case std::ios_base::cur:
                cur_pos += offset;
                break;
            case std::ios_base::beg:
                cur_pos = offset;
                break;

            default: break;
        }
        seekg(cur_pos);
    }

private:
    pos_type cur_pos;

    enum class Port : std::uint16_t
    {
        IO_BASE            = 0x1F0,
        DATA               = 0x1F0,
        ERROR              = 0x1F1,
        FEATURES           = 0x1F1,
        SECTOR_COUNT       = 0x1F2,
        LBA_LO             = 0x1F3,
        LBA_MID            = 0x1F4,
        LBA_HI             = 0x1F5,
        DRIVE_HEAD_LBA_EXT = 0x1F6,
        STATUS             = 0x1F7,
        CMD                = 0x1F7
    };

    enum class Command : std::uint8_t
    {
        READ_SECTORS = 0x20
        //Others...
    };

    enum class Status : std::uint8_t
    {
        BUSY = 0x40
        //Others...
    };

    Status get_status() const
    {
        return static_cast<Status>(
                x86::inb(std::to_underlying(Port::STATUS)) & 0xC0);
    }

    void waitdisk() const
    {
        while(get_status() != Status::BUSY);
    }
};

#endif //ATA_PIO_LBA28_DISK_HPP
