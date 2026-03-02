% Facts
% book(Title, Author, Genre, NumberOfPages).
/*
MyLibrary = [
    book(illiad,homer,study,500),book(c,richie,study, 150),
    book(ntbible,sams,reference,480),book(ntfordummies,bob, reference,200),
    book(montypython,comedy,300), book(pythonalgorithms,david,study, 225),
    book(masacre,dillenger,crime,180), book(lilacbus,binchey,fiction,200)
].
*/

% Relationships
holiday(_, []).
holiday(book(HT, HA, _, _), [book(Title, Author, Genre, NumberOfPages)|_]) :-
    HT = Title, HA = Author, NumberOfPages < 400, Genre \== study, Genre \== reference.
holiday(Book, [_|Tail]) :- holiday(Book, Tail).

revision(_, []).
revision(book(HT, HA, _, _), [book(Title, Author, Genre, NumberOfPages)|_]) :-
    HT = Title, HA = Author, NumberOfPages > 300, (Genre == study ; Genre == reference).
revision(Book, [_|Tail]) :- revision(Book, Tail).

literary(_, []).
literary(book(HT, HA, _, _), [book(Title, Author, Genre, _)|_]) :-
    HT = Title, HA = Author,  Genre == drama.
literary(Book, [_|Tail]) :- literary(Book, Tail).

leisure(_, []).
leisure(book(HT, HA, _, _), [book(Title, Author, Genre, _)|_]) :-
    HT = Title, HA = Author, (Genre == comedy ; Genre == fiction).
leisure(Book, [_|Tail]) :- leisure(Book, Tail).

