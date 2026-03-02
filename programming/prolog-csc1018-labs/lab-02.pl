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

holiday(_, []).
holiday(book(HT, HA, _, _), [book(Title, Author, Genre, NumberOfPages)|_]) :-
    HT = Title, HA = Author, NumberOfPages < 400, Genre \== study, Genre \== reference.
holiday(Book, [_|Tail]) :- holiday(Book, Tail).

