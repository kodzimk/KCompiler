global _start
_start:
    mov rax, 2
    push rax
    mov rax, 1
    push rax
    pop rax
    pop rbx
    div rbx
    push rax
    mov rax, 4
    push rax
    mov rax, 5
    push rax
    pop rax
    pop rbx
    mul rbx
    push rax
    pop rax
    pop rbx
    add rax, rbx
    push rax
    mov rax, 8
    push rax
    mov rax, 1
    push rax
    pop rax
    test rax, rax
    jz label0
    mov rax, 69
    push rax
    mov rax, 60
    pop rdi
    syscall
    add rsp, 0
label0:
    mov rax, 1
    push rax
    pop rax
    test rax, rax
    jz label2
    mov rax, 68
    push rax
    mov rax, 60
    pop rdi
    syscall
    add rsp, 0
    jmp label1
label2:
    mov rax, 67
    push rax
    mov rax, 60
    pop rdi
    syscall
    add rsp, 0
label1:
    push QWORD [rsp + 8]
    mov rax, 60
    pop rdi
    syscall
    mov rax, 60
    mov rdi, 0
    syscall
