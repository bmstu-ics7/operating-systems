.386p
descr struc
	limit 	dw 0
	base_l 	dw 0
	base_m 	db 0
	attr_1 	db 0
	arrt_2 	db 0
	base_h 	db 0
descr ends

data segment
	gdt_null descr <0,0,0,0,0,0>
	gdt_data descr <data_size-1,0,0,92h,0,0>
	gdt_code descr <code_size-1,0,0,98h,0,0>
	gdt_stack descr <255,0,0,92h,0,0>
	gdt_screen descr <4095,8000h,0Bh,92h,0,0>
	gdt_size=$-gdt_null

	pdescr dq 0
	attr db 1Eh
	real_message db "real$"
	protect_message db "protect$"
	data_size=$-gdt_null
data ends

text segment 'code' use16
	assume CS:text, DS:data

main proc
		xor EAX,EAX
		mov AX,data
		mov DS,AX
		shl EAX,4
		mov EBP,EAX

		mov EBX,offset gdt_data
		mov [BX].base_l,AX
		rol EAX,16
		mov [BX].base_m,AL

		xor EAX,EAX
		mov AX,CS
		shl EAX,4
		mov EBX,offset gdt_code
		mov [BX].base_l,AX
		rol EAX,16
		mov [BX].base_m,AL

		mov dword ptr pdescr+2,EBP
		mov word ptr pdescr,gdt_size-1
		lgdt pdescr

		cli
		mov AL,80h
		out 70h,AL

		mov EAX,CR0
		or EAX,1
		mov CR0,EAX

		db 0EAh
		dw offset continue
		dw 16

continue:
		mov AX,8
		mov DS,AX

		mov AX,24
		mov SS,AX

		mov AX,32
		mov ES,AX
		mov BX,3000
		mov CX,7
		mov SI,0

screen:
		mov EAX,word ptr protect_message[SI]
		mov ES:[BX],EAX
		add BX,2
		inc SI
		loop screen

		mov AX,8
		mov DS,AX
		mov AX,24
		mov SS,AX
		mov AX,32
		mov ES,AX

		db 0EAh
		dw offset go
		dw 16

go:
		mov EAX,CR0
		and EAX,0FFFFFFFEh
		mov CR0,EAX
		db 0EAh
		dw offset return
		dw text

return:
		mov AX,data
		mov DS,AX
		mov AX,stk
		mov SS,AX

		sti
		mov AL,0
		out 70h,AL

		mov AH,09h
		mov EDX,offset real_message
		int 21h
		mov AX,4C00h
		int 21h
		main endp

		code_size=$-main
text ends

stk segment stack 'stack'
		db 256 dup ('^')
stk ends

end main
