section .data
    filename db "testfile",0
    prot equ PROT_READ | PROT_WRITE
    flags equ MAP_PRIVATE
    mode equ S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
    size equ 4096

section .text
global _start

_start:
    ; Open the file for reading and writing
    mov rax, 2          ; open syscall number
    mov rdi, filename
    mov rsi, O_RDWR
    mov rdx, mode
    syscall
    mov r9, rax         ; save file descriptor for later

    ; Map the file into memory
    mov rax, rsp
    and rsp, -4096      ; align stack to page boundary
    sub rsp, size       ; allocate space for mapped region
    mov rdi, 0          ; addr (NULL to let kernel choose)
    mov rsi, size       ; length (one page)
    mov rdx, prot       ; prot (read/write)
    mov rcx, flags      ; flags (private mapping)
    mov r8, r9          ; fd (file descriptor)
    mov r9, 0          ; offset (start at beginning of file)
    call mmap

    ; Read the first byte of the mapped region and print it out
    mov rbx, rax        ; save address of mapped region
    mov rax, [rbx]      ; read first byte
    movzx edi, byte [rax] ; zero-extend byte value to 32 bits
    mov eax, 4          ; write syscall number
    mov ebx, 1          ; stdout file descriptor
    mov ecx, rsp        ; address of byte value to write
    mov edx, 1          ; number of bytes to write
    syscall

    ; Unmap the memory region
    mov rax, 11         ; munmap syscall number
    mov rdi, rbx        ; addr
    mov rsi, size       ; length
    syscall

    ; Close the file
    mov rax, 3          ; close syscall number
    mov rdi, r9         ; fd
    syscall

    ; Exit the program
    mov eax, 60         ; exit syscall number
    xor edi, edi        ; return code 0
    syscall
