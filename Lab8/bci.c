/*
 * CS 11, C track, lab 8
 *
 * FILE: bci.c
 *       Implementation of the bytecode interpreter.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bci.h"


/* Define the virtual machine. */
vm_type vm;


/* Initialize the virtual machine. */
void init_vm(void)
{
    int i;

    /*
     * Initialize the stack.  It grows to the right i.e.
     * to higher memory.
     */

    vm.sp = 0;

    for (i = 0; i < STACK_SIZE; i++)
    {
        vm.stack[i] = 0;
    }

    /*
     * Initialize the registers to all zeroes.
     */

    for (i = 0; i < NREGS; i++)
    {
        vm.reg[i] = 0;
    }

    /*
     * Initialize the instruction buffer to all zeroes.
     */

    for (i = 0; i < MAX_INSTS; i++)
    {
        vm.inst[i] = 0;
    }

    vm.ip = 0;
}


/*
 * Helper function to read in integer values which take up varying
 * numbers of bytes from the instruction array 'vm.inst'.
 *
 * NOTES:
 * 1) This function moves 'vm.ip' past the integer's location
 *    in memory.
 * 2) This function assumes that integers take up 4 bytes and are
 *    arranged in a little-endian order (low-order bytes at the
 *    beginning).  This should hold for any pentium-based microprocessor.
 * 3) This function only works for n = 1, 2, or 4 bytes.
 *
 */

int read_n_byte_integer(int n)
{
    int i;
    unsigned char *val_ptr;
    int val = 0;

    /* This only works for 1, 2, or 4 byte integers. */
    assert((n == 1) || (n == 2) || (n == 4));

    val_ptr = (unsigned char *)(&val);

    for (i = 0; i < n; i++)
    {
        *val_ptr = vm.inst[vm.ip];
        val_ptr++;
        vm.ip++;
    }

    return val;
}


/*
 * Machine operations.
 */

void do_push(int n)
{
    vm.sp++;
    vm.stack[vm.sp] = n;
}

void do_pop(void)
{
    vm.sp--;
}

void do_load(int n)
{
    do_push(vm.reg[n]);
}

void do_store(int n)
{
    vm.reg[n] = vm.stack[vm.sp];
    do_pop();
}

void do_jmp(int n)
{
    vm.ip = n;
}

void do_jz(int n)
{
    if (vm.stack[vm.sp] == 0)
    {
        do_jmp(n);
    }
    do_pop();
}

void do_jnz(int n)
{
    if (vm.stack[vm.sp] != 0)
    {
        do_jmp(n);
    }
    do_pop();
}

void do_add(void)
{
    int sum;
    sum = vm.stack[vm.sp] + vm.stack[vm.sp - 1];
    vm.sp--;
    vm.stack[vm.sp] = sum;
}

void do_sub(void)
{
    int diff;
    diff = vm.stack[vm.sp - 1] - vm.stack[vm.sp];
    vm.sp--;
    vm.stack[vm.sp] = diff;
}

void do_mul(void)
{
    int prod;
    prod = vm.stack[vm.sp] * vm.stack[vm.sp - 1];
    vm.sp--;
    vm.stack[vm.sp] = prod;
}

void do_div(void)
{
    int quot;
    quot = vm.stack[vm.sp - 1] / vm.stack[vm.sp];
    vm.sp--;
    vm.stack[vm.sp] = quot;
}

void do_print(void)
{
    printf("%d\n", vm.stack[vm.sp]);
    do_pop();
}


/*
 * Stored program execution.
 */

/* Load the stored program into the VM. */
void load_program(FILE *fp)
{
    int nread;
    unsigned char *inst = vm.inst;

    do
    {
        /*
         * Read a single byte at a time and load it into the
         * 'vm.insts' array.  'fread' returns the number of bytes read,
         * or 0 if EOF is hit.
         */

        nread = fread(inst, 1, 1, fp);
        inst++;
    }
    while (nread > 0);
}



/* Execute the stored program in the VM. */
void execute_program(void)
{
    int val;

    vm.ip = 0;
    vm.sp = 0;

    while (1)
    {
        /*
         * Read each instruction and select what to do based on the
         * instruction.  For each instruction you may also have to
         * read in some number of bytes as the arguments to the
         * instruction.
         */

        switch (vm.inst[vm.ip])
        {
        case NOP:
            /* Skip to the next instruction. */
            vm.ip++;
            break;

        case PUSH:
            vm.ip++;

            /* Read in the next 4 bytes. */
            val = read_n_byte_integer(4);
            do_push(val);
            break;

        case POP:
            vm.ip++;

            /* We do not need to read, as there is no value required for
             * do_pop();
             */
            do_pop();
            break;

        case LOAD:
            vm.ip++;

            /* Read in the next byte. */
            val = read_n_byte_integer(1);
            do_load(val);
            break;

        case STORE:
            vm.ip++;

            /* Read in the next byte. */
            val = read_n_byte_integer(1);
            do_store(val);
            break;

        case JMP:
            vm.ip++;

            /* Read in the next two bytes. */
            val = read_n_byte_integer(2);
            do_jmp(val);
            break;

        case JZ:
            vm.ip++;

            /* Read in the next two bytes. */
            val = read_n_byte_integer(2);
            do_jz(val);
            break;

        case JNZ:
            vm.ip++;

            /* Read in the next two bytes. */
            val = read_n_byte_integer(2);
            do_jnz(val);
            break;

        case ADD:
            vm.ip++;

            /* We do not need to read, as there is no value required for
             * do_add();
             */
            do_add();
            break;

        case SUB:
            vm.ip++;

            /* We do not need to read, as there is no value required for
             * do_sub();
             */
            do_sub();
            break;

        case MUL:
            vm.ip++;

            /* We do not need to read, as there is no value required for
             * do_mul();
             */
            do_mul();
            break;

        case DIV:
            vm.ip++;

            /* We do not need to read, as there is no value required for
             * do_div();
             */
            do_div();
            break;

        case PRINT:
            vm.ip++;

            /* We do not need to read, as there is no value required for
             * do_pop();
             */
            do_print();
            break;

        case STOP:
            return;

        default:
            fprintf(stderr, "execute_program: invalid instruction: %x\n",
                    vm.inst[vm.ip]);
            fprintf(stderr, "\taborting program!\n");
            return;
        }
    }
}


/* Run the program given the file name in which it's stored. */
void run_program(char *filename)
{
    FILE *fp;

    /* Open the file containing the bytecode. */
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "bci.c: run_program: "
               "error opening file %s; aborting.\n", filename);
        exit(1);
    }

    /* Initialize the virtual machine. */
    init_vm();

    /* Read the bytecode into the instruction buffer. */
    load_program(fp);

    /* Execute the program. */
    execute_program();

    /* Clean up. */
    fclose(fp);
}

