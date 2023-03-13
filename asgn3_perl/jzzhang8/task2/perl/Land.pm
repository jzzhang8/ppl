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
package Land;

sub new {
    my $class = shift;
    my $self  = {
        owner => undef,
        level => 0,
    };
    bless $self, $class;
    return $self;
}

sub print {
    my $self = shift;
    if (!defined($self->{owner})) {
        print("Land ");
    } else {
        print("$self->{owner}->{name}:Lv$self->{level}");
    }
}

sub buyLand {

    # ...
    my $self = shift @_;
    if($main::cur_player->{money} < 1000 * (1 + 0.1)){
        print "You do not have enough money to buy the land!\n";
        return;
    }

    local $Player::due = 1000;
    local $Player::handling_fee_rate = 0.1;

    $self->{owner} = $main::cur_player;

    $main::cur_player->payDue();
}

sub upgradeLand {

    # ... 
    my $self = shift @_;
    my $price = 0;
    if($self->{level} == 0){
        $price = 1000;
    }elsif($self->{level} == 1){
        $price = 2000;
    }elsif($self->{level} == 2){
        $price = 5000;
    }else{
        print "ERROR: You cannot upgrade land of level 3 or above!\n";
        return;
    }

    if($main::cur_player->{money} < $price * (1 + 0.1)){
        print "You do not have enough money to upgrade the land!\n";
        return;
    }

    $self->{level} += 1;
    local $Player::due = $price;
    local $Player::handling_fee_rate = 0.1;
    $main::cur_player->payDue();
}

sub chargeToll {

    # ...
    my $self = shift @_;
    my $price;
    my $tax_rate;
    if($self->{level} == 0){
        $price = 500;
        $tax_rate = 0.1;
    }elsif($self->{level} == 1){
        $price = 1000;
        $tax_rate = 0.15;
    }elsif($self->{level} == 2){
        $price = 1500;
        $tax_rate = 0.2;
    }else{
        $price = 3000;
        $tax_rate = 0.25;
    }

    if($main::cur_player->{money} < $price){
        $price = $main::cur_player->{money};
    }

    print "You need to pay player ",$self->{owner}->{name}," \$",$price,"\n";
    local $Player::handling_fee_rate = 0;
    local $Player::due = $price;
    $main::cur_player->payDue();

    # ...
    $Player::handling_fee_rate = 0;
    $Player::due = 0;
    local $Player::income = $price;
    local $Player::tax_rate = $tax_rate;
    $self->{owner}->payDue();
}

sub stepOn {

    # ...
    my $self = shift @_;
    if(defined($self->{owner})){
        if($self->{owner}->{name} eq $main::cur_player->{name}){
            # step on own land
            my $price;
            if($self->{level} == 0){
                $price = 1000;
            }elsif($self->{level} == 1){
                $price = 2000;
            }elsif($self->{level} == 2){
                $price = 5000;
            }else{
                $price = 0;
            }

            if($self->{level} == 3){
                return;
            }else{
                print "Pay \$",$price," to upgrade the land? [y/n]\n";
                my $upgrade = 0;
                while(1){
                    my $ans = <STDIN>;
                    if($ans eq "y\n"){
                        $upgrade = 1;
                        last;
                    }elsif($ans eq "n\n"){
                        last;
                    }else{
                        print "Pay \$",$price," to upgrade the land? [y/n]\n";
                    } 
                }
                if($upgrade){
                    $self->upgradeLand();
                }
            }

        }else{
            # step on opponent's land
            $self->chargeToll();
        }
        
    }else{
        print "Pay \$1000 to buy the land? [y/n]\n";
        my $buy = 0;
        while(1){
            my $ans = <STDIN>;
            if($ans eq "y\n"){
                $buy = 1;
                last;
            }elsif($ans eq "n\n"){
                last;
            }else{
                print "Pay \$1000 to buy the land? [y/n]\n";
            } 
        }
        if($buy){
            $self->buyLand();
        }
    }

}

1;