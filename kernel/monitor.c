/*
 * Copyright (c) 2020 Institute of Parallel And Distributed Systems (IPADS), Shanghai Jiao Tong University (SJTU)
 * OS-Lab-2020 (i.e., ChCore) is licensed under the Mulan PSL v1.
 * You can use this software according to the terms and conditions of the Mulan PSL v1.
 * You may obtain a copy of Mulan PSL v1 at:
 *   http://license.coscl.org.cn/MulanPSL
 *   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
 *   PURPOSE.
 *   See the Mulan PSL v1 for more details.
 */

// Simple command-line kernel monitor useful for
// controlling the kernel and exploring the system interactively.

#include <common/printk.h>
#include <common/types.h>

static inline __attribute__ ((always_inline))
u64 read_fp()
{
	u64 fp;
	__asm __volatile("mov %0, x29":"=r"(fp));
	return fp;
}

__attribute__ ((optimize("O1")))
int stack_backtrace()
{
	printk("Stack backtrace:\n");

	// Your code here.
    u64 *old_fptr = (u64 *)read_fp();
    u64 *new_fptr = (u64 *)*old_fptr;

    while (*new_fptr) {
        printk("  LR %llx   FP %llx  ", *(new_fptr+1), new_fptr);
        printk("Args %llx %llx %llx %llx %llx\n", *(old_fptr+2), *(old_fptr+3), *(old_fptr+4), *(old_fptr+5), *(old_fptr+6) );
        old_fptr = new_fptr;
        new_fptr = (u64 *)*new_fptr;
    }

	return 0;
}
