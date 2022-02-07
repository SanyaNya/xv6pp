#ifndef XV6PP_IO_DETAIL_ATA_PIO_LBA28_DISK_HPP
#define XV6PP_IO_DETAIL_ATA_PIO_LBA28_DISK_HPP

#include "../libcpp/cstdint.hpp"
#include "../utils/ebitset.hpp"
#include "../x86.hpp"

namespace xv6pp::io::detail
{

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
    //TODO
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

inline Status get_status()
{
    return Status(x86::inb(Port::STATUS));
}

inline bool is_ready()
{
    Status s = get_status();
    return s[StatusId::READY] && !s[StatusId::BUSY];
}

inline void waitdisk()
{
    while(!is_ready());
}

inline constexpr std::uint8_t MASTER_LBA_MASK = 0xE0;

inline constexpr std::size_t BUFFER_SIZE = 4096; 
inline constexpr std::uint16_t SECTOR_SIZE = 512;

template<typename char_type, typename pos_type>
inline void read(char_type* buffer, pos_type sector_pos)
{
    static_assert(detail::BUFFER_SIZE % SECTOR_SIZE == 0);
    static_assert(detail::BUFFER_SIZE % 4 == 0);

    constexpr std::uint8_t sector_count = BUFFER_SIZE / SECTOR_SIZE;
    constexpr std::size_t  dwords_count  = BUFFER_SIZE / 4;

    waitdisk();
    x86::outb(Port::SECTOR_COUNT, sector_count);

    const std::uint8_t* const bytes = 
        reinterpret_cast<const std::uint8_t* const>(&sector_pos);
    x86::outb(Port::LBA_LO,        bytes[0]);
    x86::outb(Port::LBA_MID,       bytes[1]);
    x86::outb(Port::LBA_HI,        bytes[2]);
    x86::outb(Port::DRIVE_LBA_EXT, bytes[3] | detail::MASTER_LBA_MASK);

    x86::outb(Port::CMD, Command::READ_SECTORS);

    waitdisk();
    x86::insl(Port::DATA, buffer, dwords_count);
}

} //namespace xv6pp::io::detail 

#endif //XV6PP_IO_DETAIL_ATA_PIO_LBA28_DISK_HPP
