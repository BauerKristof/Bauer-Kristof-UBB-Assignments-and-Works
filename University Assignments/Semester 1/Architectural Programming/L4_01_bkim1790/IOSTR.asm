;Nev:Bauer Kristof
;Azonostio:bkim1790
;Csoportszam 511
;Labor 4 / 2. feladat
;Stringek irasa olvasasa

%include 'mio.inc'

global ReadStr,WriteStr,ReadLnStr,WriteLnStr,NewLine


section .text

ReadStr:
pusha
xor ebx,ebx

.ciklus:
    call    mio_readchar
    cmp     al, 13 ;ha enter leallitja az olvasast
    je      .vege
	cmp     al, 8 ;ha backspace
    je .backspace
	call mio_writechar ;ha nem tortent backspace kiiratja a szamot
	inc ebx ;noveli az aktualis hosszt
	
	cmp ebx,ecx ;ha az aktualis hossz nagyobb mint az ecx-ben megadott akkor mar nem menti el a karaktert
	ja .ciklus ;ujrabeolvas
	
	mov [esi],al ;ha az aktualis hossz < hossz elmentjuk a memoriacimre a karaktert
	inc esi ;noveljuk a memoriacimet
    jmp     .ciklus ;ujrabeolvas
	
	
	.backspace:
	cmp ebx,0 ;ha a hossz az 0 nem torlunk karaktert, ujrahivjuk a ciklust
	je .ciklus
	cmp ebx,ecx ;ha a hossz > aktualis hossz es backspace tortent
	ja .fakeback
	
	dec esi ;letorli a memoriacimet
	jmp .fakeback ;csokkenti az aktualis hosszt es elvegzi a backspace muveletet
	
	.fakeback: ;csokkenti az aktualis hosszt viszont nem torol ki karaktert a memoriabol
	dec ebx
	call    mio_writechar
	mov     al, ' '
    call    mio_writechar
    mov     al, 8
    call    mio_writechar
	jmp .ciklus
    
.vege:
	mov [esi],byte 0 ;vegere bekerul a 0 karakter
	popa
    ret
	
	
WriteStr:
 pusha
  
 .ciklus:
	lodsb ;karakter al-ben || esi++
	cmp al,0 ;ha nincs vege
	jz  .vege
	call mio_writechar
	jmp .ciklus

.vege:
	popa
	ret
	
ReadLnStr:
pusha
xor ebx,ebx

;elvegzi az elobbi beolvasast ugy hogy a vegen meghivja a NewLinet hogy uj sort irjon ki

.ciklus:
    call    mio_readchar
    cmp     al, 13
    je      .vege
	cmp     al, 8
    je .backspace
	call mio_writechar
	inc ebx
	
	cmp ebx,ecx
	ja .ciklus
	
	mov [esi],al
	inc esi
    jmp     .ciklus
	
	
	.backspace:
	cmp ebx,0
	je .ciklus
	cmp ebx,ecx
	ja .fakeback
	
	dec esi
	jmp .fakeback
	
	.fakeback:
	dec ebx
	call    mio_writechar
	mov     al, ' '
    call    mio_writechar
    mov     al, 8
    call    mio_writechar
	jmp .ciklus
    
.vege:
	mov [esi],byte 0
	call NewLine
	popa
    ret
	
WriteLnStr:
 pusha
  ;elvegzi az elobbi kiiratast ugy hogy a vegen meghivja a NewLinet hogy uj sort irjon ki

  
 .ciklus:
	lodsb ;karakter al || esi++
	cmp al,0
	jz  .vege
	call mio_writechar
	jmp .ciklus ;csokkenti a hosszt ecx

.vege:
	call NewLine
	popa
	ret
	
NewLine:
	push eax
	mov eax, 10 ;ujsor kiiratasa
	call mio_writechar
	mov eax, 13 ;carriage return kiiratasa
	call mio_writechar
	pop eax
	ret