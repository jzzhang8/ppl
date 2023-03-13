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