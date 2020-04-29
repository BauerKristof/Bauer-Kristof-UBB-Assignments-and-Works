;Nev:Bauer Kristof
;Azonostio:bkim1790
;Csoportszam 511
;Labor 3 | B feladat - 1es
;B Feldat/1.: A[29:20] OR C[23:14], C[4:3] XOR 10, B[31:17] + C[23:9], B[30:29] OR A[1:0], 001 AND A[12:10]



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
	
muveletsorozat:
	push eax
	push ebx
	push ecx
	clc
	
	xor eax,eax
	xor ebx,ebx
	xor ecx,ecx
	xor edx,edx
	
	
	; A[29:20] OR C[23:14]
	mov eax,[a]
	shr eax,20
	and eax,1111111111b
	
	mov ecx,[c]
	shr ecx,14
	and ecx,1111111111b
	
	or eax,ecx
	add edx,eax
	shl edx,2
	
	;C[4:3] XOR 10
	mov ecx,[c]
	shr ecx,3
	and ecx,11b
	
	mov ebx,10b
	and ebx,11b
	
	xor ecx,ebx
	add edx,ecx
	shl edx,15
	
	;B[31:17] + C[23:9]
	mov ebx,[b]
	shr ebx,17
	and ebx, 111111111111111b
	
	mov ecx,[c]
	shr ecx,9
	and ecx,111111111111111b
	
	add ebx,ecx
	and ebx,111111111111111b

	add edx,ebx
	shl edx,2
	
	;B[30:29] OR A[1:0]
	mov ebx,[b]
	shr ebx,29
	and ebx,11b
	
	mov eax,[a]
	and eax,11b
	
	or ebx,eax
	add edx,ebx
	shl edx,3
	
	;001 AND A[12:10]
	mov eax,[a]
	shr eax,10
	and eax,111b
	mov ebx,001b
	and ebx,111b
	and eax,ebx
	add edx,eax
	

	
	
	.vege:
	pop ecx
	pop ebx
	pop eax
	ret

	


main:

	xor eax,eax
	xor ebx,ebx
	xor ecx,ecx
	xor edx,edx
	
	mov eax,kiirfel
	call mio_writestr ;KIIRFELSZOVEG
	call mio_writeln
	
	mov eax,kiirbina
	call mio_writestr
	call beolvashex ;eaxbe bekerult az ertek
	jc .hiba
	mov [a], eax ;beolvas A szamot
	
	
	;elso szam a cimen
	call mio_writeln
	mov eax,kiirbinb
	call mio_writestr
	call beolvashex ;eaxbe bekerult az ertek
	jc .hiba	
	mov [b], eax ;beolvas B szam
	
	
	call mio_writeln
	mov eax,kiirbinc
	call mio_writestr
	call beolvashex ;eaxbe bekerult az ertek
	jc .hiba	
	mov [c], eax ;BEOLVAS C SZAM
	
	call mio_writeln
	mov eax,kiirbina
	call mio_writestr
	mov eax,[a]
	call kiirbinarisan ;kiirbinA
	
	call mio_writeln
	mov eax,kiirbinb
	call mio_writestr
	mov eax,[b]
	call kiirbinarisan ;masodik szam b cimen
	
	call mio_writeln
	mov eax,kiirbinc
	call mio_writestr
	mov eax,[c]
	call kiirbinarisan ;c cimen harmadik szam

	call muveletsorozat
	call mio_writeln
	mov eax,kiireredmeny
	call mio_writestr
	xor eax,eax
	mov eax,edx
	call kiirbinarisan
	ret	
	


.hiba:
	call mio_writeln
	mov eax, hibas
    call mio_writestr
	call mio_writeln
	ret
	
section .bss	
a resb 32 ;A szamnak helyet foglalok a memoriaban
b resb 32 ;B szamnak -||-
c resb 32 ;C szamnak -||-
	
	
section .data
 kiirbina db "A= ",0
 kiirbinb db "B= ",0
 kiirbinc db "C= ",0
 kiirfel db "A[29:20] OR C[23:14], C[4:3] XOR 10, B[31:17] + C[23:9], B[30:29] OR A[1:0], 001 AND A[12:10]",0
 hibas db "Hiba: Rossz erteket adtal meg",0
 kiireredmeny db "EREDMENY= ",0