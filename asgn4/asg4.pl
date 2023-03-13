
% /∗
% ∗ CSCI3180 Principles of Programming Languages
% ∗
% ∗ --- Declaration --- 
% ∗
% ∗ I declare that the assignment here submitted is original except for source
% ∗ material explicitly acknowledged. I also acknowledge that I am aware of
% ∗ University policy and regulations on honesty in academic work, and of the
% ∗ disciplinary guidelines and procedures applicable to breaches of such policy
% ∗ and regulations, as contained in the website
% ∗ http://www.cuhk.edu.hk/policy/academichonesty/ 
% ∗
% ∗ Assignment 4
% ∗ Name : ZHANG Jingze
% ∗ Student ID : 1155107857
% ∗ Email Addr : jzzhang8@cse.cuhk.edu.hk 
% ∗/

% part 1

element_last(X,[X]).
element_last(X,[_|L]):- element_last(X,L).

% element_n(X,L,N)
element_n(X,[X|_],s(0)).
element_n(X,[_|L],s(N)):- element_n(X,L,N).


% remove_n(X,L1,N,L2)
remove_n(X,[X|R],s(0),R).
remove_n(X,[H|L1],s(N),[H|L2]):- remove_n(X,L1,N,L2).

% insert_n(X,L1,N,L2)
insert_n(X,L1,N,L2):- remove_n(X,L2,N,L1).

% repeat_three(L1,L2)
repeat_three([],[]).
repeat_three([H|L1],[H,H,H|L2]):- repeat_three(L1,L2).


% part 2

mt(e,[]).
mt(f,[]).
mt(c,[]).
mt(g,[]).
mt(b,[mt(e,E),mt(f,F)]):- mt(e,E),mt(f,F).
mt(d,[mt(g,G)]):- mt(g,G).
mt(a,[mt(b,B),mt(c,C),mt(d,D)]):- mt(b,B),mt(c,C),mt(d,D).



% is_tree(mt(X,F))
is_tree(mt(X,Y)):- mt(X,Y).

% sum from lecture
sum(0,X,X).
sum(s(X),Y,s(Z)):- sum(X,Y,Z).

% num_node(Tree,N)

list_num_sum([mt(_,[])],s(0)).
list_num_sum([mt(_,L)],R):- list_num_sum(L,R1),sum(s(0),R1,R).
list_num_sum([H|T],R):- list_num_sum([H],R1),list_num_sum(T,R2),sum(R1,R2,R).
num_node(mt(_,[]),s(0)).
num_node(mt(_,L),R):- list_num_sum(L,R1),sum(R1,s(0),R).

% sum_length(Tree,L)
% the second parameter is the depth of this node named D
list_num_height([mt(_,[])],D,D).
list_num_height([mt(_,L)],D,R):- sum(D,s(0),D1),list_num_height(L,D1,R1),sum(D,R1,R).
list_num_height([H|T],D,R):- list_num_height([H],D,R1),list_num_height(T,D,R2),sum(R1,R2,R).
sum_length(mt(_,[]),0).
sum_length(mt(_,L),R):- list_num_height(L,s(0),R).


























