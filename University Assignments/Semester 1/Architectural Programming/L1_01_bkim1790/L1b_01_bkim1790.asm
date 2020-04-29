;Nev:Bauer Kristof
;Azonosotio:bkim1790
;Csoportszam:511

;Labor 1 / B Feladat / 1.

;bitenkénti logikai műveletek
;Írassuk ki a kiértékelendő kifejezést, olvassuk be az a, b, c, d értékeket az io_readint függvény segítségével, majd írassuk ki a beolvasott értékeket 
;és az eredményt egymás alá bináris formában az io_writebin függvény segítségével.


%include 'io.inc' ;io filet includeolja


global main ;mindig meg kell legyen

section .text ;kodszegmens
main: 
	
	push eax
	push ebx
	push ecx
	push edx
	
	mov eax,str_muv
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
	xchg eax,edx ; eax=a | edx=d
	
	push eax ;eax verembe
	mov eax,str_a
	call io_writestr
	pop eax
	call io_writebin ;eax kiiratva binarisan
	call io_writeln
	
	xchg eax,ebx; ;ebx=eax
	push eax
	mov eax,str_b
	call io_writestr
	pop eax
	call io_writebin ;ebx kiiratva binarisan
	call io_writeln
	
	xchg eax,ecx ;ecx = ebx
	push eax
	mov eax,str_c
	call io_writestr
	pop eax
	call io_writebin ;ecx kiiratva binarisan
	call io_writeln
	
	xchg eax,edx ;edx=ecx
	push eax
	mov eax,str_d
	call io_writestr
	pop eax
	call io_writebin ;edx kiiratva binarisan
	call io_writeln
	
	xchg eax,ebx ; eax=a || ebx=d
	xchg ebx,ecx ;ebx =b || ecx=d
	xchg ecx,edx ;rendezve mind
	
	not ecx ;negaljuk c-t
	push eax;
	
	and eax,edx ;(a and d)
    xor eax,ecx ;(a and d) xor (not c)
    pop ecx; ;ecx=a
    and ecx,ebx ;ecx =(a and b)	
    or eax,ecx ;muvelet elvegzese
	mov ebx, eax ;atrakjuk hogy irassuk ki az E=
	mov eax,str_e
	call io_writestr
	mov eax,ebx ;visszarakjuk az eax-et
	call io_writebin
	
	
	
	
	
	
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
str_muv db'(a AND b) OR ((a AND d) XOR (NOT c))',0
str_e db 'E=',0
    