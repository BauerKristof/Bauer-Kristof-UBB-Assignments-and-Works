;Nev:Bauer Kristof
;Azonostio:bkim1790
;Csoportszam 511
;Labor 3 | A feladat
;A. feladat – bináris szám írása


%include 'mio.inc'

global main

section .text




beolvashex:
push eax 
push edx 
push ebx 
	
	xor eax,eax
	xor edx,edx
	xor ebx,ebx
  		
	jmp .beolvas		
				
			.beolvas: ;beolvas karakter->szam(edx)
				call mio_readchar
				jmp .ellenoriz
				
			.ellenoriz:
				cmp al,13 ;megnezi hogy enter-e
				je .kiirvege
				cmp al,'0' ;kissebb mint 0
				jl .hiba
				cmp al,'9' ;ha 9-0 kozott van
				jle .szam
				cmp al,'9' ;ha betu
				jg .betu
				
				jmp .beolvas
				
			.hiba:
				stc ;beallit carryflag
				pop ebx 
				pop edx
				pop edi ;edi=eax-eel
				ret
			
				
			.szam:	
				call mio_writechar ;kiir szam
				sub eax,'0'
				shl ebx,4 ;eltolassal hatvanyoljuk a szamot
				add ebx,eax
				jmp .beolvas ;ujrahiv a kov szamjegyre
				
			.betu:
			cmp al,'A' ;9esA kozotti karakterek hibasak
			jl .hiba
			cmp al,'F' ;A->F
			jle .atalakit
			cmp al,'a' ;F->a kozotti szimbolumokra hiba
			jl .hiba
			cmp al,'f'
			jle .kisbetu
			
			jmp .hiba ;ha egyik casebe se ment bele azt jelenti f-nel nagyobb az meg hibas
				
			.atalakit: ;nagybetut szamma alakit
			call mio_writechar
			sub eax,'A'
			add eax,10
			shl ebx,4
			add ebx,eax
			jmp .beolvas ;ujrahiv a kov szamjegyre
			
			
			.kisbetu: ;kisbetut szamma alakit
			call mio_writechar
			sub eax,'a'
			add eax,10
			shl ebx,4
			add ebx,eax
			jmp .beolvas ;ujrahiv a kov szamjegyre
				
	
				
			.kiirvege:
				mov eax,ebx
				pop ebx
				pop edx
				pop edi
				clc
				ret
				
				
kiirbinarisan:

	push eax
	push ebx
	push ecx
	push edx
	clc
	
	mov ecx,32
	mov ebx,eax
	xor edx,edx
	
		.space:
	xor edx,edx
	mov eax,32 ;kiir space es nullazza a szamlalot
	call mio_writechar
	
	
	.ciklus:
	add edx,1 
	cmp edx,5 ;nezi hogy minden otodik elemnel space legyen
	je .space ;ha spcae
	xor eax,eax	;lenullaz eax
	rcl ebx,1 ;eltolja ebx-et
	adc eax,'0' ;hozzaadja eax-hez a carryt
	call mio_writechar ;kiirja
	loop .ciklus

	.vege:
	pop edx
	pop ecx
	pop ebx
	pop eax
	ret
	

	
	loop .ciklus
	


main:

	xor eax,eax
	xor ebx,ebx
	xor ecx,ecx
	xor edx,edx
	
	
	mov eax,behex
	call mio_writestr
	call beolvashex ;eaxbe bekerult az ertek
	mov ecx, eax
	jc .hiba	
	
	call mio_writeln
	mov eax,kiirbin
	call mio_writestr
	mov eax,ecx
	call kiirbinarisan
	
	
	;elso szam ecx-ben'
	call mio_writeln
	mov eax,behex
	call mio_writestr
	call beolvashex ;eaxbe bekerult az ertek
	mov ebx, eax
	jc .hiba	
	
	call mio_writeln
	mov eax,kiirbin
	call mio_writestr
	mov eax,ebx
	call kiirbinarisan
	;masodik szam ebx-ben
	
	call mio_writeln	
	add ebx,ecx ;osszead
	mov eax,kiirbinosszeg
	call mio_writestr
	mov eax,ebx
	call kiirbinarisan
	
	
	ret	
	


.hiba:
	call mio_writeln
	mov eax, hibas
    call mio_writestr
	call mio_writeln
	ret
	
section .data
 kiirbin db "A szam binarisan = ",0
 kiirbinosszeg db "A ket szam osszege binarisban = ",0
 behex db "Add meg a hex szamot: 0x",0
 hibas db "Hiba: Rossz erteket adtal meg",0

	