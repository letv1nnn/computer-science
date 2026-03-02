% Facts
% parents(child, father, mother).
parents(david, george, noreen).
parents(jennifer, george, noreen).
parents(georgejr, george, noreen).
parents(scott, george, noreen).
parents(joanne, george, noreen).
parents(jessica, david, edel).
parents(clara, david, edel).
parents(michael, david, edel).
parents(laura, georgejr, susan).
parents(anna, scott, siobhan).

% Relationships
father(X, Y) :- parents(Y, X, _).
mother(X, Y) :- parents(Y, _, X).

male(X) :- father(X, _).
female(X) :- mother(X, _).

grandfather(X, Y) :-
    father(X, Z),
    (father(Z, Y) ; mother(Z, Y)).

grandmother(X, Y) :-
    mother(X, Z),
    (father(Z, Y) ; mother(Z, Y)).

sibling(X, Y) :-
    parents(X, F, M),
    parents(Y, F, M),
    X \= Y.

brother(X, Y) :-
    sibling(X, Y),
    male(X).

sister(X, Y) :-
    sibling(X, Y),
    female(X).

uncle(X, Y) :- 
    male(X),
    parents(Y, F, M),
    (sibling(F, X) ; sibling(M, X)).

aunt(X, Y) :-
    female(X),
    parents(Y, F, M),
    (sibling(F, X) ; sibling(M, X)).

cousin(X, Y) :-
    parents(X, F1, M1),
    parents(Y, F2, M2),
    (sibling(F1, F2) ;
        sibling(M1, M2) ;
        sibling(F1, M1) ;
        sibling(F2, M2) ;
        sibling(F1, M2) ;
        sibling(F2, M1)
    ).

