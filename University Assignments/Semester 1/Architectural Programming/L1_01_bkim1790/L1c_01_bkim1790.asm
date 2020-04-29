;Nev:Bauer Kristof
;Azonosotio:bkim1790
;Csoportszam:511

;Labor 1 / C Feladat / 1.
;feltételes kifejezés

%include 'io.inc' ;io filet includeolja

global main ;mindig meg kell legyen

section .text ;kodszegmens
main: 
	
	push eax
	push ebx
	push ecx
	push edx
	
	mov eax,str_eset0
	call io_writestr
	call io_writeln
	
	mov eax,str_eset1
	call io_writestr
	call io_writeln

	
	mov eax,str_eset2
	call io_writestr
	call io_writeln

	
	mov eax,str_eset3
	call io_writestr	
	call io_writeln

	
	mov eax,str_eset4
	call io_writestr
	call io_writeln

	
	mov eax,str_a
	call io_writestr
    call io_readint
	mov edx,eax ;edx=a
	
	mov eax,str_b
	call io_writestr
	call io_readint
	mov ebx,eax ;ebx=b
	
	mov eax,str_c
	call io_writestr
	call io_readint
	mov  ecx,eax ;c=CX
	
	mov eax,str_d
	call io_writestr
	call io_readint;eax=d
	
	push edx ;a bekerul a verembe
	push ecx ;c bekerul a verem tetetejere
	mov ecx,5
	cdq ;elojel kiterjesztese edx-re
	idiv ecx ;EAX-hanyados EDX- maradek !!! (KERDES A TANARNONEK : IDIV,5 NEM LEHET?)
	
	pop ecx
	pop eax ;eax=a ||ebx=b|| ecx =c || edx = d mod 5
	
	cmp edx,0
	JE  F0 ;ha igaz ugrik a feltetel 0ra

	cmp edx,1
	JE F1
	
	cmp edx,2
	JE F2
	
	cmp edx,3
	JE F3
	
	cmp edx,4
	JE F4
	
	F0:
	add eax,ebx 
	sub eax,7
	mov ebx,eax
	mov eax,str_eset0
	call io_writestr
	call io_writeln
	mov eax,str_eredmeny
	call io_writestr 
	mov eax,ebx
	call io_writeint
	JMP V
	
	F1:
	imul ebx,2
	mov eax,15
	sub eax,ebx
	
	mov ebx,eax
	mov eax,str_eset1
	call io_writestr
	call io_writeln
		mov eax,str_eredmeny
	call io_writestr 
	mov eax,ebx
	
	call io_writeint
	JMP V
	
	F2:
	push eax
	imul eax,ecx
	pop ecx
	mov ecx, 3
	sub ecx,eax
	mov eax,ecx
	
	mov ebx,eax
	mov eax, str_eset2
	call io_writestr
	call io_writeln
		mov eax,str_eredmeny
	call io_writestr 
	mov eax,ebx
	
	call io_writeint
	JMP V
	
	F3:
    mov eax,ecx
	mov ebx,2
	cdq
	idiv ebx
	
	mov ebx,eax
	mov eax,str_eset3
	call io_writestr
	call io_writeln
		mov eax,str_eredmeny
	call io_writestr 
	mov eax,ebx
	
	call io_writeint
	JMP V
	
	F4:
	add eax,5
	sub eax,ebx
	
	mov ebx,eax
	mov eax,str_eset4
	call io_writestr
	call io_writeln
		mov eax,str_eredmeny
	call io_writestr 
	mov eax,ebx
	
	call io_writeint
	JMP V
	
	
	
	
	
	V:
	pop eax
	pop ebx
	pop ecx
	pop edx   
    ret
	
section .data
str_a db 'A=',0
str_b db 'B=',0
str_c db 'C=',0
str_d db 'D=',0
str_eset0 db 'ha d mod 5 = 0 : a + b - 7',0
str_eset1 db 'ha d mod 5 = 1 : 15 - (2 * b)',0
str_eset2 db 'ha d mod 5 = 2 : 3 - (a * c)',0
str_eset3 db 'ha d mod 5 = 3 : c div 2',0
str_eset4 db 'ha d mod 5 = 4 : a + 5 - b',0
str_eredmeny db 'Erdemeny=',0



    