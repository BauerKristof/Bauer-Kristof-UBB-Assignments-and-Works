%Bauer Kristof
%521


dupla([], []).
dupla([H | T1], [H, H | T2]) :-
    dupla(T1, T2).

kszor(_,[],[]).
kszor(K,[H1|T1],Lista):-
    findall(H1, between(1, K, _), L),
    kszor(K,T1,Seged),
    append(L,Seged,Lista).

osszead([],OSSZ):-OSSZ is 0.
osszead([H|T],OSSZ):-
    osszead(T,X),
    OSSZ is H+X.

gen(A,A,[L]):-L is A.
gen(A,B,[A|T]):-
    A1 is A+1,
    gen(A1,B,T).

%findall(X, between(1, 18000, X), Xs), inverz(Xs,L).
inverz([],[]).
inverz([H|T],L1):-
     inverz(T,L2),
     append(L2,[H],L1).


torolk(Lista,K,ErLista):-
    torolk(Lista,K,0,ErLista).
torolk([],_,_,[]).
torolk([_],_,_,[]).
torolk([_|T1],K,I,[H2|T2]):-
    SI is I+1,
    K=SI,
    torolk(T1,K,0,[H2|T2]).

torolk([H1|T1],K,I,[H2|T2]):-
    SI is I+1,
    H2 is H1,
    torolk(T1,K,SI,T2).


is_permutation(Xs, Ys) :-
  msort(Xs, Sorted),
  msort(Ys, Sorted).

perm(L):-
   length(L,N),
   gen(1,N,UList),
   is_permutation(L,UList).

kompakt(L1,L2):-
    kompakt(L1,1,L2).

kompakt([],_,[]).
kompakt([H], Szamlalo, [[H,Szamlalo]]).

kompakt([H,H|T],Szamlalo,L):-
    SZ is Szamlalo+1,
    kompakt([H|T],SZ,L).

%kompakt([H1,H2|T],Szamlalo,[H1|T2]):-
%   dif(H1,H2),
%   Szamlalo=1,
%   kompakt([H2|T],1,T2).

kompakt([H1,H2|T],Szamlalo,[[H1,Szamlalo]|T2]):-
   dif(H1,H2),
   kompakt([H2|T],1,T2).

megoldas(L):-
    digit(S),
    S>0,
    digit(E),
    digit(N),
    digit(D),
    digit(M),
    M>0,
    digit(O),
    digit(R),
    digit(Y),
    1000*S+100*E+10*N+D+1000*M+100*O+10*R+E=:=10000*M+1000*O+100*N+10*E+Y,
    L=[S,E,N,D,M,O,R,Y],
    different(L).

digit(0).
digit(1).
digit(2).
digit(3).
digit(4).
digit(5).
digit(6).
digit(7).
digit(8).
digit(9).

different([]).
different([X|R]):-
    not(member(X,R)),
    different(R).

szinesz(X) :-
    actor(_, X, _).

szinesz(X) :-
    actress(_, X, _).

csakegy(Szinesz) :-
    actor(_, Szinesz, _),
    not(min2_actor(Szinesz)).

csakegy(Szinesz) :-
    actress(_, Szinesz, _),
    not(min2_actress(Szinesz)).

min2_actor(Szinesz) :-
    movie(Film1, _),
    movie(Film2, _),
    Film1 \= Film2,
    actor(Film1, Szinesz, _),
    actor(Film2, Szinesz, _).

min2_actress(Szinesz) :-
    movie(Film1, _),
    movie(Film2, _),
    Film1 \= Film2,
    actress(Film1, Szinesz, _),
    actress(Film2, Szinesz, _).

pontosan_ketto(Szinesz) :-
    actor(_, Szinesz, _),
    not(tobb3_actor(Szinesz)),
    min2_actor(Szinesz).

pontosan_ketto(Szinesz) :-
    actress(_,Szinesz,_),
    not(tobb3_actress(Szinesz)),
    min2_actress(Szinesz).


tobb3_actor(Szinesz) :-
    movie(Film1, _),
    movie(Film2, _),
    movie(Film3, _),
    Film1 \= Film2,
    Film1 \= Film3,
    Film2 \= Film3,
    actor(Film1, Szinesz, _),
    actor(Film2, Szinesz, _),
    actor(Film3, Szinesz, _).

tobb3_actress(Szinesz) :-
     movie(Film1, _),
    movie(Film2, _),
    movie(Film3, _),
    Film1 \= Film2,
    Film1 \= Film3,
    Film2 \= Film3,
    actress(Film1, Szinesz, _),
    actress(Film2, Szinesz, _),
    actress(Film3, Szinesz, _).



egyfilmbensem(Szinesz) :-
    actor(_, Szinesz, '').

egyfilmbensem(Szinesz) :-
    actress(_, Szinesz,'').
















