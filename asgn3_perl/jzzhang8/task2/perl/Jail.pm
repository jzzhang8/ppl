
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
require "./Player.pm";

package Jail;
sub new {
    my $class = shift;
    my $self  = {};
    bless $self, $class;
    return $self;
}

sub print {
    print("Jail ");
}

sub stepOn {

    # ...
    my $self = shift @_;

    print "Pay \$1000 to reduce the prison round to 1? [y/n]\n";
    my $buy = 0;
    while(1){
        my $ans = <STDIN>;
        if($ans eq "y\n"){
            $buy = 1;
            last;
        }elsif($ans eq "n\n"){
            last;
        }else{
            print "Pay \$1000 to reduce the prison round to 1? [y/n]\n";
        } 
    }

    local $Player::handling_fee_rate = 0;
	local $Player::prison_rounds = 2;
	local $Player::due = 0;
    if($buy){
    	if($main::cur_player->{money} < 1000 * (1 + 0.1)){
    		print "You do not have enough money to reduce the prison round!\n";
     		$Player::handling_fee_rate = 0;
			$Player::prison_rounds = 2;
			$Player::due = 0;   		
    	}else{
    		$Player::handling_fee_rate = 0.1;
			$Player::prison_rounds = 1;
			$Player::due = 1000;
    	}

    }
    $main::cur_player->payDue();
    $main::cur_player->putToJail();
}

1;
