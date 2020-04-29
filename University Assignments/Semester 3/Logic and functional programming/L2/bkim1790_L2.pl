randperm(0,_).
randperm(N, L):-
  findall(Num, between(1, N, Num), S),
  perm(S,N,L).

perm([],0,[]).
perm([H],1,[H2|T]):-
  H2 is H,
  perm([],0,T).

perm(List,N,[H|T]):-
  N>=2,
  random(1,N,R),
  nth1(R,List,H),
  delete(List,H,List2),
  N1 is N-1,
  perm(List2,N1,T).


derivalt(Kif,L):-
  d(Kif,x,L).

d(X,X,1) :-
  !.
d(C,_,0) :-
  atomic(C).

d(U+V,X,A+B) :-
  d(U,X,A),
  d(V,X,B).
d(U-V,X,A-B) :-
  d(U,X,A),
  d(V,X,B).
d(U*V,X,DU*V+U*DV) :-
  d(U,X,DU),
  d(V,X,DV).
d(U/V,X,(DU*V-U*DV)/(V*V)) :-
  d(U,X,DU),
  d(V,X,DV).

d(sin(U+V),X,cos(U+V)*(A+B)):-
  d(U,X,A),
  d(V,X,B).

d(cos(U+V),X,-sin(U+V)*(A+B)):-
  d(U,X,A),
  d(V,X,B).

d(sin(U-V),X,cos(U-V)*(A-B)):-
  d(U,X,A),
  d(V,X,B).

d(cos(U-V),X,-sin(U-V)*(A-B)):-
  d(U,X,A),
  d(V,X,B).

d(sin(U*V),X,cos(U*V)+(DU*V+U*DV)) :-
  d(U,X,DU),
  d(V,X,DV).

d(cos(U*V),X,-sin(U*V)+(DU*V+U*DV)) :-
  d(U,X,DU),
  d(V,X,DV).

d(sin(U/V),X,cos(U/V)*((DU*V-U*DV)/(V*V))) :-
  d(U,X,DU),
  d(V,X,DV).

d(cos(U/V),X,-sin(U/V)*((DU*V-U*DV)/(V*V))) :-
  d(U,X,DU),
  d(V,X,DV).


lsort(L1,L2):-
  maplist(list_pair,L1, Pot),
  keysort(Pot, Pairs2),
  listaSort(Pairs2,L2).


listaSort([],[]).
listaSort([_-List | T], [List|T2]):-
 listaSort(T,T2).

list_pair(Ls, L-Ls) :-
        length(Ls, L).

elott(X):-
  movie(X,Y),
  between(0,1979,Y).

kozott(X):-
   director(MNev,X),
   movie(MNev,MKijott),
   between(2000,2005,MKijott).

ugyanabban(EgyFilm,MasikFilm):-
  movie(EgyFilm,EgyIdo),
  movie(MasikFilm,MasikIdo),
  EgyFilm \= MasikFilm,
  EgyIdo=MasikIdo.

joPartnerek(F,Sz):-
	(actor(F,Sz,_);actress(F,Sz,_)).

joPartner(Sz1,Sz2):-
	joPartnerek(F1,Sz1),
	joPartnerek(F1,Sz2),
	joPartnerek(F2,Sz1),
	joPartnerek(F2,Sz2),
	Sz1\=Sz2,
	F1\=F2.


isactor(SZ):-
    actor(_,SZ,_);
    actress(_,SZ,_).

kulonbozoSzinesz(DB):-
    findall(SZ,isactor(SZ),L),
    list_to_set(L,L2),
    length(L2,DB).


favorit(L):-
    setof((SZ1,N),kulonbozoJopartner(SZ1,N),L1),
    sort(2,@>=,L1,R),
    append(L,_,R),
    length(L,25),
    !.

kulonbozoJopartner(SZ1,N):-
	setof(SZ2,joPartner(SZ1,SZ2),L),
	length(L,N).













