__THIS FILE IS A COMPILATION OF NOTES THAT MIGHT PROVE USEFUL IN THE FUTURE__

* NOTE: CHECK VALIDATIONS IN TFTP AGAIN!!!!!!!!!! YOU FUCKING MORON!

* NOTE: We could support instant booting if there was a watchdog reset by checking for that. That way reset is instant but reprogram waits.

* NOTE: stk500v2 bootloader only needs avrinterruptname.h and avr_cpunames.h if you want to build the monitor

* NOTE: stk500v2 defines the mcu signature bytes with a comment about that at line ~280. But the are defined also in the includes from <avr/io.h>. Look into it.

* NOTE: The tablejump instructions use the LPM assembler instruction for access to jump tables. Always use -fno-jump-tables switch, if compiling a bootloader for devices with more than 64 KB of code memory. 
  (http://www.nongnu.org/avr-libc/user-manual/using_tools.html)


