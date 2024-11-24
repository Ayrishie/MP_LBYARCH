section .text
bits 64
default rel
global imgCvtGrayDoubleToInt
global debug_temp

section .bss
debug_temp resq 1    ; Temporary storage for debugging

section .data
scale_factor dq 255.0  ; Scale factor to convert 0.0–1.0 to 0–255

section .text

; Function: imgCvtGrayDoubleToInt
imgCvtGrayDoubleToInt:
    push rbp
    mov rbp, rsp

    ; Load parameters
    mov rdi, rcx        ; output array
    mov rsi, rdx        ; input array
    mov r8d, r8d        ; width
    mov r9d, r9d        ; height

    xor r10d, r10d      ; row index = 0

row_loop:
    xor r11d, r11d      ; column index = 0

col_loop:
    ; Calculate index: index = row * width + column
    mov eax, r10d
    imul eax, r8d
    add eax, r11d

    ; Load double-precision value from input
    movq xmm0, qword [rsi + rax * 8]  ; Load input[i] (double)

    ; Multiply by 255.0 and convert to integer
    movsd xmm1, qword [scale_factor]  ; Load scale factor (255.0)
    mulsd xmm0, xmm1                  ; input[i] * 255.0
    movq qword [debug_temp], xmm0     ; Store scaled value in debug_temp

    ; Convert to integer
    cvttsd2si eax, xmm0               ; Truncate to integer

    ; Clamp value to 0–255
    cmp eax, 0
    jl clamp_to_zero
    cmp eax, 255
    jg clamp_to_255
    jmp store_value

clamp_to_zero:
    mov eax, 0
    jmp store_value

clamp_to_255:
    mov eax, 255

store_value:
    ; Store the result in the output array
    mov byte [rdi + rax], al          ; Corrected: Store at the correct offset based on index
    mov byte [rdi + rax], al          ; Proper indexing for storage in output

    ; Increment column index
    inc r11d
    cmp r11d, r8d              ; Compare column index with width
    jl col_loop

    ; Increment row index
    inc r10d
    cmp r10d, r9d              ; Compare row index with height
    jl row_loop

    ; Clean up and return
    pop rbp
    ret
