;Nev:Bauer Kristof
;Azonostio:bkim1790
;Csoportszam 511
;Labor 5 / 1. feladat
;1. E(a,b,c,d) = sqrt(a + b / 2) + b * (d - c)



%include 'mio.inc'


global main

section .text


ReadFloat:
  push edx
  push esi
	
	xor eax,eax
	xor edx,edx
	xor esi,esi
  	
	xorps xmm0,xmm0 ;ide epitem a szamot
	xorps xmm1,xmm1 ;0,1-es szorzo
	xorps xmm2,xmm2 ;ebbe konvertalom a tortreszt
	
	movss	xmm1, [szorzo]

		
	;EGESZ RESZ BEOLVASASA:
	
	call mio_readchar
	cmp al,'-' ;ha negativ az elso karakter 
	je .negativ ;ralep a negativ agra
	
	jmp .ellenoriz;ha nem negativ az elso szam hanem pozitiv elvegez egyszer rajta a beolvas ellenorzes majd meghivjuk a tobbi karakterre
	
			.negativ:
				mov esi,1
				call mio_writechar
				jmp .beolvas
				
			.hiba:
				stc ;beallit carryflag
				pop esi
				pop edx
				ret
				
			.ellenoriz:
				cmp al,2Eh ;megnezi hogy pont-e
				je .felepitegesz
				cmp al,'0' ;kissebb mint 0
				jl .hiba
				cmp al, '9' ;nagyobb mint 9
				jg .hiba
				
				call mio_writechar
				jmp .szamol
			
				
			.beolvas: ;beolvas karakter->szam(edx)
				call mio_readchar
				jmp .ellenoriz
				
			.szamol:	
				imul edx,10 ;megszorozza a szamjegyet 10-el
				sub eax,'0' ;asciit szamma alakitja
				add edx,eax ;a szamot megkapja az edx
				jmp .beolvas ;ujrahiv a kov szamjegyre
	
				
			.felepitegesz:
				call mio_writechar
			    cvtsi2ss xmm0,edx
				jmp .beolvastort
				
	;---------TORTRESZ BEOLVASASA-------------
	
			.ellenorizt:
			cmp al,13 ;ha enter
			je .konvert
			cmp al,'0'
			jl .hiba
			cmp al,'9'
			jg .hiba
			call mio_writechar
			jmp .szamoltort
	
			.beolvastort:
			xor eax,eax ;lenullazzuk hogy a beolvastort ellenorzese ne adjon hibat a . miatt

			call mio_readchar
			jmp .ellenorizt
			
			.szamoltort:
			sub eax,'0'
			cvtsi2ss xmm2,eax ;xmm2-be konvertalom a szamot
			mulss xmm2,xmm1 ;megszorzom 0,1-el
			addss xmm0,xmm2 ;hozzadom az egeszreszhez
			mulss xmm1,[szorzo] ;a szorzot tovabbszorzom
			jmp .beolvastort
			
			
			.konvert:
				cmp esi,1 ;ha negativ
				je .konvertneg
				
				xorps xmm1,xmm1 ;visszanullazzom a regisztereket
				xorps xmm2,xmm2 
				pop esi
				pop edx
				clc
				ret
			
			.konvertneg:	
				movss xmm1,xmm0 ;xmm1-be berakom a felepitett szamot
				xorps xmm0,xmm0 ;xmm0-at lenullazom
				subss xmm0,xmm1 ;kivonom 0-bol a felepitett szamot
				xorps xmm1,xmm1 ;lenullazom a regisztert
				xorps xmm2,xmm2 
				pop esi
				pop edx
				clc
				ret
				
WriteFloat:
	push eax
	push ecx
	
	xorps xmm1,xmm1 ;ide fogjuk tarolni a kivonando egeszreszt
	xor ecx,ecx
	mov ecx,4 ;4x fut le 
	
	comiss	xmm0, xmm1 ;ha a szam nagyobb mint nulla
	jae		.egeszkiir
	mov		al,'-' ;kiirjuk a minuszt
	call	mio_writechar
	movss xmm1,[minuszegy]  ;xmm1-be berakjuk a minuszegyet
	mulss xmm0,xmm1 ;negaljuk xmm0-t
	
	xorps xmm1,xmm1 

	
	
	;---------EGESZRESZ KIIRASA-----------------
	.egeszkiir:
	cvttss2si eax,xmm0
	call  WriteInt
	push eax
	mov eax,'.'
	call mio_writechar
	pop eax

	;------TORTRESZ KIIRASA -------------------
	
	
	.ciklus:
	cvtsi2ss xmm1,eax ;xmm1-be konvertalom a szamot
	subss xmm0,xmm1 ;megkapom a tortreszt
	mulss xmm0,[tiz] ;beszorozzuk a tortreszt tizzel hogy megkapjuk az egeszet
	xor eax,eax
	CVTTSS2SI eax,xmm0 ;az eax-be bekerul az egeszreszhez

	;cmp eax,0
	;je .vege
	add eax,'0'
	call mio_writechar ;kiirjuk az egeszreszt
	sub eax,'0'
	loop .ciklus

	
	.vege:
	pop ecx
	pop eax
	ret
	
WriteInt:
	pusha

	push dword -1 ;megjegyezzuk a verem veget
	mov ebx,10 ;ebxbel bontjuk a szamjegyet
	jmp .ciklus

			.ciklus: ;lebont szam
				xor edx,edx
				div ebx ;lebontjuk a szamjegyet
				push edx ;a szamjegy bekerul az edx-be . edx>verembe
				test eax,eax;megnezzuk hogy lebontottuk e az osszes szamjegyet	
				jnz .ciklus ;ujrahivjuk a lebontast
				
				test eax,eax
				je .felepit
			
			.felepit:
				pop eax
				cmp eax,-1
				je .kiirvege
				add eax,'0'
				call mio_writechar
				jmp .felepit
			
			
			.kiirvege:
			popa
			ret
			
ReadExpo:
  push edx
  push esi
  push ecx
	
	xor eax,eax
	xor edx,edx
	xor esi,esi
  	
	xorps xmm0,xmm0 ;ide epitem a szamot
	xorps xmm1,xmm1 ;0,1-es szorzo
	xorps xmm2,xmm2 ;ebbe konvertalom a tortreszt
	
	movss	xmm1, [szorzo]

		
	;EGESZ RESZ BEOLVASASA:
	
	call mio_readchar
	cmp al,'-' ;ha negativ az elso karakter 
	je .negativ ;ralep a negativ agra
	
	jmp .ellenoriz;ha nem negativ az elso szam hanem pozitiv elvegez egyszer rajta a beolvas ellenorzes majd meghivjuk a tobbi karakterre
	
			.negativ:
				mov esi,1
				call mio_writechar
				jmp .beolvas
				
			.hiba:
				stc ;beallit carryflag
				pop ecx
				pop esi
				pop edx
				ret
				
			.ellenoriz:
				cmp al,2Eh ;megnezi hogy pont-e
				je .felepitegesz
				cmp al,'0' ;kissebb mint 0
				jl .hiba
				cmp al, '9' ;nagyobb mint 9
				jg .hiba
				
				call mio_writechar
				jmp .szamol
			
				
			.beolvas: ;beolvas karakter->szam(edx)
				call mio_readchar
				jmp .ellenoriz
				
			.szamol:	
				imul edx,10 ;megszorozza a szamjegyet 10-el
				sub eax,'0' ;asciit szamma alakitja
				add edx,eax ;a szamot megkapja az edx
				jmp .beolvas ;ujrahiv a kov szamjegyre
	
				
			.felepitegesz:
				call mio_writechar
			    cvtsi2ss xmm0,edx
				jmp .beolvastort
				
	;---------TORTRESZ BEOLVASASA-------------
	
			.ellenorizt:
			cmp al,'e' ;ha beirta az e betut
			je .konvert
			cmp al,'E' 
			je .konvert
			cmp al,'0'
			jl .hiba
			cmp al,'9'
			jg .hiba
			call mio_writechar
			jmp .szamoltort
	
			.beolvastort:
			xor eax,eax ;lenullazzuk hogy a beolvastort ellenorzese ne adjon hibat a . miatt

			call mio_readchar
			jmp .ellenorizt
			
			.szamoltort:
			sub eax,'0'
			cvtsi2ss xmm2,eax ;xmm2-be konvertalom a szamot
			mulss xmm2,xmm1 ;megszorzom 0,1-el
			addss xmm0,xmm2 ;hozzadom az egeszreszhez
			mulss xmm1,[szorzo] ;a szorzot tovabbszorzom
			jmp .beolvastort
			
			
			.konvert:
				call mio_writechar ;kiirja az e betut
				cmp esi,1 ;ha negativ
				je .konvertneg
				
				xorps xmm1,xmm1 ;visszanullazzom a regisztereket
				xorps xmm2,xmm2 
				jmp .exponencialisepit
				
			
			.konvertneg:	
				movss xmm1,xmm0 ;xmm1-be berakom a felepitett szamot
				xorps xmm0,xmm0 ;xmm0-at lenullazom
				subss xmm0,xmm1 ;kivonom 0-bol a felepitett szamot
				xorps xmm1,xmm1 ;lenullazom a regisztert
				xorps xmm2,xmm2 
				
			;-----E-ig felepitve a szam-----
			.exponencialisepit:
			
			xor eax,eax
			xor edx,edx
			xor esi,esi
  		
			call mio_readchar
			cmp al,'-' ;ha negativ az elso karakter 
			je .negativ2 ;ralep a negativ agra
	
			jmp .ellenoriz2;ha nem negativ az elso szam hanem pozitiv elvegez egyszer rajta a beolvas ellenorzes majd meghivjuk a tobbi karakterre
	
	
	
			.negativ2:
				mov esi,1
				call mio_writechar
				jmp .beolvas2
				
				
			.ellenoriz2:
				cmp al,13 ;megnezi hogy enter-e
				je .kiirvege
				cmp al,'0' ;kissebb mint 0
				jl .hiba
				cmp al, '9' ;nagyobb mint 9
				jg .hiba
				
				call mio_writechar
				jmp .szamol2
			
				
			.beolvas2: ;beolvas karakter->szam(edx)
				call mio_readchar
				jmp .ellenoriz2
				
			.szamol2:	
				imul edx,10 ;megszorozza a szamjegyet 10-el
				sub eax,'0' ;asciit szamma alakitja
				add edx,eax ;a szamot megkapja az edx
				jmp .beolvas2 ;ujrahiv a kov szamjegyre
				
			.kiirvege:
				cmp esi,1 ;ha negativ
				je .kiirnegativan
				mov ecx,edx
				jmp .exposzorzat
			
			.kiirnegativan:
				mov ecx,edx 
				neg ecx	
			
			;--------------FELPEITJUK AZ EXPONENCIALIS SZAMOT-----------
			.exposzorzat:
			cmp ecx,0
			je .teljesvege
			
			movss xmm1,[tiz] ;tizzel fogunk osztani vagy szorozni
			mov eax, ecx ;eax-ba lementem a kiiras miatt
			cmp ecx,0
			jl .osztas ;ha a beolvasott szam negativ akkor osztunk 10-el
			
			.szorzas:
			mulss xmm0,xmm1
			loop .szorzas
			jmp .teljesvege
			
			.osztas:
			neg ecx ;negaljuk az ecx-et hogy hanyszor pozitivszor vegezze el a muveletet
				.ciklus:
				divss xmm0,xmm1
				loop .ciklus
			
			.teljesvege:
			clc
			pop ecx
			pop esi
			pop edx
			ret
			
			
WriteExpo:
push ebx ;ebbe szamoljuk hogy hanyszor osztottunk vagy szoroztunk 10-el
push eax ;ide kerul mindig az egeszresz

	xor ebx,ebx
	xor eax,eax
	xorps xmm1,xmm1 ;visszanullazzom a regisztereket

	comiss	xmm0, xmm1 ;ha a szam nagyobb mint nulla
	jae		.pozitiv
	mov		al,'-' ;kiirjuk a minuszt
	call	mio_writechar
	movss xmm1,[minuszegy]  ;xmm1-be berakjuk a minuszegyet
	mulss xmm0,xmm1 ;negaljuk xmm0-t
	
	;--------E Felepitese---------
	
	.pozitiv:
	comiss xmm0,[nulla] ;megnezi hogy kiiratando regiszter nem 0
	je .kiiratas ;ha 0 akkkor ugrik a kiiratashoz
	
	CVTTSS2SI eax,xmm0 ;letruncoljuk az egesz reszt
	
	cmp eax,0 ;ha az egeszresz 0 akkor szorzunk 10-el
	je .szorzas
	cmp eax,9 ;ha nagyobb mint 9 akkor osztunk 10-el
	jg .osztas
	
	.szorzas:
	cmp eax,0
	jg .kiiratas ;ha elertunk az elso nem nulla szamjegyig kiiratunk
	mulss xmm0, [tiz] ;szorozzuk 10-el az xmmt
	cvttss2si eax, xmm0 ;visszaadjuk az egesz reszt megint
	inc ebx ;noveljuk a szorzas countert
	jmp .szorzas

	.osztas:
	cmp eax,9 ;ha kissebb vagy egyenlo mint 9akkor megvan a szam es jon a kiiratas
	jbe .kiiratas
	divss xmm0,[tiz] ;osztunk 10-el
	cvttss2si eax,xmm0 ;visszaadjuk az egeszreszt megint
	dec ebx ;csokkentjuk az osztas countert
	jmp .osztas
	
	.kiiratas:
	call WriteFloat ;meghivjuk a hagyomanyos kiiratast
	xor eax,eax
	mov al,'e' ;kiirjuk az e-t
	call mio_writechar
	
	cmp ebx,0
	jle .negativkiir ;ha osztottunk akkor kell -e-t
	mov eax,ebx ;kiirjuk a felepitett szamot
	add eax,'0'
	call mio_writechar
	pop eax
	pop ebx
	ret
	
	
	.negativkiir:
	mov eax,'-' 
	call mio_writechar
	
	;neg ebx ;mivel a szamunk negativ, pozitiv lesz
	imul ebx,-1
	mov eax,ebx
	add eax,'0'
	call mio_writechar
	pop eax
	pop ebx
	ret
	
	
	
	
	
	
			
			
			
				

	
main:
 xor eax,eax
 xor ebx,ebx
 xor ecx,ecx
 xor edx,edx

 mov eax,fel
 call mio_writestr
 call mio_writeln
 
 mov eax,befloat
 call mio_writestr
 call ReadFloat
 jc .hiba
 call mio_writeln
 movss xmm3,xmm0 ;xmm3 = a
 
 mov eax,beexpo
 call mio_writestr
 call ReadExpo
 jc .hiba
 call mio_writeln
 movss xmm4,xmm0 ;xmm4 = b
 
 mov eax,befloat
 call mio_writestr
 call ReadFloat
 jc .hiba
 call mio_writeln
 movss xmm5,xmm0 ;xmm5 = c
 
 mov eax,beexpo
 call mio_writestr
 call ReadExpo
 jc .hiba
 call mio_writeln
 movss xmm6,xmm0 ;xmm6 = d
 
 movss xmm7,xmm4
 mov ebx,2
 cvtsi2ss xmm1,ebx
 divss xmm7,xmm1 ; xmm7=b/2
 


 addss xmm3,xmm7
 sqrtss xmm2,xmm3 ;sqrt(a+b/2)
 xorps xmm1,xmm1
 xorps xmm7,xmm7
 
 subss xmm6,xmm5 ;(d-c)
 mulss xmm6,xmm4 ;b*(d-c)
 addss xmm2,xmm6
 
 mov eax,kifloat
 call mio_writestr
 movss xmm0,xmm2
 call WriteFloat
 call mio_writeln

 mov eax,kiexpo
 call mio_writestr
 movss xmm0,xmm2
 call WriteExpo
 
 ret

 	.hiba:
	call mio_writeln
	mov eax, hibas
    call mio_writestr
	call mio_writeln
	ret
	
 
section .bss

	
section .data
	a dd 0.
    b dd 0.
    c dd 0.
    d dd 0.
	szorzo dd 0.1
	tiz dd 10.0
	minuszegy dd -1.0
	nulla dd 0.
    befloat db "Add meg a szamot hagyomanyos formaban:", 0
	kifloat db "A szam hagyomanyos formaban: ",0
	beexpo db "Add meg a szamot exponencialis formaban (egeszresz.tortresz(e)+-hatvany: ",0
	kiexpo db "A szam exponencialis formaban: ",0
	hibas db "Hiba: Rossz erteket adtal meg",0
	fel db "E(a,b,c,d) = sqrt(a + b / 2) + b * (d - c)",0


