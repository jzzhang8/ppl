(* /∗
∗ CSCI3180 Principles of Programming Languages 
∗
∗ --- Declaration --- 
∗
∗ I declare that the assignment here submitted is original except for source
∗ material explicitly acknowledged. I also acknowledge that I am aware of
∗ University policy and regulations on honesty in academic work, and of the
∗ disciplinary guidelines and procedures applicable to breaches of such policy
∗ and regulations, as contained in the website
∗ http://www.cuhk.edu.hk/policy/academichonesty/ 
∗
∗ Assignment 4
∗ Name : ZHANG Jingze
∗ Student ID : 1155107857
∗ Email Addr : jzzhang8@cse.cuhk.edu.hk 
∗/ *)


datatype suit = Clubs | Diamonds | Hearts | Spades;
datatype hand = 
Nothing | Pair | Two_Pairs | Three_Of_A_Kind | Full_House | Four_Of_A_Kind | Flush | Straight;

fun check_flush([(Clubs,_),(Clubs,_),(Clubs,_),(Clubs,_),(Clubs,_)]: (suit * int) list) = true : bool |
check_flush([(Diamonds,_),(Diamonds,_),(Diamonds,_),(Diamonds,_),(Diamonds,_)]) = true : bool |
check_flush([(Hearts,_),(Hearts,_),(Hearts,_),(Hearts,_),(Hearts,_)]) = true : bool |
check_flush([(Spades,_),(Spades,_),(Spades,_),(Spades,_),(Spades,_)]) = true : bool |
check_flush([(_,_),(_,_),(_,_),(_,_),(_,_)]) = false : bool;



fun compare_flush([] : (suit * int) list,[] : (suit * int) list) : string = "This is a tie" |
compare_flush((_,hn1)::t1 : (suit * int) list, (_,hn2)::t2 : (suit * int) list) : string = if hn1 = hn2 then compare_flush(t1,t2)
else (if hn2 < hn1 then "Hand 1 wins" else "Hand 2 wins");


fun check_straight([(_,5),(_,4),(_,3),(_,2),(_,1)] : (suit * int) list) : bool = true |
check_straight([(_,6),(_,5),(_,4),(_,3),(_,2)]) : bool = true |
check_straight([(_,7),(_,6),(_,5),(_,4),(_,3)]) : bool = true |
check_straight([(_,8),(_,7),(_,6),(_,5),(_,4)]) : bool = true |
check_straight([(_,9),(_,8),(_,7),(_,6),(_,5)]) : bool = true |
check_straight([(_,10),(_,9),(_,8),(_,7),(_,6)]) : bool = true |
check_straight([(_,11),(_,10),(_,9),(_,8),(_,7)]) : bool = true |
check_straight([(_,12),(_,11),(_,10),(_,9),(_,8)]) : bool = true |
check_straight([(_,13),(_,12),(_,11),(_,10),(_,9)]) : bool = true |
check_straight([(_,13),(_,12),(_,11),(_,10),(_,1)]) : bool = true |
check_straight([(_,_),(_,_),(_,_),(_,_),(_,_)]) : bool = false;


fun compare_straight([(_,13),(_,12),(_,11),(_,10),(_,1)] : (suit * int) list,[(_,13),(_,12),(_,11),(_,10),(_,1)] : (suit * int) list) : string = "This is a tie" |
	compare_straight([(_,13),(_,12),(_,11),(_,10),(_,1)],[(_,_),(_,_),(_,_),(_,_),(_,_)]) = "Hand 1 wins" |
	compare_straight([(_,_),(_,_),(_,_),(_,_),(_,_)],[(_,13),(_,12),(_,11),(_,10),(_,1)]) = "Hand 2 wins" |
	compare_straight((hs1,hn1)::t1,(hs2,hn2)::t2) = if hn1 = hn2 then "This is a tie" 
		else (if hn1 > hn2 then "Hand 1 wins" else "Hand 2 wins");


fun four_of_a_kind_pre([a,b,c,d,e] : int list) : bool = if a = b andalso a = c andalso a = d then true 
else (if b = c andalso b = d andalso b = e then true else false);
fun four_of_a_kind([(_,a),(_,b),(_,c),(_,d),(_,e)] : (suit * int) list)  : bool= four_of_a_kind_pre([a,b,c,d,e]);


fun full_house_pre([a,b,c,d,e] : int list) : bool = if (a = b andalso a = c andalso d = e) orelse (a = b andalso c = d andalso c = e) then true
else false;
fun full_house([(_,a),(_,b),(_,c),(_,d),(_,e)] : (suit * int) list) : bool = full_house_pre([a,b,c,d,e]);

fun three_of_a_kind_pre([a,b,c,d,e] : int list) : bool = if four_of_a_kind_pre([a,b,c,d,e]) orelse full_house_pre([a,b,c,d,e]) then false 
else (if (a = b andalso a = c) orelse (b = c andalso b = d) orelse (c = d andalso c = e) then true else false);
fun three_of_a_kind([(_,a),(_,b),(_,c),(_,d),(_,e)] : (suit * int) list) : bool = four_of_a_kind_pre([a,b,c,d,e]);

fun two_pairs_pre([a,b,c,d,e] : int list) : bool = if four_of_a_kind_pre([a,b,c,d,e]) then false
else (if (a = b andalso c = d) orelse (a = b andalso d = e) orelse (b = c andalso d = e) then true else false);
fun two_pairs([(_,a),(_,b),(_,c),(_,d),(_,e)] : (suit * int) list) : bool = two_pairs_pre([a,b,c,d,e]);

fun pair_pre([a,b,c,d,e] : int list) : bool = if three_of_a_kind_pre([a,b,c,d,e]) orelse two_pairs_pre([a,b,c,d,e]) then false
else (if a = b orelse b = c orelse c = d orelse d =e then true else false);
fun pair([(_,a),(_,b),(_,c),(_,d),(_,e)] : (suit * int) list) : bool = pair_pre([a,b,c,d,e]);

fun count_patterns([(_,a),(_,b),(_,c),(_,d),(_,e)] : (suit * int ) list ) : hand * (int * int) list = 
if four_of_a_kind_pre([a,b,c,d,e]) then (if a = b then (Four_Of_A_Kind,[(a, 4),(e, 1)]) else (Four_Of_A_Kind,[(b, 4),(a, 1)]))
else if full_house_pre([a,b,c,d,e]) then (if b = c then (Full_House,[(b, 3),(d, 2)]) else (Full_House,[(b, 2),(d, 3)]))
else if three_of_a_kind_pre([a,b,c,d,e]) then (if a = b andalso b = c then (Three_Of_A_Kind,[(a,3),(d,1),(e,1)])
											   else if b = c andalso c = d then (Three_Of_A_Kind,[(b,3),(a,1),(e,1)])
											   else  (Three_Of_A_Kind,[(c,3),(a,1),(b,1)]))
else if two_pairs_pre([a,b,c,d,e]) then (if a = b andalso c = d then (Two_Pairs,[(a,2),(c,2),(e,1)])
										 else if a = b andalso d = e then (Two_Pairs,[(a,2),(d,2),(c,1)])
										 else (Two_Pairs,[(b,2),(d,2),(a,1)]))
else if pair_pre([a,b,c,d,e]) then (if a = b then (Pair,[(a,2),(c,1),(d,1),(e,1)])
									else if b = c then (Pair,[(b,2),(a,1),(d,1),(e,1)])
									else if c = d then (Pair,[(c,2),(a,1),(b,1),(e,1)])
								    else (Pair,[(d,2),(a,1),(b,1),(c,1)]))
else (Nothing,[(a,1),(b,1),(c,1),(d,1),(e,1)]);


fun compare_rank([] : (int * int) list,[] : (int * int) list) : string = "This is a tie" |
compare_rank((r1,_)::t1,(r2,_)::t2) = if r1 = r2 then compare_rank(t1,t2) 
else if r1 > r2 then "Hand 1 wins"
else "Hand 2 wins";

fun hand_num(Nothing : hand) : int = 1 |
hand_num(Pair) : int = 2 | 
hand_num(Two_Pairs) : int = 3 | 
hand_num(Three_Of_A_Kind) : int = 4 | 
hand_num(Full_House) : int = 5 | 
hand_num(Four_Of_A_Kind) : int = 6 |
hand_num(_) : int = 0; 

fun compare_hand(h1 : hand , h2 : hand) : bool = hand_num(h1) > hand_num(h2);

fun compare((h1,l1) : hand * (int * int) list ,(h2,l2) : hand * (int * int) list) : string = if h1 = h2 then compare_rank(l1,l2) 
else (if compare_hand(h1,h2) then "Hand 1 wins" else "Hand 2 wins");

fun compare_count(l1 : (suit * int) list,l2 : (suit * int) list) : string = compare(count_patterns(l1),count_patterns(l2));




