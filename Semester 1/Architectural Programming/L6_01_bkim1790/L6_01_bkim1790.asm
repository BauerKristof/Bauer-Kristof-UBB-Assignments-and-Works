;Nev:Bauer Kristof
;Azonostio:bkim1790
;Csoportszam 511
;Labor 6 / 1. feladat
;1. E(a,b) = sqrt(a + b / 3) + (b - 2) * (b - a)


%include 'io.inc'

global main

section .text

beolvasa:

xor ebx,ebx

	.aciklus:
	cmp ebx,ecx
	jge .aciklusvege
 
	mov eax,belem
	call io_writestr
	call io_readflt
	call io_writeln
	movss[a+ebx*4],xmm0
	inc ebx
	jmp .aciklus

 .aciklusvege:
  ret
  
beolvasb:
	  xor ebx,ebx

	.bciklus:
	cmp ebx,ecx
	jge .bciklusvege
	
	mov eax,belem
	call io_writestr
	call io_readflt
	call io_writeln
	movss[b+ebx*4],xmm0
	inc ebx
	jmp .bciklus
	
	.bciklusvege:
	ret

felepit:
	xor ebx,ebx

	.cciklus:
		cmp ebx,ecx
		jge .cciklusvege
		
		movaps xmm0,[a+4*ebx]
		movaps xmm1,[b+4*ebx]
		
		
		;----muveletek
		xorps xmm2,xmm2
		movaps xmm2,xmm1
		divps xmm2,[harom] ;b/3
		addps xmm2,xmm0 ; (a+b/3)
		sqrtps xmm3,xmm2 ;sqrt(a+b/3) ;XMM3-ban van az elso muvelet
		
		xorps xmm2,xmm2
		movaps xmm2,xmm1
		subps xmm2,[ketto] ;xmm2-be van a (b-2)
		
		subps xmm1,xmm0 ;xmm1-be van a b-a
		mulps xmm2,xmm1 ;(b-2)*(b-a)
		addps xmm3,xmm2 ;sqrt(a+ b/3) + (b-2)*(b-a)
		
		movaps [c+4*ebx],xmm3
		add ebx,4
		jmp .cciklus
	
		.cciklusvege:
		ret
kiir:
		xor ebx,ebx
		mov edi,c
            .kiirciklus:
			cmp ebx,ecx
			jge .kiirciklusvege
			movss xmm0,[edi+4*ebx]
			mov eax,eredmeny
			call io_writestr
			call io_writeflt
			call io_writeln
			inc ebx
			jmp .kiirciklus
			
			.kiirciklusvege:
			ret

main:
 xor ebx,ebx
 xor ecx,ecx
 xor edx,edx
 
 mov eax,feladat
 call io_writestr
 call io_writeln
 
 mov eax,bedec
 call io_writestr
 xor eax,eax
 call io_readint ;tomb hosszanak bekerese

 
  cmp eax,4			;ha kissebb mint 4 hibas
  jl .hiba
  cmp eax,256		;hogy nagyobb mint 256 hibas
  jge .hiba
  mov ebx,4 ;ha nem oszthato 4-el hiba
  mov ecx, eax
  cdq		
  idiv ebx
  cmp edx,0	
  jne .hiba
 

 mov eax,bea
 call io_writestr
 call io_writeln
 call beolvasa
 call io_writeln
 
 mov eax,beb
 call io_writestr
 call io_writeln
 call beolvasb
 call io_writeln
 
 mov eax,bec
 call io_writestr
 call io_writeln
 call felepit
 call kiir
 ret
 
 .hiba:
 mov eax,hiba
 call io_writestr
 ret

section .bss
a resd 256
b resd 256
c resd 256

	
section .data
	harom dd 3.0, 3.0, 3.0, 3.0
	ketto dd 2.0, 2.0, 2.0, 2.0
	feladat db "E(a,b) = sqrt(a + b / 3) + (b - 2) * (b - a)",0
    bedec db "Add meg a tombok hosszat:", 0
	bea db "--Az A tomb beolvasasa--",0
	beb db "--A B tomb beolvasasa--",0
	bec db "-Az eredmenytomb--",0
	eredmeny db "Az elem = ",0
	belem db "Add meg az elemet: ",0
	hiba db "Rossz erteket adtal meg. A tomb hossza 4 es 256 kozott kell legyen es oszthato kell legyen 4-el. Probald ujra",0