;Nev:Bauer Kristof
;Azonostio:bkim1790
;Csoportszam 511
;Labor 4 / 4. feladat
;Az előző három eljárásgyűteményhez készítsünk (a megfelelő, megértést segítő szövegeket is tartalmazó!) példaprogramot

%include 'IONUM.inc'
%include 'IOSTR.inc'
%include 'STRINGS.inc'
%include 'mio.inc'

global main

section .text

main:
;-----------32bit---------------------
	;bedec
	mov esi,bedec
	call WriteStr
	call ReadInt
	jc .hiba
	mov [seged],eax
	
	
	;kidec
	mov esi,kidec
	call WriteStr
	call WriteInt
	call mio_writeln
	
	mov eax,[seged]
	;kihex
	mov esi,kihex
	call WriteStr
	call WriteHex
	call mio_writeln
	
	mov eax,[seged]
	;kibin
	mov esi,kibin
	call WriteStr
	call WriteBin
	call mio_writeln
	
	;behex
	mov esi,behex
	call WriteStr
	call ReadHex
	jc .hiba
	mov [seged2],eax
	
	;kidec
	mov esi,kidec
	call WriteStr
	call WriteInt
	call mio_writeln
	
	mov eax,[seged2]
	;kihex
	mov esi,kihex
	call WriteStr
	call WriteHex
	call mio_writeln
	
	mov eax,[seged2]
	;kibin
	mov esi,kibin
	call WriteStr
	call WriteBin
	call mio_writeln
	
	;bebin
	mov esi,bebin
	call WriteStr
	call ReadBin
	jc .hiba
	mov [seged3],eax
	
	;kidec
	mov esi,kidec
	call WriteStr
	call WriteInt
	call mio_writeln
	
	mov eax,[seged3]
	;kihex
	mov esi,kihex
	call WriteStr
	call WriteHex
	call mio_writeln
	
	mov eax,[seged3]
	;kibin
	mov esi,kibin
	call WriteStr
	call WriteBin
	call mio_writeln
	
	;osszeg
	mov eax,[seged3]
	add eax,[seged2]
	add eax,[seged]
	mov [seged4],eax
	
	mov esi,kidec
	call WriteStr
	call WriteInt
	call mio_writeln
	
	mov eax,[seged4]
	;kihex
	mov esi,kihex
	call WriteStr
	call WriteHex
	call mio_writeln
	
	mov eax,[seged4]
	;kibin
	mov esi,kibin
	call WriteStr
	call WriteBin
	call mio_writeln
	call mio_writeln
	call mio_writeln
 ;----------64 BITES RESZ--------------------
 
 ;bedec
	mov esi,bedec64
	call WriteStr
	call ReadInt64
	jc .hiba
	mov [seged],edx ;[seged]-elso szam64bit
	mov [seged2],eax ;[seged2]- elso szam 32bit
	
	
	;kidec
	mov esi,kidec64
	call WriteStr
	call WriteInt64
	call mio_writeln
	
	mov edx,[seged]
	mov eax,[seged2]
	;kihex
	mov esi,kihex64
	call WriteStr
	call WriteHex64
	call mio_writeln
	
	mov edx,[seged]
	mov eax,[seged2]
	;kibin
	mov esi,kibin64
	call WriteStr
	call WriteBin64
	call mio_writeln
	
	;behex
	mov esi,behex64
	call WriteStr
	call ReadHex64
	jc .hiba
	mov [seged3],edx ;seged3 masodik szam 64bitje
	mov [seged4],eax ;seged4 masodik szam 32bitje
	
	;kidec
	mov esi,kidec64
	call WriteStr
	call WriteInt64
	call mio_writeln
	
	mov edx,[seged3]
	mov eax,[seged4]
	;kihex
	mov esi,kihex64
	call WriteStr
	call WriteHex64
	call mio_writeln
	
	mov edx,[seged3]
	mov eax,[seged4]
	;kibin
	mov esi,kibin64
	call WriteStr
	call WriteBin64
	call mio_writeln
	
	;bebin
	mov esi,bebin64
	call WriteStr
	call ReadBin64
	jc .hiba
	mov [seged5],edx ;seged5 3. szam 64bitje
	mov [seged6],eax ;seged6 3. szam 32 bitje
	
	;kidec
	mov esi,kidec64
	call WriteStr
	call WriteInt64
	call mio_writeln
	
	mov edx,[seged5]
	mov eax,[seged6]
	;kihex
	mov esi,kihex64
	call WriteStr
	call WriteHex64
	call mio_writeln
	
	mov edx,[seged5]
	mov eax,[seged6]
	;kibin
	mov esi,kibin64
	call WriteStr
	call WriteBin64
	call mio_writeln
	
	;osszeg
	xor eax,eax
	xor ebx,ebx
	xor ecx,ecx
	xor edx,edx
	
	mov edx,[seged] ;elso szam 64bitje
	mov eax, [seged2] ;elso szam 32bitje
	mov ecx,[seged3] ;masodik szam 64bitje
	mov ebx, [seged4] ;masodik szam 32bitje
	
	add eax,ebx
	adc edx,0
	add edx,ecx
	
	mov ecx,[seged5] ;harmadik szam 64bitje
	mov ebx,[seged6] ;harmadik szam 32bitje
	add eax,ebx
	adc edx,0
	add edx,ecx
	
	
	mov [seged5],edx
	mov [seged6],eax
	
	mov esi,kidec64
	call WriteStr
	call WriteInt64
	call mio_writeln
	
	mov edx,[seged5]
	mov eax,[seged6]
	;kihex
	mov esi,kihex64
	call WriteStr
	call WriteHex64
	call mio_writeln
	
	mov edx,[seged5]
	mov eax,[seged6]
	;kibin
	mov esi,kibin64
	call WriteStr
	call WriteBin64
	call mio_writeln
	call mio_writeln
	ret
 
 

	.hiba:
	call mio_writeln
	mov esi, hibas
    call WriteLnStr
	ret

    
section .data
    bedec db "Add meg a 32 bites 10-es szamrendszerbeli decimalis szamot: ", 0
	kidec db "A 32 bites 10-es szamrendszerbeli decimalis szam: ",0
	bebin db "Add meg a 32bites 2-es szamrendzerbeli binaris szamot: ",0
	kibin db "A 32 bites 2-es szamrendszerbeli binaris szam: ",0
	behex db "Add meg a 32 bites 16-os szamrendszerbeli hexadecimalis szamot: ",0
	kihex db "A 32 bites 16-os szamrendszerbeli hexadecimalis szam: ",0
	bedec64 db "Add meg a 64 bites 10-es szamrendszerbeli decimalis szamot: ", 0
	kidec64 db "A 64 bites 10-es szamrendszerbeli decimalis szam: ",0
	bebin64 db "Add meg a 64 bites 2-es szamrendszerbeli binaris szamot: ",0
	kibin64 db "A 64 bites 2-es szamrendszerbeli binaris szam: ",0
	behex64 db "Add meg a 64 bites 16-os szamrendszerbeli hexadecimalis szamot: ",0
	kihex64 db "A 64 bites 16-os szamrendzerbeli hexadecimalis szam: ",0
	hibas db "Hiba: Rossz erteket adtal meg",0
	

	
section .bss
s1 resb 256
seged resd 1
seged2 resd 1
seged3 resd 1
seged4 resd 1
seged5 resd 1
seged6 resd 1