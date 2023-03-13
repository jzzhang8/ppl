
# /∗
# ∗ CSCI3180 Principles of Programming Languages
# ∗
# ∗ --- Declaration --- 
# ∗
# ∗ I declare that the assignment here submitted is original except for source
# ∗ material explicitly acknowledged. I also acknowledge that I am aware of
# ∗ University policy and regulations on honesty in academic work, and of the
# ∗ disciplinary guidelines and procedures applicable to breaches of such policy
# 
# ∗ and regulations, as contained in the website
# ∗ http://www.cuhk.edu.hk/policy/academichonesty/ 
# ∗
# ∗ Assignment 3
# ∗ Name : ZHANG Jingze
# ∗ Student ID : 1155107857
# ∗ Email Addr : jzzhang8@cse.cuhk.edu.hk 
# ∗/

use strict;
use warnings;
 
package Player;
sub new {
	my $class = shift @_;
	my $self = {
		name => shift @_,
		cards => []
	};
	return bless $self, $class;
}

sub getCards {
	my $self = shift @_;
	my $cards = shift @_;
	for my $card (@$cards){
		push @{$self->{cards}}, $card;	
	}	
}

sub dealCards {
	my $self = shift @_;
	my $card = shift @{$self->{cards}};
	return $card;
}

sub numCards {
	my $self = shift @_;
	my @cards = @{$self->{cards}};
	my $cards_num = @cards;
	return $cards_num;
}

return 1;