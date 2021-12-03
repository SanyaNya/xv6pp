static short* vga_buf = (short*)0xb8000;
static constexpr short color = 0x0200;

static void print(short* buf, const char* str)
{
    while(*str != 0) *buf++ = color | *str++;
}

static inline void print(short* buf, unsigned int i)
{
   *buf++ = color | '0';
   *buf++ = color | 'x';
    for(short* e = buf+7; e != buf-1; i >>= 4, --e)
        *e = color | (i%16 + (i%16 > 9 ? 97-10 : 48));
}
