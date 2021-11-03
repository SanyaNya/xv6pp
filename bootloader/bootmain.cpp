static short* vga_buf = (short*)0xb8000;

static constexpr short color = 0x0200;
static const char* msg = "Hello Fluffer from C++! (@w@)";
static constexpr int msglen = 29;

extern "C" void bootmain()
{
   for(int i = 0; i != msglen; ++i)
       vga_buf[i+80] = color | msg[i];
}
