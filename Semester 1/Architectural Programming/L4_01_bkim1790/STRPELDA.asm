;Nev:Bauer Kristof
;Azonostio:bkim1790
;Csoportszam 511
;Labor 4 / 4. feladat
;Mindkét stringnek kiírjuk a hosszát, kompaktált formáját, majd a kompaktált formát kis betűkre alakítva és nagy betűkre alakítva. 
;Végül hozzáfűzzük az első string nagybetűs verziójához a második string kisbetűs verzióját és kiírjuk a hosszával együtt.

%include 'IOSTR.INC'
%include 'STRINGS.INC'
%include 'IONUM.inc'
%include 'mio.inc'

global main
 
section .text



main:	

	;beolvas elso string
	mov esi,bestring1
	call WriteStr
	mov esi,s1
	mov ecx,256
	call ReadLnStr
	
	;megnezi az elso string hosszat
	mov esi,hossz1
	call WriteStr
	mov esi,s1
	call StrLen
	call WriteInt ;eaxben van a hossz es kiirja
	call mio_writeln
	
	;kiírjuk a tömörített formáját;
	mov esi,kompakt1
	call WriteStr
	mov edi,kompakts1 ;edibe bekerul a kompakt string1
	mov esi,s1
	call StrCompact
	mov esi,kompakts1
	call WriteLnStr
	
	;kiírjuk a tömörített formáját kisbetűkre alakítva;
	mov esi,kisbetu1
	call WriteStr
	mov esi,kompakts1
	call StrLower
	mov esi,kompakts1
	call WriteLnStr
	
	;beolvas masodik string
	mov esi,bestring2
	call WriteStr
	mov esi,s2
	mov ecx,256
	call ReadLnStr
	
	;masodik string hossza
	mov esi,hossz2
	call WriteStr
	mov esi,s2
	call StrLen
	call WriteInt ;eaxben van a hossz es kiirja
	call mio_writeln
	
	;masodik string tomoritett formaja
	mov esi,kompakt2
	call WriteStr
	mov edi,kompakts2 ;edibe bekerul a masodik string kompaktja
	mov esi,s2 ;esibe bekerul a masodik string
	call StrCompact
	mov esi,kompakts2
	call WriteLnStr
	
	;masodik string tomoritett formaja nagybetukre
	mov esi,nagybetu2
	call WriteStr
	mov esi,kompakts2
	call StrUpper
	mov esi,kompakts2
	call WriteLnStr
	
	;elso string nagybetukkel
	mov esi,s1
	call StrUpper
	
	;masodik string kisbetukkel
	mov esi,s2
	call StrLower
	
	;osszefuz db 'Elso string kisbetu + Masodik string nagybetu: ',0
	mov esi,osszefuz
	call WriteStr
	mov edi,s3 ;az ures stringet osszefuzzuk az s1 stringgel
	mov esi,s1
	call StrCat
	
	mov edi,s3 ;az s1 stringet osszefuzi az s2 stringgel az eredemeny az uj s3 stringben
	mov esi,s2
	call StrCat
	mov esi,s3
	call WriteLnStr
	
	;letrehozott string hossza
	mov esi,hossz3
	call WriteStr
	mov esi,s3
	call StrLen
	call WriteInt ;eaxben van a hossz es kiirja
	call mio_writeln
	
	ret

section .data
bestring1 db 'Add meg az elso stringet: ', 0
bestring2 db 'Add meg a masodik stringet: ',0
hossz1 db 'Az elso string hossza: ',0
hossz2 db 'A masodik string hossza: ',0
hossz3 db 'Az osszefuzott string hossza: ',0
kompakt1 db 'Az elso string kompakt alakja: ',0
kompakt2 db 'A masodik string kompakt alakja: ',0
kisbetu1 db 'Az elso string kompakt alakja kisbetukkel: ',0
nagybetu2 db 'A masodik string kompakt alakja nagybetukkel: ',0
osszefuz db 'Elso string kisbetu + Masodik string nagybetu: ',0


section .bss
s1 resb 256
s2 resb 256
s3 resb 256
kompakts1 resb 256
kompakts2 resb 256