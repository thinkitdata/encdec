; mmap - map or unmap files or devices into memory
; int mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
;
; Parameters:
;   rdi - void *addr - the address of the memory region to map (NULL for kernel to choose)
;   rsi - size_t length - the length of the memory region to map
;   rdx - int prot - the memory protection flags
;   rcx - int flags - additional flags for the mapping
;   r8 - int fd - the file descriptor of the file to map
;   r9 - off_t offset - the offset in the file to start mapping from
;
; Returns:
;   rax - void * - the starting address of the mapped region, or MAP_FAILED (-1) on error

section .data
    MAP_FAILED equ -1

section .text
global mmap
mmap:
    ; Set up the arguments for the mmap system call
    mov rax, 9          ; mmap syscall number
    mov rdi, [rsp + 8]  ; addr
    mov rsi, [rsp + 16] ; length
    mov rdx, [rsp + 24] ; prot
    mov rcx, [rsp + 32] ; flags
    mov r8, [rsp + 40]  ; fd
    mov r9, [rsp + 48]  ; offset

    ; Make the mmap system call
    syscall

    ; Check for errors
    cmp rax, MAP_FAILED
    jne .mmap_done

    ; On error, set errno and return -1
    mov rax, -1
    mov rdi, errno
    mov rsi, rax
    syscall
    mov rax, MAP_FAILED
    ret

.mmap_done:
    ret
