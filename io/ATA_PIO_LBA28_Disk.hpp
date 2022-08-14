#ifndef XV6PP_IO_DETAIL_ATA_PIO_LBA28_DISK_HPP
#define XV6PP_IO_DETAIL_ATA_PIO_LBA28_DISK_HPP

#include "../libcpp/cstdint.hpp"
#include "../libcpp/cstddef.hpp"
#include "../libcpp/span.hpp"
#include "../utils/bitfield.hpp"
#include "../x86/intrinsics.hpp"

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

struct Status : bitfield<Status, std::byte>
{
    using bitfield::bitfield;

    std::uint8_t ERROR             : 1;
    std::uint8_t INDEX             : 1;
    std::uint8_t CORRECTED_DATA    : 1;
    std::uint8_t DRIVE_READY_QUERY : 1;
    std::uint8_t SERVICE_REQUEST   : 1;
    std::uint8_t DRIVE_FAULT       : 1;
    std::uint8_t READY             : 1;
    std::uint8_t BUSY              : 1;
};

inline Status get_status()
{
    return x86::inb(Port::STATUS);
}

inline bool is_ready()
{
    Status s = get_status();
    return s.READY && !s.BUSY;
}

inline void waitdisk()
{
    while(!is_ready());
}

constexpr std::byte MASTER_LBA_MASK {0xE0};

constexpr std::uint16_t SECTOR_SIZE = 512;

template<typename pos_type>
constexpr pos_type align_buf(pos_type pos)
{
    return pos - (pos % SECTOR_SIZE);
}

template<typename pos_type>
constexpr pos_type buf_align_indent(pos_type pos)
{
    return pos % SECTOR_SIZE;
}

template<typename pos_type>
constexpr pos_type buf_sector(pos_type pos)
{
    return pos / SECTOR_SIZE;
}

template<typename char_type, std::size_t BUFFER_SIZE>
inline void read(std::span<char_type, BUFFER_SIZE> buffer, std::uint32_t sector_pos)
{
    static_assert(BUFFER_SIZE != std::dynamic_extent);
    static_assert(BUFFER_SIZE % SECTOR_SIZE == 0);
    static_assert(BUFFER_SIZE % 4 == 0);

    constexpr std::uint8_t SECTOR_COUNT = BUFFER_SIZE / SECTOR_SIZE;
    constexpr std::size_t  DWORDS_COUNT = BUFFER_SIZE / 4;

    waitdisk();
    x86::outb(Port::SECTOR_COUNT, SECTOR_COUNT);

    std::byte* bytes = reinterpret_cast<std::byte*>(&sector_pos);
    x86::outb(Port::LBA_LO,        bytes[0]);
    x86::outb(Port::LBA_MID,       bytes[1]);
    x86::outb(Port::LBA_HI,        bytes[2]);
    x86::outb(Port::DRIVE_LBA_EXT, bytes[3] | MASTER_LBA_MASK);

    x86::outb(Port::CMD, Command::READ_SECTORS);

    waitdisk();
    x86::insl(Port::DATA, buffer.data(), DWORDS_COUNT);
}

} //namespace xv6pp::io::detail 

#endif //XV6PP_IO_DETAIL_ATA_PIO_LBA28_DISK_HPP
