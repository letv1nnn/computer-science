% Working with lists and recursion

% Relations
% This relation is true if X is and element of list A.
my_elem(El, [El|_]).
my_elem(El, [_|Tail]) :- my_elem(El, Tail).

% This relation is true if X is the first element of list A.
my_head(El, [El|_]).

% This relation is true if X is the last element of list A.
my_last(El, [El]).
my_last(El, [_|Tail]) :- my_last(El, Tail).

% This relation is true if list A is the tail of list B.
my_tail(L, [_|L]).

% This relation is true if list C is list B appended to the end of list A.
my_append([], L, L).
my_append([X|XS], Y, [X|Z]) :- my_append(XS, Y, Z).

% This relation is true if list A is the reverse of list B.
my_reverse([], []).
my_reverse([X|XS], Y) :- my_reverse(XS, R), my_append(R, [X], Y).

% This relation is true if list B is list A with the first occurence of X removed.
my_delete(X,[X|L1],L1).
my_delete(X,[Y|L1],[Y|L2]) :- my_delete(X,L1,L2).

