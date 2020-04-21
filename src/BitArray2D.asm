
        global  set_bit_elem
        global  get_bit_elem
        section .text

set_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col

        ; add your code here
        ;mov rax, rdx        ; moves row to rax register
        ;imul rax, rsi       ; multiplies row and rowwidth
        ;add rax, rcx        ; adds col to row * rowwidth
        ;mov rbx, rax        ; move value to new rbx register
        ;sal rax, 4          ; left shift by 4
        ;add rax, rdi        ; add array base pointer
        ;mov rax, [rax]      ; read stored value
        ;mov rdx, 1
        ;mov rax, rdx
        ;mov rax, 1


        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax




get_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col

        ; add your code here - for now returning 0
        ; mov rax, 0

        ;mov rax, rdx        ; moves row to rax register
        ;imul rax, rsi       ; multiplies row and rowwidth
        ;add rax, rcx        ; adds col to row * rowwidth
        ;mov rcx, rax        ; move value to rcx register

        setl al

        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax
