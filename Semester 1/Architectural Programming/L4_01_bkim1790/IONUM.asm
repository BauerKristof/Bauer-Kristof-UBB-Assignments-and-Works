;Nev:Bauer Kristof
;Azonostio:bkim1790
;Csoportszam 511
;Labor 4 / 1. feladat
;Szamok irasa es olvasasa 32/64bit

%include 'IOSTR.inc'
%include 'STRINGS.inc'
%include 'mio.inc'


global ReadInt, WriteInt, ReadBin, WriteBin,ReadHex,WriteHex, ReadInt64, WriteInt64, ReadBin64, WriteBin64, ReadHex64, WriteHex64

section .text

ReadInt:
	push edx
	push ecx
	push esi
	
	xor eax,eax
	xor edx,edx

 mov esi, s1 ;betoltjuk a stringet
 mov ecx,256 
 call ReadLnStr
 xor esi,esi
 
 mov edi,s1
 mov al,[edi] ;betolt elso karaktert
 cmp al,byte '-' ;ha - elojel az akkor lep a negativ agra
 je .negativ
 jmp .ellenoriz;ha nem negativ az elso szam hanem pozitiv elvegez egyszer rajta a beolvas ellenorzes majd meghivjuk a tobbi karakterre
	
	
	
			.negativ:
				mov esi,1 ;esibe mentem el, hogy negativ-e vagy sem
				jmp .beolvas
				
			.hiba:
				stc ;beallit carryflag
				pop esi
				pop ecx
				pop edx
				ret
				
			.ellenoriz:
				cmp al,0 ;megnezi hogy enter-e
				je .kiirvege
				cmp al,'0' ;kissebb mint 0
				jl .hiba
				cmp al, '9' ;nagyobb mint 9
				jg .hiba
				
				jmp .szamol
			
				
			.beolvas: ;edibol al-be beolvas
				inc edi
				mov al,[edi]
				jmp .ellenoriz
				
			.szamol:	
				imul edx,10 ;megszorozza a szamjegyet 10-el
				jo .hiba
				sub al,'0' ;asciit szamma alakitja
				add edx,eax ;a szamot megkapja az edx ;ITT A HIBA!!!!
				jo .hiba
				jmp .beolvas ;ujrahiv a kov szamjegyre
	
				
			.kiirvege:
				cmp esi,1 ;ha negativ
				je .kiirnegativan
				mov eax,edx
				pop esi
				pop ecx
				pop edx
				clc
				ret
			
			.kiirnegativan:
				mov eax,edx 
				neg eax
				pop esi
				pop ecx
				pop edx
				clc
				ret
 


WriteInt:
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
	 

ReadBin:
	push edx
	push ecx
	
	xor eax,eax
	xor edx,edx

 mov esi, s1 ;beolvas
 mov ecx,256
 call ReadLnStr
 
 mov esi,s1
 call StrLen
 cmp eax,32 ;megnezzuk hogy a beolvasott binaris szam hossza nem tobb-e mint 32
 jg .hiba ;ha igen hibas
 
 xor esi,esi
 xor eax,eax
 mov edi,s1 ;edibe bekerul a string
 mov al,[edi] ;beolvas elso karakter
 jmp .ellenoriz
	
				
			.hiba:
				stc ;beallit carryflag
				pop ecx
				pop edx
				ret
				
			.ellenoriz:
				cmp al,0 ;megnezi hogy enter-e
				je .kiirvege
				cmp al,'0' ; megnezi hogy 0-e ha igen helyes "agra lep
				je .szamol
				cmp al,'1' ; ugyanez 1-el
				je .szamol
				
				jmp .hiba
			
				
			.beolvas: ;beolvas karakter
				inc edi
				mov al,[edi]
				jmp .ellenoriz
				
			.szamol:	
				sub al,'0' ;asciit szamma alakitja
				shl edx,1 ;eltoljuk az edx-et 1-el hogy legyen hely a szamunknak
				add dl,al ;a szamot megkapja az edx
				jmp .beolvas ;ujrahiv a kov szamjegyre
	
				
			.kiirvege:

				mov eax,edx ;megkapja a felepitett szamot
				pop ecx
				pop edx
				clc
				ret
					
			
WriteBin:
	pusha
	
	xor edx,edx
	xor ecx,ecx
	xor ebx, ebx
	
	mov ebx,eax
	xor edx,edx
	mov ecx,32 ;32 szamjegyet kell kiirassunk
	
	.ciklus:
	cmp ecx,0
	je .vege
	
	xor eax,eax	;lenullaz eax
	rcl ebx,1 ;eltolja ebx-et
	adc al,'0' ;hozzaadja eax-hez a carryt
	call mio_writechar ;kiirja
	
	sub ecx,1 ;csokkentjuk az ecx-et
	jmp .ciklus

	

	.vege:		
	popa
	ret
	
	
ReadHex:
push edx 
push ebx 
	
	xor eax,eax
	xor edx,edx
	xor ebx,ebx
	
	mov esi, s1
	mov ecx,256
	call ReadLnStr
	
	mov esi,s1
	mov al,[esi] ;al-be bekerul a karakter
	jmp .ellenoriz ;vegrehajtodik rajta az ellenorzes
				
			.beolvas: ;beolvas uj karaktert al-be
				inc esi
				mov al, [esi]
				jmp .ellenoriz
				
			.ellenoriz:
				cmp al,0 ;megnezi hogy sorvege-e
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
				ret
			
				
			.szam:	
				sub eax,'0'
				shl ebx,4 ;eltolassal hatvanyoljuk a szamot
				jo .hiba
				add ebx,eax
				jo .hiba
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
			sub eax,'A'
			add eax,10
			shl ebx,4
			jo .hiba
			add ebx,eax
			jo .hiba
			jmp .beolvas ;ujrahiv a kov szamjegyre
			
			
			.kisbetu: ;kisbetut szamma alakit
			sub eax,'a'
			add eax,10
			shl ebx,4
			jo .hiba
			add ebx,eax
			jo .hiba
			jmp .beolvas ;ujrahiv a kov szamjegyre
				
	
				
			.kiirvege:
				mov eax,ebx
				pop ebx
				pop edx
				clc
				ret
				

WriteHex:
	push 	edx
	push	ebx
	push	ecx	
	
	push eax ;a 0x elotag miatt pusholjuk az eax-et
	mov		eax,'0'
	call	mio_writechar
	mov		eax,'x'
	call	mio_writechar
	pop eax
	
	
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

	
;;;;;;;;;;;;;;;;64BITES RESZ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


ReadInt64:
	push ecx
	push ebx
	push edi
	
	xor eax,eax
	xor edx,edx
	xor ecx,ecx
	xor edi,edi
	
	mov esi,s1
	mov ecx, 256 ;beolvas
	call ReadLnStr
	
	xor ecx,ecx
	
	mov esi,s1
	mov ebx,10 ;szorzot beallitjuk 10-re

	movzx ecx,byte[esi] ;betoltjuk az ecx-be a karaktert 
	cmp ecx, '-'
	je .negativ ;ha negativ ugrunk a negativ agra
	
	jmp .ellenoriz ;ha nem negativ ellenorzi a karaktert
	
	.negativ:
		mov [negativ],byte 1 ;[negativ] segedvaltozot hasznaljuk arra, hogy megjegyezzuk negativ volt-e
		jmp .beolvas
		
	.hiba:
		stc ;beallit carry es kilep
		pop edi
		pop ebx
		pop ecx
		ret
	
	.ellenoriz:
		cmp ecx, 0
		je .kiirvege
		cmp ecx, '0'
		jl .hiba
		cmp ecx, '9'
		jg .hiba
		
		jmp .ciklus ;ha helyes a karakter kovetkezik a kiszamolas
		
	.beolvas:
		inc esi
		movzx ecx, byte[esi]
		jmp .ellenoriz
	
	
	.ciklus:
	sub ecx,'0' ;szamma alakitjuk 
	mov edi,edx ;az edx-et hogy ne rontsuk el edi-be toltjuk
	mul ebx ;a 10-el szorzunk
	imul edi,ebx ;eltolas
	jo .hiba
	add edx,edi ;visszakerul a szam
	jo .hiba
	add eax,ecx ;a 32bites reszt alakitjuk ki
	adc edx,0 ;ha nem ferunk bele a 32bitbe az edxbe kerul a carry
	jo .hiba
	jmp .beolvas
	
	
	.kiirvege:
	cmp [negativ],byte 1
	je .kiirnegativan	 ;ha negativ volt a szam
	pop edi
	pop ebx
	pop ecx
	clc
	ret
	
	.kiirnegativan:
	not eax ;komplementerkod miatt nem negeljuk hanem notoljuk
	not edx
	add eax,1 ;a neg kifutobitjeit hozzadjuk
	adc edx,0
	pop edi
	pop ebx
	pop ecx
	clc
	ret
 
 
		
WriteInt64:
	push ecx
	push ebx
	
	push dword -1 ;megjegyezzuk a verem veget
	mov ebx,10	
	xor ecx,ecx

	cmp		edx, 0			;megnezzuk hogy negativ vagy pozitiv a szam
	jge		.ciklus	
					
	not		edx		;ha negativ akkor notoljuk a szamot
	not		eax
	add eax,1
	adc edx,0
	
	push	eax
	mov		eax, '-'		;kiiratjuk a minusz jelt
	call	mio_writechar	
	pop		eax
	
	
	.ciklus:
	mov ecx,eax ;atkerul ecx-be eax
	mov eax,edx ;eaxbe bekerul a 64bit
	xor edx,edx ;lenullazzuk az edx-et
	div ebx ;lebontjuk 64bites a szamjegyet
	xchg eax,ecx ;visszacsereljuk
	div ebx ;32bites szamjegy lebontas
	push edx ;berakjuk a verembe a szamot
	mov edx,ecx
	test edx,edx
	jnz .ciklus
	test eax,eax
	jnz .ciklus
	
	.felepit:	;a verembol felepitjuk a kiiratando szamot
	xor eax,eax
	pop eax
	cmp eax,-1
	je .kiirvege
	add eax,'0'
	call mio_writechar
	jmp .felepit
	
	.kiirvege:
	pop ebx
	pop ecx
	ret
	
ReadBin64:
	push ecx
	push ebx
	
	xor eax,eax
	xor edx,edx
	xor ebx,ebx

 mov esi, s1
 mov ecx,256
 call ReadLnStr
 
 mov esi,s1
 call StrLen
 cmp eax,64 ;megnezzuk hogy a beolvasott binaris szam hossza nem tobb-e mint 64
 jg .hiba ;ha igen hibas
 
 xor esi,esi
 xor eax,eax
 mov edi,s1
 mov al,[edi]
 jmp .ellenoriz ;ellenorizzuk hogy helyes-e a karakter
	
				
			.hiba:
				stc ;beallit carryflag
				pop ebx
				pop ecx
				ret
				
			.ellenoriz:
				cmp al,0 ;megnezi hogy enter-e
				je .kiirvege
				cmp al,'0' ; ha 0 szamol
				je .szamol
				cmp al,'1' ; ha 1 szamol
				je .szamol
				
				jmp .hiba
			
				
			.beolvas:
				inc edi
				mov al,[edi]
				jmp .ellenoriz
				
			.szamol:	
				sub al,'0' ;asciit szamma alakitja
				shl edx,1 ;az edx-1et eltoljuk 1-el
				shl ebx,1 ;az ebx-et eltoljuk 1-el, ide epitjuk a 32bitet
				adc edx,0 ;ha az eltolasbol carry keletkezett atkerul edx-be
				add bl,al ;felepitjuk az ebx-be a szamot
				jmp .beolvas ;ujrahiv a kov szamjegyre
	
				
			.kiirvege:
				mov eax,ebx ;az eax megkapja a 32bites regisztert
				
				pop ebx
				pop ecx
				clc
				ret
					
WriteBin64:
	pusha
	
	xor ecx,ecx
	xor ebx, ebx
	
	mov ebx,edx
	push eax ;lementjuk a verembe az eax-et
	mov ecx,32
	
	.ciklus: ;felepitjuk eloszor az edx-et  a 32bites kiiratassal
	cmp ecx,0
	je .inicializal
	
	xor eax,eax	;lenullaz eax
	rcl ebx,1 ;eltolja ebx-et
	adc al,'0' ;hozzaadja eax-hez a carryt
	call mio_writechar ;kiirja
	
	sub ecx,1 ;csokkentjuk az ecx-et
	jmp .ciklus

	.inicializal: ;felepitjuk az eax-et a 32bites kiiratassal
	xor ecx,ecx
	xor ebx,ebx
	pop eax  ;kiszedjuk a verembol az eax-et
	
	mov ebx,eax
	mov ecx,32
	
	.ciklus2:
	cmp ecx,0
	je .vege
	
	xor eax,eax	;lenullaz eax
	rcl ebx,1 ;eltolja ebx-et
	adc al,'0' ;hozzaadja eax-hez a carryt
	call mio_writechar ;kiirja
	
	sub ecx,1 ;csokkentjuk az ecx-et
	jmp .ciklus2
	
	.vege:		
	popa
	ret

ReadHex64:
push ebx 
push ecx
push edi
	
	xor eax,eax
	xor edx,edx
	xor edi,edi
	xor ebx,ebx
	xor ecx,ecx
	
	mov esi, s1
	mov ecx,256
	call ReadLnStr
	
	mov esi,s1
	call StrLen
	cmp eax,16 ;megnezzuk hogy a beolvasott hexadecimalis szam hossza nem tobb-e mint 16, ha igen tulcsordulas hiba
	jg .hiba ;ha igen hibas
	xor esi,esi
    xor eax,eax
	
	xor ecx,ecx
	mov ebx,16
	mov esi,s1
	
	movzx ecx,byte [esi]
	jmp .ellenoriz	
	
	
	;a 64bites hexabeolvasas megegyezik a 64bites decimalis szam beolvasasaval
				
				
			.beolvas:
				inc esi
				movzx ecx,byte [esi]
				jmp .ellenoriz
				
			.ellenoriz:
				cmp ecx,0 ;megnezi hogy sorvege-e
				je .kiirvege
				cmp ecx,'0' ;kissebb mint 0
				jl .hiba
				cmp ecx,'9' ;ha 9-0 kozott van
				jle .szam
				cmp ecx,'9' ;ha betu
				jg .betu
				
				jmp .beolvas
				
			.hiba:
				stc ;beallit carryflag
				pop edi
				pop ecx 
				pop ebx
				ret
			
			.ciklus:
				mov edi,edx
				mul ebx
				imul edi,ebx
				add edx,edi
				add eax,ecx
				adc edx,0
				jmp .beolvas
			
			.szam:	
				sub ecx,'0'
				jmp .ciklus
				
			.betu:
			cmp ecx,'A' ;9esA kozotti karakterek hibasak
			jl .hiba
			cmp ecx,'F' ;A->F
			jle .atalakit
			cmp ecx,'a' ;F->a kozotti szimbolumokra hiba
			jl .hiba
			cmp ecx,'f'
			jle .kisbetu
			jmp .hiba ;ha egyik casebe se ment bele azt jelenti f-nel nagyobb az meg hibas
				
			.atalakit: ;nagybetut szamma alakit
			sub ecx,'A'
			add ecx,10
			jmp .ciklus
			
			
			.kisbetu: ;kisbetut szamma alakit
			sub ecx,'a'
			add ecx,10
			jmp .ciklus
					
			.kiirvege:
				pop edi
				pop ecx
				pop ebx
				clc
				ret

	
WriteHex64:
	pusha
	
	push eax
	mov		eax,'0'
	call	mio_writechar
	mov		eax,'x'
	call	mio_writechar
	pop eax
	
	xor ebx,ebx 
	xor ecx,ecx
	
	MOV  [negativ],byte 8 ;a [negativ]-at memoriasporolast figyelembe veve, egy segedvaltozonak hasznaljuk,beallitjuk 8bytera az edx kiirasahoz
	push eax ;lementjuk a verembe hogy a 32bites kiirataskor tudjuk hasznalni
	mov ecx,edx ;az ecx regisztert egy potszamnak hasznaljuk, hogy mindig byteonkent tudjunk kiiratni majd
	
	
	.eltol:
		MOV  ebx,ecx ;ujratoltjuk a szamot
		CMP [negativ],byte 0 ;ellenorizzuk hogy vegig ment-e mind a 8 byteon
		JE .inicializal
		SHR  ebx,28 ;eltoljuk a 28 bittel hogy csak 4 bitet nezzunk
		cmp ebx,9 ;megnezi hogy szam-e
		JLE   .kiirszam
		
		;ha nem szam akkor karakter, ezesetben kiszamoljuk a karaktert
		add	ebx, 'A'
		sub	ebx, 10		
		mov eax,ebx
		call mio_writechar
		shl ecx, 4 ;kovetkezo 4 bitet nezi
		sub [negativ],byte 1 ;csokkentjuk a ciklust
		jmp .eltol

	.kiirszam:
		add ebx,'0'
		mov eax,ebx
		call mio_writechar
		sub [negativ],byte 1
		shl ecx, 4	
		jmp .eltol

	
	.inicializal: ;inicializalunk az eax kiiratasahoz
	xor ebx,ebx 
	xor ecx,ecx
	
	mov [negativ],byte 8 
	pop eax ;kiszedjuk a verembol hogy kiirassuk a 32bites reszt
	mov ecx,eax ;az ecx regisztert egy potszamnak hasznaljuk, hogy mindig byteonkent tudjunk kiiratni majd
	
	.eltol32:
		MOV  ebx,ecx ;ujratoltjuk a szamot
		CMP [negativ],byte 0 ;ellenorizzuk hogy vegig ment-e mind a 8 byteon
		JE .kilep
		SHR  ebx,28 ;eltoljuk a 28 bittel hogy csak 4 bitet nezzunk
		cmp ebx,9 ;megnezi hogy szam-e
		JLE   .kiirszam32
		
		;ha nem szam akkor karakter, ezesetben kiszamoljuk a karaktert
		add	ebx, 'A'
		sub	ebx, 10		
		mov eax,ebx
		call mio_writechar
		shl ecx, 4 ;kovetkezo 4 bitet nezi
		sub [negativ],byte 1 ;csokkentjuk a ciklust
		jmp .eltol32

	.kiirszam32:
		add ebx,'0'
		mov eax,ebx
		call mio_writechar
		sub [negativ],byte 1
		shl ecx, 4	
		jmp .eltol32
		
		
	.kilep:
		popa
		ret
		
	
section .bss
s1 resb 256
negativ resd 1