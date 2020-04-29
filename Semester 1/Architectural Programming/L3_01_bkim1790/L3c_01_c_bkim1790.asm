;Nev:Bauer Kristof
;Azonostio:bkim1790
;Csoportszam 511
;Labor 3 | C feladat /3as (CSTRING) / 01 Alpont
;C Feldat/01.:[minden betű az A-ból, ami nincs benne a B-ben (külön számít a kis- és nagybetű)] + [azok a számjegyek a B-ből, amelyek előtt kisbetű van]


%include 'mio.inc'

global main

section .text

beolvasstring:
pusha
 ;EAX-be van a memoriacim
 mov edi,eax ;ebx-be memoriacim
 
 .ciklus:
 call mio_readchar ;beolvas al
 cmp al,13
 je .vege
 call mio_writechar ;kiir al
 stosb
 jmp .ciklus
 
 
  .vege:
	mov [edi],byte 0
	popa
	ret
 
 
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 kiir:
 push eax
 push ecx
 push esi
 
 
 mov esi,eax ;esibe berakja a cimet
  
 .ciklus:
	lodsb ;karakter al || esi++
	cmp al,0
	jz  .vege
	call mio_writechar
	jmp .ciklus ;csokkenti a hosszt ecx

.vege:

pop esi
pop ecx
pop eax
ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
	
szamjegyek:
	pusha
	
	;EBX-BEN A SZAM	
	
	
	mov edi,s4 ;EDI-be s4

	
	.ciklus:
	
	cmp [ebx],byte 0 ;megnezi hogy veget ert-e a string
	je .vege
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
	mov al,[ebx]
	cmp al,'9' ;megnezzuk hogy a karakter kissebb-e/= mint 9
	jle .talanszam ;ha kissebb-e/
	dec ebx ;visszacsokkentjuk az ebx-et
	jmp .leptet
	
	.talanszam:
	cmp al,'0'
	jge .helyesmegoldas ;ha elotte betu volt es o legit szam berakjuk az s4-be
	dec ebx
	jmp .leptet
	
	.helyesmegoldas:
	mov [edi],al
	inc edi
	jmp .leptet
	
	.leptet:
	inc ebx ;noveli az ebx-et
	jmp .ciklus
	
	.vege:
	mov [edi],byte 0 ;az s4-be bekerul a hossz
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
		
	.fociklus:
	 mov al,byte [edi]
	 inc edi
	cmp al,0
	je .vege
	
	cmp al,'A' ;NEZI HOGY A KARAKTER KISSEBB-E MINT 'A', ha igen
	jb .hibas
	
	cmp al,'Z'
	jle .folyt
	
	cmp al,'a'
	 jb .hibas
	 
	 cmp al,'z'
	 ja .hibas
	 
	
	
	.folyt:
	mov ebx,s2 ;ujra betolt s2-t ebx-be a kovetkezo vegignezeshez
	
		
					.ciklus2:	
					cmp al,[ebx]
					je .fociklus
					cmp [ebx],byte 0
					jz .megtalalta
					inc ebx

	 	 
	 jmp .ciklus2 ;meghivja a vegignezest
	 

	 .megtalalta:
	 mov [esi],al
	 inc esi
	 jmp .fociklus ;ujrahivja a fociklust

	 
	 
	 .hibas:
	 jmp .fociklus
	 
	 .vege:
	 mov [esi],byte 0
		 
	 popa
	 ret
	 
	
 
	
osszefuz:

	pusha

	xor ecx,ecx
	

	.ciklus:
	cmp[eax],byte 0
	je .betolt2
	inc eax
	jmp .ciklus

	
	.betolt2:
	cmp [ebx], byte 0
	je .vege
	mov cl,[ebx]
	mov [eax],cl
	inc eax
	inc ebx
	jmp .betolt2
	
	.vege:
	mov [eax],byte 0
	popa
	ret

		

main:
	
	mov eax,beolvasa ;beolvassuk az A stringet
	call mio_writestr
	mov eax,s1
	call beolvasstring
	
	call mio_writeln
	mov eax,beolvasb ;beolvassuk a B stringet
	call mio_writestr
	mov eax,s2
	call beolvasstring
	call mio_writeln
	
	mov eax,fel
	call mio_writestr
	call mio_writeln

	mov eax,beolvasa ;kiir A string
	call mio_writestr
	mov eax,s1
	call kiir
	call mio_writeln
	
	mov eax,beolvasb ;kiir B string
	call mio_writestr
	mov eax,s2
	call kiir
	call mio_writeln

	mov eax,s1
	mov ebx,s2
	call kulonb
	
	mov ebx,s2
	call szamjegyek

	
	mov eax, eredmeny
	call mio_writestr
	mov eax,s3
	mov ebx,s4
	call osszefuz
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