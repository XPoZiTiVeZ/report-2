global f1, f2, f3

section .data
    two dq 2.0
    three dq 3.0

section .text
f1:
    push ebp
    mov ebp, esp

    finit

    fld qword[ebp + 8]
    fldl2e
    fmulp

    fld1
    fld st1
    fprem
    f2xm1
    faddp
    fscale

    fstp st1
    fadd qword[two]

    mov esp, ebp
    pop ebp
    ret

f2:
    push ebp
    mov ebp, esp

    finit

    fld1
    fld qword[ebp + 8]
    fdivp
    fchs

    mov esp, ebp
    pop ebp
    ret

f3:
    push ebp
    mov ebp, esp

    finit

    fld qword[ebp + 8]
    fld1
    faddp
    fmul qword[two]
    fdiv qword[three]
    fchs

    mov esp, ebp
    pop ebp
    ret

section .note.GNU-stack noalloc noexec nowrite progbits