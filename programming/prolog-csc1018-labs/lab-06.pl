% Sudoku Solver
digit(1).
digit(2).
digit(3).
digit(4).
digit(5).
digit(6).
digit(7).
digit(8).
digit(9).
digit(0).

% Entry point
sudoku(Board) :- solve(Board).

% Solve by filling blanks
solve([]).
solve([Row|Rest]) :-
    solve_row(Row),
    solve(Rest).

solve_row([]).
solve_row([Cell|Rest]) :-
    nonvar(Cell),
    solve_row(Rest).
solve_row([Cell|Rest]) :-
    var(Cell),
    digit(Cell),
    valid_move(Cell, Rest),
    solve(Rest).

% Check valid row
valid_move(_, Row) :- no_duplicates(Row).

no_duplicates([]).
no_duplicates([H|T]) :-
    var(H),
    !,
    no_duplicates(T).
no_duplicates([H|T]) :-
    \+ member(H, T),
    no_duplicates(T).

% Full board validation
sudoku_valid(Board) :-
    rows_valid(Board),
    columns_valid(Board),
    blocks_valid(Board).

% Rows valid
rows_valid([]).
rows_valid([Row|Rest]) :-
    no_duplicates(Row),
    rows_valid(Rest).

% Columns valid
columns_valid(Board) :-
    transpose(Board, TBoard),
    rows_valid(TBoard).

transpose([], []).
transpose([[]|_], []).
transpose(Matrix, [Row|Rows]) :-
    maplist(head_tail, Matrix, Row, RestMatrix),
    transpose(RestMatrix, Rows).

head_tail([H|T], H, T).

% Blocks valid
blocks_valid(Board) :-
    Board = [A,B,C,D,E,F,G,H,I],
    blocks(A,B,C),
    blocks(D,E,F),
    blocks(G,H,I).

blocks([], [], []).
blocks([A,B,C|R1],
       [D,E,F|R2],
       [G,H,I|R3]) :-
    no_duplicates([A,B,C,D,E,F,G,H,I]),
    blocks(R1, R2, R3).

