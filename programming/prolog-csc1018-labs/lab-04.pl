% Fibonacci numbers
fib(0, 0).
fib(1, 1).
fib(N, R) :-
    N1 is N - 1, N2 is N - 2,
    fib(N1, R1), fib(N2, R2),
    R is R1 + R2.

% Area of a triangle
triangle_area(A, H, R) :- R is A * H * 0.5.

% Factorial
factorial(0, 1).
factorial(N, R) :-
    N > 0,
    N1 is N - 1,
    factorial(N1, R1),
    R is R1 * N.

% Power function
power(_, 0, 1).
power(Base, Exp, Result) :-
    Exp > 0,
    Exp1 is Exp - 1,
    power(Base, Exp1, Result1),
    Result is Base *  Result1.

% Sum of the first N natual numbers
sum_to(0, 0).
sum_to(N, S) :- 
    N > 0,
    N1 is N - 1,
    sum_to(N1, S1),
    S is S1 + N.

% Check if number is even
even(0).
even(N) :-
    N > 0,
    N2 is N - 2,
    even(N2).

% Greatest common divisor
gcd(A, 0, A).
gcd(A, B, GCD) :- 
    B > 0,
    B1 is A mod B,
    gcd(B, B1, GCD).

% Count down from N
count_down(0) :- write(0), nl.
count_down(N) :- 
    N > 0,
    write(N), nl,
    N1 is N - 1,
    count_down(N1).

