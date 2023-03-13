#! /usr/bin/perl

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

use warnings;
use strict;
require "./Bank.pm";
require "./Jail.pm";
require "./Land.pm";
require "./Player.pm";

our @game_board = (
    new Bank(), new Land(), new Land(), new Land(), new Land(), new Land(), new Land(), new Land(), new Land(), new Jail(),
    new Land(), new Land(), new Land(), new Land(), new Land(), new Land(), new Land(), new Land(),
    new Jail(), new Land(), new Land(), new Land(), new Land(), new Land(), new Land(), new Land(), new Land(), new Jail(),
    new Land(), new Land(), new Land(), new Land(), new Land(), new Land(), new Land(), new Land(),
);
our $game_board_size = @game_board;

our @players = (new Player("A"), new Player("B"));
our $num_players = @players;

our $cur_player_idx = 0;
our $cur_player = $players[$cur_player_idx];
our $cur_round = 0;
our $num_dices = 1;

srand(0); # don't touch

# game board printing utility. Used to show player position.
sub printCellPrefix {
    my $position = shift;
    my @occupying = ();
    foreach my $player (@players) {
        if ($player->{position} == $position && $player->{money} > 0) {
            push(@occupying, ($player->{name}));
        }
    }
    print(" " x ($num_players - scalar @occupying), @occupying);
    if (scalar @occupying) {
        print("|");
    } else {
        print(" ");
    }
}

sub printGameBoard {
    print("-"x (10 * ($num_players + 6)), "\n");
    for (my $i = 0; $i < 10; $i += 1) {
        printCellPrefix($i);
        $game_board[$i]->print();
    }
    print("\n\n");
    for (my $i = 0; $i < 8; $i += 1) {
        printCellPrefix($game_board_size - $i - 1);
        $game_board[-$i-1]->print();
        print(" "x (8 * ($num_players + 6)));
        printCellPrefix($i + 10);
        $game_board[$i+10]->print();
        print("\n\n");
    }
    for (my $i = 0; $i < 10; $i += 1) {
        printCellPrefix(27 - $i);
        $game_board[27-$i]->print();
    }
    print("\n");
    print("-"x (10 * ($num_players + 6)), "\n");
}

sub terminationCheck {

    # ...
    if($main::cur_player->{money} == 0){
        return 0;
    }
    if(@main::players[1-$main::cur_player_idx]->{money} == 0){
        return 0;
    }
    return 1;
}

sub throwDice {
    my $step = 0;
    for (my $i = 0; $i < $num_dices; $i += 1) {
        $step += 1 + int(rand(6));
    }
    return $step;
}

sub main {
    while (terminationCheck()){
        printGameBoard();
        foreach my $player (@players) {
            $player->printAsset();
        }
        
        # ...
        if($main::cur_player->{money} < 200){
            local $Player::due = $main::cur_player->{money};
            $main::cur_player->payDue();
        }else{
            $main::cur_player->payDue();
        }

        if($main::cur_player->{num_rounds_in_jail} > 0){
            $main::cur_player->move(0);
            # change the ongoing player
            $main::cur_player_idx = 1 - $main::cur_player_idx;
            $main::cur_player = $main::players[$main::cur_player_idx];
            next;
        }

        print "Player ",$main::cur_player->{name},"'s turn.\n";
        print "Pay \$500 to throw two dice? [y/n]\n";

        my $throwNum = 1;
        while(1){
            my $ans = <STDIN>;
            if($ans eq "y\n"){
                $throwNum = 2;
                last;
            }elsif($ans eq "n\n"){
                last;
            }else{
                print "Pay \$500 to throw two dice? [y/n]\n";
            } 
        }
        
        if($throwNum == 2){
            if($main::cur_player->{money} < 500 * (1+0.05)){
                print "You do not have enough money to throw two dice!\n";
                $throwNum = 1;
            }else{
                local $Player::due = 500;
                local $Player::handling_fee_rate;
                $Player::handling_fee_rate = 0.05;
                $main::cur_player->payDue(); 
            }    
        }

        local $main::num_dices = $throwNum;
        my $step;
        $step = throwDice();  
        
        print "Points of dice: ",$step,"\n";

        
        $main::cur_player->move($step);
        printGameBoard();
        $main::game_board[$main::cur_player->{position}]->stepOn();
        

        # change the ongoing player
        $main::cur_player_idx = 1 - $main::cur_player_idx;
        $main::cur_player = $main::players[$main::cur_player_idx];

        while($main::cur_player->{num_rounds_in_jail} > 0){
            if($main::cur_player->{money} < 200){
                local $Player::due = $main::cur_player->{money};
                $main::cur_player->payDue();
            }else{
                $main::cur_player->payDue();
            }

            $main::cur_player->move(0);
            # change the ongoing player
            $main::cur_player_idx = 1 - $main::cur_player_idx;
            $main::cur_player = $main::players[$main::cur_player_idx];
        }

    }

    if($main::cur_player->{money} != 0){
        print "Game over! winner: ",$main::cur_player->{name},"\n";
    }else{
        print "Game over! winner: ",$main::players[1 - $main::cur_player_idx]->{name},"\n";
    }
}

main();








