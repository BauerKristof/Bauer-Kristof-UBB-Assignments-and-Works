;Nev:Bauer Kristof
;Azonosotio:bkim1790
;Csoportszam:511

;Labor 1 / A Feladat / 1.

;A. feladat – aritmetikai kifejezés kiértékelése, „div” az egész osztás hányadosát, „mod” pedig a maradékát jelenti. 
;a, b, c, d, e, f, g előjeles egész számok, az io_readint függvénnyel olvassuk be őket ebben a sorrendben. Az eredményt az io_writeint eljárás segítségével írjuk ki.


%include 'io.inc' ;io filet includeolja

global main ;mindig meg kell legyen

section .text ;kodszegmens
main: 
	
	push eax
	push ebx
	push ecx
	push edx
	
	mov eax,str_kif
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
	call io_readint
     mov [g],eax ;[g]=d
	
	mov eax,str_e
	call io_writestr
	call io_readint
    mov [e],eax ;e=e
	
		mov eax,str_f
	call io_writestr
	call io_readint ;eax=f
	mov [f],eax ;[f]=f
	
	
	mov eax,str_g
	call io_writestr
	call io_readint ;eax=g
	xchg eax,[g] ;eax =d || [g]=g
	xchg eax,edx ;eax=a; ||edx=d;
	;elrendezve mindegyik
	
	push edx ;Verem: b
	push eax ;       a
	push ebx ;       d

	sub eax,edx ;a-d
	sub eax,ecx ; a-d-c
	add eax,ebx ; (a-d-c+b)

	mov ebx,[e] ; ebx=e
	add ebx,[g] ;ebx=(e+g)
	cdq ;elojel dx
	idiv ebx ;(a-d-c)/(e+g) AX>hanyados DX>maradek!!
	
	pop ebx ; ebx=b
	pop eax ; eax=a
	;verembe d
	
	sub eax,[e] ;a-e
	add eax,[f] ;a-e+f
	add ebx,ecx ;b+c
	pop ecx ;ecx=d
	push edx ; I muvelet bekerul a verembe
	cdq ;elojel allitas
	idiv ebx; (a-e+f)e div (b+c) eredmeny EAX!! ; maradek EDX
	push eax ; II muvelet verem tetejen
	
	mov eax,ecx ;eax=d
	add eax,[f] ;eax=d+f
	imul eax,2; eax=2*(d+f);
	cdq ;elojel allitas
	idiv ecx ;2*(d+f) div d ->Eredmeny EAX Maradek EDX
	add eax,[g] ;EAX= Harmadik muvelet
	
	pop ebx ;II muvelet ebx
	pop ecx ;I muvelet ecx
	
	sub ecx,ebx ; I muvelet - II muvelet
	add ecx, eax ; I muvelet - II muvelet + III muvelet 
	
	mov eax,str_eredmeny
	call io_writestr
	mov eax,ecx ; eaxbe bekerul a vegmuvelet
	call io_writeint ; kiir
	
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
str_e db 'E=',0
str_f db 'F=',0
str_g db 'G=',0
str_er db 'Eredmeny = ',0
str_kif db '1. ((a - d - c + b) mod (e + g)) - ((a - e + f) div (b + c)) + ((2 * (d + f)) div d + g)',0
str_eredmeny db'Eredmeny= ',0
    
section .bss ;adat szegmens

     e resd 1
	 f resd 1
	 g resd 1

	
	
	