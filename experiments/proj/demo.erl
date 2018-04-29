-module(demo).
-export([convert/2]).
-export([double/1]).
-export([times/2]).
-export([factorial/1]).
-export([list_length/1]).

convert(M, inch) ->
	M / 2.54;
convert(N, centimeter) ->
	N * 2.54.
double(N) ->
	times(N, 2).

list_length([]) ->
	0;
list_length([First | Rest]) ->
	1 + list_length(Rest).
times(A, B) ->
	A * B.

factorial(0) -> 1;
factorial(1) -> 1;
factorial(2) -> 2;
factorial(3) -> 6;
factorial(N) -> N * factorial(N-1).
