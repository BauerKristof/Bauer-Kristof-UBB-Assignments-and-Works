;Nev:Bauer Kristof
;Azonosotio:bkim1790
;Csoportszam:511

;Labor 2 / Iras / Olvasas

;Írjunk meg egy-egy ASM alprogramot (függvényt, eljárást) 32 bites, előjeles egész (decimális), illetve 32 bites, pozitív hexa számok beolvasására és kiírására.


%include 'mio.inc'

global main

section .text

beolvasdec:
	
push eax
push edx
push esi
	
	xor eax,eax
	xor edx,edx
	xor esi,esi
  		
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
				pop edi
				pop edx
				pop esi
				ret
				
			.ellenoriz:
				cmp al,13 ;megnezi hogy enter-e
				je .kiirvege
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
	
				
			.kiirvege:
				cmp esi,1 ;ha negativ
				je .kiirnegativan
				mov eax,edx
				pop edi
				pop edx
				pop esi
				clc
				ret
			
			.kiirnegativan:
				mov eax,edx 
				neg eax
				pop edi
				pop edx
				pop esi
				clc
				ret
				
				
kiirdecimalis:
	push ebx
	push edx
	push esi

	push dword -1 ;megjegyezzuk a verem veget
	mov ebx,10 ;ebxbel bontjuk a szamjegyet
	cmp eax,0 ;ha negativ a szamunk
	jl .negativ
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
				cmp esi,1 ;ha negativ
				je .kiirminusz
				
				pop eax
				cmp eax,-1
				je .kiirvege
				add eax,'0'
				call mio_writechar
				jmp .felepit
				
			.kiirminusz:
				mov eax,'-'
				call mio_writechar
				xor esi,esi
				jmp .felepit
				
			.negativ:
			xor esi,esi
			mov esi,1
			neg eax
			jmp .ciklus
			
			
			.kiirvege:
			pop esi
			pop edx
			pop ebx
			ret
	 
	 
kiirhex:
	push 	edx
	push	ebx
	push	ecx	
	
	MOV  ECX,8 ;beallitjuk 8bytera
	mov ebx,eax ;az ebx regisztert egy potszamnak hasznaljuk, hogy mindig byteonkent tudjunk kiiratni majd
	
	.eltol:
		MOV  EDX,ebx ;ujratoltjuk a szamot
		CMP ECX,0 ;ellenorizzuk hogy vegig ment-e mind a 8 byteon
		JE .kilep
		SHR  EDX,28 ;eltoljuk a 28 bittel hogy csak 4 bitet nezzunk
		cmp edx,9 ;megnezi hogy szam-e
		JLE   .kiirszam
		
		;ha nem szam akkor karakter, ezesetben kiszamoljuk a karaktert
		add	edx, 'A'
		sub	edx, 10		
		mov eax,edx
		call mio_writechar
		shl ebx, 4 ;kovetkezo 4 bitet nezi
		sub ecx,1 ;csokkentjuk a ciklust
		jmp .eltol

	.kiirszam:
		add edx,'0'
		mov eax,edx
		call mio_writechar
		sub ecx,1
		shl ebx, 4	
		jmp .eltol

	.kilep:
		mov eax,ebx
		pop	ecx
		pop	ebx
		pop	edx
		ret
	

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
	

main:



	
	xor eax,eax
	xor ebx,ebx
	xor ecx,ecx
	xor edx,edx
	
	;beolvassa a decimalist
	mov eax,uzenetbedec
	call mio_writestr
	call beolvasdec
	jc .hiba	
	mov ebx,eax ;azert hogy a szamunk ne valtozzon a decimal kiiratasnal ebx-be mentjuk a tovabbi muveletek miatt
	call mio_writeln
	
	;kiiratja a decimalist
	xor edx,edx
	xor esi,esi
	mov eax,uzenetkidec
	call mio_writestr
	mov eax,ebx 
	call kiirdecimalis
	call mio_writeln
	
	;kiiratja hexaba
	xor edx,edx
	xor ecx,ecx
	mov eax,hexkiir
	call mio_writestr
	mov eax,ebx
	call kiirhex
	call mio_writeln

	;beolvas egy hexa szamot
	mov eax,behex
	call mio_writestr
	call beolvashex
	mov ecx,eax
	jc .hiba	
	
	;kiiratja a hexaszamot decimalisan
	call mio_writeln
	mov edi, eax
	mov eax,uzenetkidec
	call mio_writestr
	xchg eax,edi
	call kiirdecimalis
	

	;kiirja a hexadecimaliskent
	call mio_writeln
	mov eax,hexkiir
	call mio_writestr
	mov eax,ecx
	call kiirhex
	
	;EBX=Elsoszam Deckent ECX=Masodikszam deckent

	add ebx,ecx ;EBX=ket szam osszege
	
	;kiirja a ket szam osszeget decimalisan
	call mio_writeln
	mov eax,eredmenydec
	call mio_writestr
	mov eax,ebx
	call kiirdecimalis
	
	;kiirja a ket szam osszeget hexkent
	call mio_writeln
	mov eax,eredmenyhex
	call mio_writestr
	mov eax,ebx
	call kiirhex
	
	
	ret	
	


	.hiba:
	call mio_writeln
	mov eax, hibas
    call mio_writestr
	call mio_writeln
	ret
	


section .data
 uzenetbedec db "Add meg a decimalis elojeles szamot:",0
 uzenetkidec db "A megadott decimalis elojeles szam= ",0
 behex db "Add meg a hex szamot: 0x",0
 hexkiir db "A szam 16-os szamrendszerben = 0x",0
 hibas db "Hiba: Rossz erteket adtal meg",0
 eredmenydec db "A ket szam osszege decimaliskent= ",0
 eredmenyhex db "A ket szam osszege hexakent= 0x",0
