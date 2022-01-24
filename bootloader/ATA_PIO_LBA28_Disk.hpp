#ifndef ATA_PIO_LBA28_DISK_HPP
#define ATA_PIO_LBA28_DISK_HPP

#include "../libcpp/type_traits.hpp"
#include "../libcpp/cstdint.hpp"
#include "../libcpp/ios.hpp"
#include "../libcpp/algorithm.hpp"
#include "../utils/ebitset.hpp"
#include "x86.hpp"
#include "bootloader_new.hpp"

namespace xv6pp
{

inline constexpr std::uint32_t SECTOR_SIZE = 512;

template<std::size_t BUFFER_SIZE>
class ATA_PIO_LBA28_Disk
{
public:
    using pos_type = std::uint32_t;
    using off_type = pos_type;

    ATA_PIO_LBA28_Disk()
        : cur_pos(0), 
          buffer(*new std::array<std::uint8_t, BUFFER_SIZE>)
    {
        static_assert(BUFFER_SIZE % SECTOR_SIZE == 0);
        static_assert(BUFFER_SIZE % 4 == 0);

        constexpr std::uint8_t sector_count = BUFFER_SIZE / SECTOR_SIZE;
        constexpr std::size_t  words_count  = BUFFER_SIZE / 4;

        waitdisk();
        x86::outb(Port::SECTOR_COUNT, sector_count);

        pos_type sector_pos = 1;
        std::uint8_t* bytes = reinterpret_cast<std::uint8_t*>(&sector_pos);
        x86::outb(Port::LBA_LO,        bytes[0]);
        x86::outb(Port::LBA_MID,       bytes[1]);
        x86::outb(Port::LBA_HI,        bytes[2]);
        x86::outb(Port::DRIVE_LBA_EXT, bytes[3] | 0xE0);

        x86::outb(Port::CMD, Command::READ_SECTORS);

        waitdisk();
        x86::insl(Port::DATA, buffer.data(), words_count);
    }

    void read(std::uint8_t* buf, std::size_t size)
    {
        std::copy(
                buffer.data()+cur_pos, 
                buffer.data()+cur_pos+size, 
                buf);
        cur_pos += size;
    }

    template<typename T>
        requires requires{ std::is_trivial_v<T>; }
    void operator>>(T& t)
    {
        read(reinterpret_cast<std::uint8_t*>(&t), sizeof(T));
    }

    pos_type tellg() const
    {
        return cur_pos;
    }

    void seekg(pos_type pos)
    {
        cur_pos = pos;
    }

private:
    pos_type cur_pos;
    std::array<std::uint8_t, BUFFER_SIZE>& buffer;

    enum class Port : std::uint16_t
    {
        IO_BASE       = 0x1F0,
        DATA          = 0x1F0,
        ERROR         = 0x1F1,
        FEATURES      = 0x1F1,
        SECTOR_COUNT  = 0x1F2,
        LBA_LO        = 0x1F3,
        LBA_MID       = 0x1F4,
        LBA_HI        = 0x1F5,
        DRIVE_LBA_EXT = 0x1F6,
        STATUS        = 0x1F7,
        CMD           = 0x1F7
    };

    enum class Command : std::uint8_t
    {
        READ_SECTORS = 0x20
        //Others...
    };

    enum class StatusId
    {
        ERROR,
        INDEX,
        CORRECTED_DATA,
        DRIVE_READY_QUERY,
        SERVICE_REQUEST,
        DRIVE_FAULT,
        READY,
        BUSY
    };
    using Status = ebitset<8, StatusId>;

    const Status get_status() const
    {
        return Status(x86::inb(Port::STATUS));
    }

    void waitdisk() const
    {
        for(Status s = get_status();
            s[StatusId::READY] && !s[StatusId::BUSY];
            s = get_status());
    }
};

} //namesapce xv6pp

#endif //ATA_PIO_LBA28_DISK_HPP
