
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

package Bank;
sub new {
    my $class = shift;
    my $self  = {};
    bless $self, $class;
    return $self;
}

sub print {
    print("Bank ");
}

sub stepOn {

    # ...
    my $self = shift @_;
    local $Player::income = 2000;
    local $Player::tax_rate = 0;
    local $Player::due = 0;
    $main::cur_player->payDue();
    print("You received \$2000 from the Bank!\n");
}

1;