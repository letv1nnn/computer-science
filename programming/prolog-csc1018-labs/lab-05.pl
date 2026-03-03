% Confirmation of Choice of Rule
% library patrons
client(alice).
client(bob).
book_overdue(bob, book101).

% library facilities
general_facility(X) :- basic_facility(X).
general_facility(X) :- additional_facility(X).
additional_facility(borrowing).
additional_facility(inter_library_loan).
basic_facility(references).
basic_facility(enquires).

facility(Person, Facility) :-
    book_overdue(Person),
    !,
    basic_facility(Facility).

facility(_, Facility) :-
    general_facility(Facility).

% Preventing Additional Solutions
% without cuts
sum_one_to(1, 1).
sum_one_to(N, S) :-
    N > 1,
    N1 is N - 1,
    sum_one_to(N1, S1),
    S is S1 + N.

% OR
sum_one_to2(1, 1) :- !.
sum_one_to2(N, S) :-
    N1 is N - 1,
    sum_one_to2(N1, S1),
    S is S1 + N.

% Write a Prolog relation class(X,Y) that classifies a number X into a category Y,
% where Y is either negative, zero or positive. Use cuts to make it more efficient. 
class(0, zero) :- !.
class(N, positive) :- N > 0, !.
class(N, negative) :- N < 0, !.

% Write a Prolog relation split(Numbers, Positive, Negative) that is true if all the
% positive numbers (including 0) in the list N are in the list Positive, and all the
% negative numbers in the list N are in the list Negative.
split([], [], []).
split([X|XS], [X|PS], N) :- X >= 0, !, split(XS,PS,N).
split([X|XS], P, [X|NS]) :- !, split(XS,P,NS).

