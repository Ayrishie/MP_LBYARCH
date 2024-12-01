section .data
scale_factor dq 255.0  ; Scale factor for grayscale conversion

section .text
bits 64
default rel
global imgCvtGrayDoubleToInt

imgCvtGrayDoubleToInt:
    push rbp
    mov rbp, rsp

    ; Parameters:
    ; RCX = output, RDX = input, R8D = width, R9D = height
    ; Stack +16 = height (if additional parameter needed)
    
    ; Load parameters
    mov rdi, rcx          ; output
    mov rsi, rdx          ; input
    mov ecx, r8d          ; width
    mov edx, r9d          ; height

    xor r8d, r8d          ; row index = 0
row_loop:
    xor r9d, r9d          ; column index = 0
col_loop:
    ; Calculate index: index = (row * width) + column
    mov eax, r8d          ; row index
    imul eax, ecx         ; row * width
    add eax, r9d          ; row * width + column
    mov r10, rax          ; save index

    ; Load input value
    movsd xmm0, qword [rsi + r10 * 8] ; Load input[index] (double)
    movsd xmm1, qword [scale_factor]  ; Load scale factor (255)
    mulsd xmm0, xmm1                  ; xmm0 = input[index] * 255
    cvttsd2si eax, xmm0               ; Convert to integer (truncated) 

    ; Clamp to [0, 255]
    cmp eax, 0                        ; Compare eax with 0
    jge skip_clamp_to_zero            ; Jump if >= to 0
    xor eax, eax                      ; Clamp to 0
skip_clamp_to_zero:
    cmp eax, 255                      ; Check if > 255
    jle skip_clamp_to_max             ; Skip if <= 255
    mov eax, 255                      ; Clamp to 255
skip_clamp_to_max:

    ; Store result in output
    mov byte [rdi + r10], al          ; output[index] = clamped_value

    ; Next column
    inc r9d
    cmp r9d, ecx                      ; Compare column index with width
    jl col_loop

    ; Next row
    inc r8d
    cmp r8d, edx                      ; Compare row index with height
    jl row_loop

   
    pop rbp
    ret
