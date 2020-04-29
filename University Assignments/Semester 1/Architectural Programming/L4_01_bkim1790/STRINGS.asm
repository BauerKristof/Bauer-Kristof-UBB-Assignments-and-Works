;Nev:Bauer Kristof
;Azonostio:bkim1790
;Csoportszam 511
;Labor 4 / 3. feladat
;Stringmuveletek


%include 'mio.inc'

global StrLen,StrCat,StrUpper,StrLower,StrCompact

section .text

StrLen:
xor eax,eax

	.ciklus:
	cmp [esi],byte 0 ;amig nem talalja meg a 0 karaktert
	je .vege
	inc esi
	inc eax ;eaxba szamolja a hosszt
	jmp .ciklus
	
	.vege:
	ret
	
StrCat:
pusha

	xor ecx,ecx
	
	.ciklus:
	cmp[edi],byte 0
	je .betolt2 ;ha bejarta az elso stringet, hozzafuzi a masodikat
	inc edi
	jmp .ciklus ;vegig megy az elso stringen, egeszen a nulla karakterig

	
	.betolt2:
	cmp [esi], byte 0
	je .vege
	mov cl,[esi] ;betolti a 2. string karakteret a clbe
	mov [edi],cl ;hozzafuzi az elsohoz
	inc edi
	inc esi ;noveli mindket stringet
	jmp .betolt2
	
	.vege:
	mov [edi],byte 0 ;hozzafuzi a 0 karaktertert
	popa
	ret
	
StrUpper:
pusha
	
	.ciklus:
	cmp [esi],byte 0
	je .vege
	
	cmp [esi],byte 'a'
	jae .lehetsegeskisbetu ;ha 'a'-nal nagyobb
	inc esi ;ha nem nagyobb tovabb lep
	jmp .ciklus
	
	.lehetsegeskisbetu:
	cmp [esi],byte 'z' ;ha 'a' es 'z' kozott van
	jbe .kisbetu 
	inc esi ;ha nem tovabblep
	jmp .ciklus
	
	.kisbetu:
	sub [esi],byte 32 ;atalakitja nagybetuve
	inc esi
	jmp .ciklus
	
	
	.vege:
	popa
	ret
	
StrLower:
pusha
	;ugyan az mint a kisbetu csak 'A' es 'Z' kozott keressuk es kisbetuve alakitjuk
	
	.ciklus:
	cmp [esi],byte 0
	je .vege
	
	cmp [esi],byte 'A'
	jae .lehetsegesnagy
	
	inc esi
	jmp .ciklus
	
	.lehetsegesnagy:
	cmp [esi],byte 'Z'
	jbe .nagy
	inc esi
	jmp .ciklus
	
	.nagy:
	add [esi],byte 32
	inc esi
	jmp .ciklus
	
	
	.vege:
	popa
	ret
	
StrCompact:
pusha
	xor ecx,ecx
	
	.ciklus:
	cmp [esi], byte 0 ;ha vege kilep
	je .vege
	
	cmp [esi],byte ' ' ;ha space tovabblep
	je .novel
	cmp [esi], byte 9 ;ha tabulator tovabblep
	je .novel
	cmp [esi],byte 13 ;ha CR tovabblep
	je .novel
	cmp [esi],byte 10 ;ha ujsor tovabblep
	je .novel
	
	mov cl,[esi] ;ha nem akkor clbe bekerul a karakter
	mov [edi],cl
	inc edi ;edibe felepiti az uj stringet
	inc esi
	jmp .ciklus
	
	.novel:
	inc esi
	jmp .ciklus
	
	.vege:
	mov [edi],byte 0 ;vegere fuz 0-at
	popa
	ret