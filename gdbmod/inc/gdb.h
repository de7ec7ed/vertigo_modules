/* This file is part of VERTIGO.
 *
 * (C) Copyright 2013, Siege Technologies <http://www.siegetechnologies.com>
 * (C) Copyright 2013, Kirk Swidowski <http://www.swidowski.com>
 *
 * VERTIGO is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * VERTIGO is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with VERTIGO. If not, see <http://www.gnu.org/licenses/>.
 *
 * Written by Kirk Swidowski <kirk@swidowski.com>
 */

#ifndef __GDBMOD_MAIN_H__
#define __GDBMOD_MAIN_H__

#define GDB_COMMAND_SIZE     1024
#define GDB_RESPONSE_SIZE    1024
#define GDB_COMMAND_INTERVAL 4096

#define GDB_ESCAPE_CHARACTER 0x7D

// gdb signal values
#define GDB_SIGHUP           1
#define GDB_SIGINT           2
#define GDB_SIGQUIT          3
#define GDB_SIGILL           4
#define GDB_SIGTRAP          5
#define GDB_SIGABRT          6
#define GDB_SIGIOT           6
#define GDB_SIGBUS           7
#define GDB_SIGFPE           8
#define GDB_SIGKILL          9
#define GDB_SIGUSR1         10
#define GDB_SIGSEGV         11
#define GDB_SIGUSR2         12
#define GDB_SIGPIPE         13
#define GDB_SIGALRM         14
#define GDB_SIGTERM         15
#define GDB_SIGSTKFLT       16
#define GDB_SIGCHLD         17
#define GDB_SIGCONT         18
#define GDB_SIGSTOP         19
#define GDB_SIGTSTP         20
#define GDB_SIGTTIN         21
#define GDB_SIGTTOU         22
#define GDB_SIGURG          23
#define GDB_SIGXCPU         24
#define GDB_SIGXFSZ         25
#define GDB_SIGVTALRM       26
#define GDB_SIGPROF         27
#define GDB_SIGWINCH        28
#define GDB_SIGIO           29

#ifdef __C__

extern result_t gdb_interrupt_handler(vec_handler_t *handler, bool_t *handled, gen_general_purpose_registers_t *registers);

#endif //__C__

#ifdef __ASSEMBLY__

#endif //__ASSEMBLY__

#endif //__GDBMOD_MAIN_H__
