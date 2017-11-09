# What is the difference between a 32-bit and 64-bit processor?

All calculations take place in the registers. When you're adding (or subtracting, or whatever) variables together in your code, they get loaded from memory into the registers (if they're not already there, but while you can declare an infinite number of variables, the number of registers is limited). So, having larger registers allows you to perform "larger" calculations in the same time. Not that this size-difference matters so much in practice when it comes to regular programs (since at least I rarely manipulate values larger than 2^32), but that is how it works.

Also, certain registers are used as pointers into your memory space and hence limits the maximum amount of memory that you can reference. A 32-bit processor can only reference 2^32 bytes (which is about 4 GB of data). A 64-bit processor can manage a whole lot more obviously.

# What is the meaning of 32 bit or 64 bit process?

The virtual addresses of a process are the mappings of an address table that correspond to real physical memory on the system. For reasons of efficiency and security, the kernel creates an abstraction for a process that gives it the illusion of having its own address space. This abstraction is called a virtual address space. It's just a table of pointers to physical memory.

So a 32-bit process is given about 2^32 or 4GB of address space. What this means under the hood is that the process is given a 32-bit page table. In addition, this page table has a 32-bit VAS(Virtual Address Space) that maps to 4GB of memory on the system.

So yes, a 64-bit process has a 64-bit VAS.

#  thread vs process

Processes are the abstraction of running programs: A binary image, virtualized memory, various kernel resources, an associated security context, and so on. Threads are the unit of execution in a process: A virtualized processor, a stack, and program state. Put another way, processes are running binaries and threads are the smallest unit of execution schedulable by an operating system's process scheduler.

Each process provides the resources needed to execute a program. A process has a virtual address space, executable code, open handles to system objects, a security context, a unique process identifier, environment variables, a priority class, minimum and maximum working set sizes, and at least one thread of execution. Each process is started with a single thread, often called the primary thread, but can create additional threads from any of its threads.

A thread is the entity within a process that can be scheduled for execution. All threads of a process share its virtual address space and system resources. In addition, each thread maintains exception handlers, a scheduling priority, thread local storage, a unique thread identifier, and a set of structures the system will use to save the thread context until it is scheduled.

Typical difference is：

* processes run in separated memory while threads run in shared memory.  
* processes are typically independent, while threads exist as subsets of a process  
* processes carry considerably more state information than threads, whereas multiple threads within a process share process state as well as memory and other resources  
* processes have separate address spaces, whereas threads share their address space processes interact only through system-provided inter-process communication mechanisms  
* context switching between threads in the same process is typically faster than context switching between processes.  

# What's happened in the Linux System after using 'ls' command

* https://discuss.leetcode.com/topic/91092/elaborate-what-happens-under-the-hood-after-typing-ls

1. First of all, whenever we press a key on keyboard, the keyboard controller will emit an interrupt to processor(CPU) indicating there is an event that needs immediate attention. As interrupts usually have high priority, the processor will suspending its current execution, save its state, and call an interrupt handler(should be the one that handles keyboard interrupt). Suppose we type 'l' then this character will be written the file that fd stdout points to, while shell's stdout usually points to screen (a device, in *nix familiy, everything "looks" like a file), then "l" will be shown on the screen. After the interrupt handler finishes its job, the process will resume its original work.

2. We type 'ls' and hit enter, then shell will first check out $PATH environment variable to see if there is a program 'ls' under each given path. Suppose we find /usr/bin/ls. Shell will call fork(), followed by execve("/usr/bin/ls"). fork() will create an identical child process and return twice. In parent(shell), it will typically call wait() to wait child process to complete. In child, it will execute execve() and a successful execve() will replace original data(including text, data, heap and stack, etc) in the child process's address space with new data in order to run the new executable. Note that file descriptors opened by parent will be kept(that is why output from ls will be displayed on screen like shell).

3. Then the child process will be one that runs "/usr/bin/ls" code, it will make system calls(open(2), printf(3c) etc.) to list directory entries in the current working directory. After the child process finishes its job, it will call exit()(usually called implicitly by 'return' in main()). Then all of the fds, streams will be closed. The parent process(in this case the shell) will be notified of child's termination, so wait() will be return and child exit code could be read from wait(). Then parent process(the shell) can proceed, waiting for next command to run.

### Follow ups:

What will happen if another interrupt is received while the processor is running interrupt handler code?

A: Different OS may have different ways to deal with this situation. For linux, task of an interrupt handler is split into two halves, top half and bottom half. Top half runs with interrupts disabled and respond to the interrupt as fast as possible, then bottom half runs with interrupts enabled for as long as it needs and could be preempted.

What do we call a child process when it terminates but its status has not been read by its parent which calls wait()?

A: Zombie process.

what is value of fd(in most case) will be returned by open() calling in the child process("/usr/bin/ls")?

A: 3, because stdin, stdout, stderr, will be 0, 1, 2 respectively, and lowest available fd will be returned.

How is parent process notified when its children terminate?

A: SIGCHLD will be sent to the parent process.

How does shell implement I/O redirection if we want to redirect output of ls to another command as its input? like "ls | sort"

A: Briefly speaking, shell will call a pipe() before fork() to get two fds, rfd for read end and wfd for write end, then call dup2(wfd, 1) in ls and dup2(rfd, 0) in sort.

# How to/best practices to write a thread safe code?

# How to debug segmentation fault? What are the best practices to avoid segmentation faults in the code?

Segmenfault is relatively easy to debug, but hard to avoid. Segmenfault mostly implies null pointer or wild pointer.

debug: core dump file & gdb; debugfs, dmesg

#### avoid

* assert() before dereferencing suspective pointers, mainly pointers embedded in structs that are maintained in containers in lists and arrays.  
* always remember to initialize pointers properly.  
* protect global/shared variables from concurrent threads with mutex,semaphore(avoid shared access if possible).  
* do free()s carefully, maybe with proper refcount on objects(also set NULL after free()).  

# What happens in the background from the time you press the Power button until the Linux login prompt appears?

![alt](https://discuss.leetcode.com/assets/uploads/files/1497762554789-image2.png)

### 1) BIOS - THE FIRST STEP

![alt](https://discuss.leetcode.com/assets/uploads/files/1497762591477-image7.png)

The __Basic Input/Output System (BIOS)__ initializes the hardware, including the screen and keyboard, and tests the main memory. This process is also called __POST (Power On Self Test)__.

The BIOS software is stored on a ROM chip on the motherboard. After this, the remainder of the boot process is completely controlled by the operating system.

### 2) MASTER BOOT RECORDS (MBR) AND BOOT LOADER

![alt](https://discuss.leetcode.com/assets/uploads/files/1497762625150-image5.png)

Once the POST is completed, the system control passes from the BIOS to the boot loader. The boot loader is usually stored on one of the hard disks in the system, either in the boot sector (for traditional __BIOS/MBR__ systems). Up to this stage, the machine does not access any mass storage media. Thereafter, information on the date, time, and the most important peripherals are loaded from the CMOS values (after a technology used for the battery-powered memory store - which allows the system to keep track of the date and time even when it is powered off).

A number of boot loaders exist for Linux; the most common ones are __GRUB__ (for __GRand Unified Boot loader__) and ISOLINUX (for booting from removable media). Most Linux boot loaders can present a user interface for choosing alternative options for booting Linux, and even other operating systems that might be installed. When booting Linux, the boot loader is responsible for loading the kernel image and the initial RAM disk (which contains some critical files and device drivers needed to start the system) into memory.

### 3) BOOT LOADER IN ACTION

![alt](https://discuss.leetcode.com/assets/uploads/files/1497762661184-image8.jpg)

The boot loader has two distinct stages:

##### First Stage:

For systems using the BIOS/MBR method, the boot loader resides at the first sector of the hard disk also known as the __Master Boot Record(MBR)__. The size of the MBR is just 512 bytes. In this stage, the boot loader examines the partition table and finds a bootable partition. Once it finds a bootable partition, it then searches for the second stage bootloader e.g, GRUB, and loads it into __RAM (Random Access Memory)__.

##### Second Stage:

The second stage boot loader resides under /boot. A splash screen is displayed which allows us to choose which Operating System (OS) to boot. After choosing the OS, the boot loader loads the kernel of the selected operating system into RAM and passes control to it.

The boot loader loads the selected kernel image (in the case of Linux) and passes control to it. Kernels are almost always compressed, so it's first job is to uncompress itself. After this, it will check and analyze the system hardware and initialize any hardware device drivers built into the kernel.

### 4) THE LINUX KERNEL

![alt](https://discuss.leetcode.com/assets/uploads/files/1497762678423-image10.jpg)

The boot loader loads both the kernel and an initial RAM–based filesystem (initramfs) into memory so it can be used directly by the kernel.

When the kernel is loaded in RAM, it immediately initializes and configures the computer’s memory and also configures all the hardware attached to the system. This includes all processors, I/O subsystems, storage devices, etc. The kernel also loads some necessary user space applications.

### 5) THE INITIAL RAM DISK

![alt](https://discuss.leetcode.com/assets/uploads/files/1497762712294-image4.jpg)

The initramfs filesystem image contains programs and binary files that perform all actions needed to mount the proper root filesystem, like providing kernel functionality for the needed file system and device drivers for mass storage controllers with a facility called udev (for User Device) which is responsible for figuring out which devices are present, locating the drivers they need to operate properly, and loading them. After the root filesystem has been found, it is checked for errors and mounted.

The mount program instructs the operating system that a file system is ready for use, and associates it with a particular point in the overall hierarchy of the filesystem (the mount point). If this is successful, the initramfs is cleared from RAM and the init program on the root filesystem (/sbin/init) is executed.

init handles the mounting and pivoting over to the final real root filesystem. If special hardware drivers are needed before the mass storage can be accessed, they must be in the initramfs image.

### 6) /SBIN/INIT AND SERVICES

![alt](https://discuss.leetcode.com/assets/uploads/files/1497762733204-image9.jpg)

Once the kernel has set up all its hardware and mounted the root filesystem, the kernel runs the /sbin/init program. This then becomes the initial process, which then starts other processes to get the system running. Most other processes on the system trace their origin ultimately to init; the exceptions are kernel processes, started by the kernel directly for managing internal operating system details.

Traditionally, this process startup was done using conventions that date back to System V UNIX, with the system passing through a sequence of runlevels containing collections of scripts that start and stop services. Each runlevel supports a different mode of running the system. Within each runlevel, individual services can be set to run, or to be shut down if running. Newer distributions are moving away from the System V standard, but usually support the System V conventions for compatibility purposes.

Besides starting the system, __init__ is responsible for keeping the system running and for shutting it down cleanly. It acts as the "manager of last resort" for all non-kernel processes, cleaning up after them when necessary, and restarts user login services as needed when users log in and out.

### 7) TEXT-MODE LOGIN

![alt](https://discuss.leetcode.com/assets/uploads/files/1497762752651-image3.jpg)

Near the end of the boot process, init starts a number of text-mode login prompts (done by a program called getty). These enable you to type your username, followed by your password, and to eventually get a command shell.

Usually, the default command shell is bash (the GNU Bourne Again Shell), but there are a number of other advanced command shells available. The shell prints a text prompt, indicating it is ready to accept commands; after the user types the command and presses Enter, the command is executed, and another prompt is displayed after the command is done.

# Difference between forking and multithreading

A fork gives us a brand new process which is a copy of the current process with the same code segment. It looks exactly like the parent process with different process id having it's own memory. Parent process creates a separate address space for the child with same code segments but executes independently of each other. Because the system issues a new memory space and environment for the child process, it is knows as heavy-weight process.

While threads can execute in parallel with same context. Also, memory and other resources are shared between the threads causing less overhead. A thread process is considered a sibling while a forked process is considered a child. Also, threads are known as light-weight processes as they don't have any overhead as compared to processes (as it doesn't issue any separate command for creating completely new virtual address space). A single process can have multiple threads. For all threads of any process, communication between them is direct. While process needs some interprocess communication mechanism to talk to other processes. Thought, threads seem to be more useful for any reason, do note that changes in any thread may lead to changes in other threads of the same process. While, changes in child processes is independent as parent process has its own execution copy.

# Difference between BIOS and Kernel

