authors: Ian & Cheko

This program imitates the working of a linker in libc.
It fills the right address of named functions from the 
global offset table to be used by the program currently running.
Below is the description that shows the working of the program.

Our script:
We demonstrate the linking worked by going to the first occurence of puts,
and checking to see if the linking code is called after, or if puts is called.
In our case we go to this code, and the first jump statement, jumps to
the libc code for puts. Therefore we know that our manual linking was sucessful.

Script started on 2021-11-07 17:40:36-05:00 [TERM="linux" TTY="/dev/tty1" COLUMNS="240" LINES="67"]

[?2004hian:assignment4$ gdb self-linker
[?2004l
[35;1mGNU gdb (GDB) 11.1[m
Copyright (C) 2021 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-pc-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from [32mself-linker[m...

Line 27 is the first occurence of puts.
We want to go there and check if the linker is called.

[?2004h(gdb) b 27
[?2004l
Breakpoint 1 at [34m0x1258[m: file [32mself-linker.c[m, line 27.

We begin the program here.

[?2004h(gdb) r
[?2004l
Starting program: /home/ian/Code/assignment4/self-linker 



We reach the breakpoint.

Breakpoint 1, [33mmain[m ([36margc[m=1, [36margv[m=0x7fffffffeb18) at [32mself-linker.c[m:27

Within the puts call, we have to go 3 instructions to reach the actual call.

27		[01mputs[m[31m([m[31m"TEST1"[m[31m);[m
[?2004h[?2004l
[?2004h(gdb) si
[?2004l
[34m0x000055555555525f[m	27		[01mputs[m[31m([m[31m"TEST1"[m[31m);[m
[?2004h[?2004l
[?2004h(gdb) si
[?2004l
[34m0x0000555555555262[m	27		[01mputs[m[31m([m[31m"TEST1"[m[31m);[m
[?2004h[?2004l
[?2004h(gdb) si

We reach the puts call.

[?2004l
[34m0x0000555555555030[m in [33mputs@plt[m ()

Now we disas to look at the code.

[?2004h[?2004l
[?2004h(gdb) disas
[?2004l
Dump of assembler code for function [33mputs@plt[m:
=> [34m0x0000555555555030[m <+0>:	jmp    *0x2fe2(%rip)        # [34m0x555555558018[m <[33mputs@got.plt[m>
   [34m0x0000555555555036[m <+6>:	push   $0x0
   [34m0x000055555555503b[m <+11>:	jmp    [34m0x555555555020[m
End of assembler dump.

If we after this instruction we are still in the plt, the linker was called.
If we are in puts, we know that our linking was successful.

[?2004h(gdb) si
[?2004l
[34m0x00007ffff7e58ab0[m in [33mputs[m () from [32m/usr/lib/libc.so.6[m

We see that we are in puts in /usr/lib/libc.so.6, so we know we where successful.

[?2004h[?2004l
[?2004h(gdb) [?2004l
quit
[?2004hA debugging session is active.

	Inferior 1 [process 1002] will be killed.

Quit anyway? (y or n) y
[?2004l
[?2004hian:assignment4$ [?2004l

exit

Now we exit the debugging session.

Script done on 2021-11-07 17:41:04-05:00 [COMMAND_EXIT_CODE="0"]
