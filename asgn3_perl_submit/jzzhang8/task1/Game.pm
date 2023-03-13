
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

package Game;
use MannerDeckStudent; 
use Player;

sub new {
	my $class = shift @_;
	my $self = {};
	$self->{deck} = MannerDeckStudent->new();
	$self->{players} = [];
	$self->{cards} = [];
	return bless $self, $class;
}

sub setPlayers {
	my $self = shift @_;
	my $player_names = shift @_;
	for my $name (@$player_names){
		my $player = Player->new($name);	
		push @{$self->{players}}, $player;
	}
	return 1;
}

sub getReturn {
	my $self = shift @_;
	my $cards_ref = $self->{cards};
	my @cards = @$cards_ref;
	my $cards_num = @cards;
	my $last_card = $cards[$cards_num-1];

	if($last_card eq "J"){
		if($cards_num == 1){
			return 0;
		}else{
			return $cards_num;
		}
	}

	for my $idx (1 .. $cards_num - 1){
		if($cards_ref->[$cards_num -1 - $idx] eq $last_card){
			return $idx+1;
		}
	}

	return 0;

}

sub showCards {
	my $self = shift @_;
	my @cards = @{$self->{cards}};
	return @cards;
}

sub startGame {
	my $self = shift @_;

	my $deck = $self->{deck};
	my $player_num = @{$self->{players}};
	my $players = $self->{players};
	my $card_num_each  = 52 / $player_num;
	if(52 % $player_num != 0){
		print "Error: cards' number 52 can not be divided by players number ",$player_num,"!\n";
		return;
	}
	$deck->shuffle();
	print "There ",$player_num," players in the game:\n";
	for my $each_player (@$players){
		print $each_player->{name}," ";
	}
	print "\n\n";

	print "Game begin!!!\n\n";
	my @player_decks = $deck->AveDealCards($player_num);
	for my $deck_idx (0..$player_num-1){
		my $deck_ref = $player_decks[$deck_idx];
		my $this_player = $players->[$deck_idx];
		$this_player->getCards($deck_ref);
	}


	my $turn_num = 0;
	my $curr_player;
	my $game_num = 0;
	my $out_num = 0;
	while(1){

		if($out_num == $player_num-1){
			for my $each_player (@$players){
				if($each_player->numCards() != 0){
					print "Winner is ",$each_player->{name}," in game ",$game_num,"\n";
					goto ENDOFLOOP;
				}
			}
		}

		$curr_player = $players->[$turn_num % $player_num];
		if($turn_num % $player_num == 0){
			$game_num += 1;
		}
		if($curr_player->numCards() == 0){
			$turn_num = $turn_num + 1;
			next;
		}
		print "Player ",$curr_player->{name}," has ",$curr_player->numCards()," cards before deal.\n";
		print "=====Before player's deal=======\n";
		print join " ", @{$self->{cards}};
		print "\n";
		print "================================\n";

		# print join " ","curr before cards: ", @{$curr_player->{cards}},"\n";
		my $dealt_card = $curr_player->dealCards();
		print $curr_player->{name}," ==> card ",$dealt_card,"\n";
		

		push @{$self->{cards}}, $dealt_card;
		my $return_num = $self->getReturn();
		# print "return num: ",$return_num,"\n";
		my $get_cards = [];
		for my $_num (1..$return_num){
			my $one_card = pop @{$self->{cards}};
			push @$get_cards, $one_card;
		}
		$curr_player->getCards($get_cards);
		# print join " ","curr after cards: ", @{$curr_player->{cards}},"\n";

		print "=====After player's deal=======\n";
		print join " ", @{$self->{cards}};
		print "\n";
		print "================================\n";
		print "Player ",$curr_player->{name}," has ",$curr_player->numCards()," cards after deal.\n";
		if($curr_player->numCards() == 0){
			print "Player ",$curr_player->{name}," has no cards, out!\n";
			$out_num += 1;
		}
		print "\n";
		$turn_num = $turn_num + 1;
		
	}
	ENDOFLOOP:

}




return 1;
