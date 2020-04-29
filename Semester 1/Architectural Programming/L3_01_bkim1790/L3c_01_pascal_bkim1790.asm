;Nev:Bauer Kristof
;Azonostio:bkim1790
;Csoportszam 511
;Labor 3 | C feladat /3as (PASCAL) / 01 Alpont
;C Feldat/01.:[minden betű az A-ból, ami nincs benne a B-ben (külön számít a kis- és nagybetű)] + [azok a számjegyek a B-ből, amelyek előtt kisbetű van]

%include 'mio.inc'

global main

section .text

beolvasstring:
 push eax
 push ecx
 push edi
 
 mov ecx,eax
 mov edi,eax
 inc edi
 
 .ciklus:
 call mio_readchar
 call mio_writechar
 cmp al,13
 je .vege
 stosb ;berakja al-t az edi cimre || edi++
 jmp .ciklus
 
 
  .vege:
   dec edi ;+1 karakter
   sub edi,ecx ;megkapjuk a hosszt
 mov eax,edi ;eax hosszt
 mov [ecx], al ;string elejere bekerul 
 mov eax,10 ;carriage return
 call mio_writechar 
 pop edi
 pop ecx
 pop eax
 ret
 
 
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 kiir:
 push eax
 push ecx
 push esi
 
 
 mov esi,eax ;esibe berakja a cimet
 movzx ecx,byte[esi] ;ecx string elso cime (hossz)
 inc esi
 
 test ecx, ecx
 jz .vege
 
 .ciklus:
	lodsb ;karakter al || esi++
	call mio_writechar
	loop .ciklus ;csokkenti a hosszt ecx

.vege:

pop esi
pop ecx
pop eax
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	
szamjegyek:
	pusha
	
	;EBX-BEN A SZAM
	;CL-ben a hossza
	;EDI-be ujstring
	
	
	xor edx,edx ;leptetes
	;mov esi,[ebx] ;esi B hossza
	;movzx ecx,byte[ebx] ;CL-ben EBX HOSSZA
	xor ecx,ecx
	mov cl,[ebx]
	mov edi,s4 ;EDI-be s4
	
	inc ebx ;noveljuk az elso ertekre
	inc edi ;az uj stringet noveljuk eggyel
	
	.ciklus:
	
	cmp dl,cl ;megnezi hogy a DL nem haladta-e meg a string hosszat
	jge .vege ;ha igen kilep
	mov al,[ebx] ;al-be bekerul az ebx karaktere
	cmp al,'a' ;osszehasonlitja al-t 'a'-val
	jge .betu ;ha betu
	jmp .leptet
		
	.betu:
	cmp al,'z' ;ha kisbetu
	jle .kisbetu ;a karakter az kisbetu	
	jmp .leptet
	
	.kisbetu:
	inc ebx ;noveljuk az ebx regisztert hogy megnezzuk a kovetkezo szam-e
	inc dl ;szamoljuk edx-ben is a hosszt
	mov al,[ebx]
	cmp al,'9' ;megnezzuk hogy a karakter kissebb-e/= mint 9
	jle .talanszam ;ha kissebb-e/
	dec ebx ;visszacsokkentjuk az ebx-et
	dec dl ;visszacsokkentjuk a counterst
	jmp .leptet
	
	.talanszam:
	cmp al,'0'
	jge .helyesmegoldas ;ha elotte betu volt es o legit szam berakjuk az s4-be
	dec ebx
	dec dl
	jmp .leptet
	
	.helyesmegoldas:
	add [s4hossz], byte 1 ;novelem az s4 hosszat
	mov [edi],al ;berakjuk 
	inc edi ;leptetjuk a kovetkezo ertekere
	jmp .leptet
	
	.leptet:
	inc ebx ;noveli az ebx-et
	inc dl ;noveli a countert
	jmp .ciklus
	
	.vege:
	mov cl,[s4hossz] ;cl-be bekerul az s4 hossza
	mov [s4],cl ;az s4-be bekerul a hossz
	popa
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	 
kulonb:
	pusha
	;eax s1
	;ebx s2
	xor edx,edx ;countert lenullaz
	xor ecx,ecx ;loophoz lenullaz
	xor ebp,ebp ;segedvaltozoknak memoriacim konvertalashoz
	
	mov edi,eax ;edi-be eax
	xor eax,eax
	
	mov esi,s3 ;esibe berakjuk s3-at
	inc esi ;noveli cimet az elso karakterhz
	
		
	.fociklus:
	 cmp dl,byte[s1] ;nezi ha a dl tulhaladta-e az s1 hosszat
	 jge .vege ;ha igen
	 
	 inc dl ;ha nem akkor noveljuk a dl-t
	 inc edi ;az s1 string ugrik a kovetkezo karakterre
	mov al,byte [edi]
	
	
	cmp al,'A' ;NEZI HOGY A KARAKTER KISSEBB-E MINT 'A', ha igen
	jb .hibas
	
	cmp al,'Z'
	jle .folyt
	
	cmp al,'a'
	 jb .hibas
	 
	 cmp al,'z'
	 ja .hibas
	 
	
	
	.folyt:
	mov cl,byte[s2] ;cl-be bekerul s2 hossza
	mov ebx,s2 ;ujra betolt s2-t ebx-be a kovetkezo vegignezeshez
	
		
					.ciklus2:	
					inc ebx ;noveli az ebx erteket (kezdetben mindig a 0.van)
					mov al,byte[ebx]	 
					cmp [edi], al
					je .fociklus ;ha egyenloek akkor kozos elem
					inc dh

	 	 
	 loop .ciklus2 ;meghivja a vegignezest
	 jmp .megtalalta
	 

	 .megtalalta:
	 add [s3hossz],byte 1 ;az s3hosszat szamlalo valtozo erteket noveljuk 1-el
	 mov al,byte[edi]
	 mov [esi],al
	 inc esi
	 jmp .fociklus ;ujrahivja a fociklust

	 
	 
	 .hibas:
	 jmp .fociklus
	 
	 .vege:
	 mov al,byte[s3hossz]
	 mov [s3],al
	 
	 popa
	 ret
	 
	
osszefuz:
 pusha
 
 xor ecx,ecx ;ecx-et nullaz
 
 mov eax,edi ;eax-be betolti edi cimet
 mov ebx,esi ;ebx-be betolti esi cimet
 
 inc esi ;tovabblepunk esi-vel
 
 mov cl,[eax] ;cl-be bekerul eax hossza
 add edi,ecx
 inc edi
 
 mov cl,[ebx]
 rep movsb
 
 movzx ecx,byte[eax]
 movzx edx,byte[ebx]
 add ecx,edi
 
 mov [eax],cl
 
 popa
 ret

		

main:
	
	mov eax,beolvasa ;Beolvas A string
	call mio_writestr
	mov eax,s1
	call beolvasstring
	
	mov eax,beolvasb ;beolvas B string
	call mio_writestr
	mov eax,s2
	call beolvasstring
	
	mov eax,fel ;kiirfel
	call mio_writestr
	call mio_writeln
	
	mov eax,beolvasa 
	call mio_writestr
	mov eax,s1
	call kiir
	call mio_writeln
	
	mov eax,beolvasb ;kiirB
	call mio_writestr
	mov eax,s2
	call kiir
	call mio_writeln

	mov eax,s1
	mov ebx,s2
	call kulonb
	
	mov ebx,s2
	call szamjegyek
	
	mov eax,eredmeny 
	call mio_writestr
	mov edi,s3
	mov esi,s4
	call osszefuz
	mov eax,edi
	call kiir
	
	
	ret
	
	
section .bss	
s1 resb 256
s2 resb 256
s3 resb 256
s4 resb 256
	
section .data
fel db "[minden betu az A-bol, ami nincs benne a B-ben (kulon szamit a kis- es nagybetu)] + [azok a szamjegyek a B-bol, amelyek elott kisbetu van]",0
beolvasa db "A= ",0
beolvasb db "B= ",0
eredmeny db "Eredmeny= ",0
s4hossz db 0
s3hossz db 0
