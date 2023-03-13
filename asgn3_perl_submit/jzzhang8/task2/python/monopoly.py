
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

import random

random.seed(0) # don't touch!

# you are not allowed to modify Player class!
class Player:
    due = 200
    income = 0
    tax_rate = 0.2
    handling_fee_rate = 0
    prison_rounds = 2

    def __init__(self, name):
        self.name = name
        self.money = 100000
        self.position = 0
        self.num_rounds_in_jail = 0

    def updateAsset(self):
        self.money += Player.income

    def payDue(self):
        # print(cur_player.name,"In:",Player.income,"tax:",Player.tax_rate)
        self.money += Player.income * (1 - Player.tax_rate)
        # print(cur_player.name,"Out:",Player.due,"handling",Player.handling_fee_rate)
        self.money -= Player.due * (1 + Player.handling_fee_rate)

    def printAsset(self):
        print("Player %s's money: %d" % (self.name, self.money))

    def putToJail(self):
        self.num_rounds_in_jail = Player.prison_rounds

    def move(self, step):
        if self.num_rounds_in_jail > 0:
            self.num_rounds_in_jail -= 1
        else:
            self.position = (self.position + step) % 36



class Bank:
    def __init__(self):
        pass

    def print(self):
        print("Bank ", end='')

    def stepOn(self):

        Player.due = 0
        Player.income = 2000
        Player.tax_rate = 0
        Player.handling_fee_rate = 0
        cur_player.payDue()
        print("You received $2000 from the Bank!")
        return

class Jail:
    def __init__(self):
        pass

    def print(self):
        print("Jail ", end='')

    def stepOn(self):

        # ...
        print("Pay $1000 to reduce the prison round to 1? [y/n]")
        buy = 0
        while True:
            ans = input()
            if ans == 'y':
                buy = 1
                break
            elif ans == 'n':
                break
            else:
                print("Pay $1000 to reduce the prison round to 1? [y/n]")

        Player.due = 0
        Player.income = 0
        Player.tax_rate = 0.2
        Player.handling_fee_rate = 0
        Player.prison_rounds = 2
        if buy:
            if cur_player.money < 1000 * (1 + 0.1):
                print("You do not have enough money to reduce the prison round!")
                Player.due = 0
                Player.income = 0
                Player.tax_rate = 0.2
                Player.handling_fee_rate = 0
                Player.prison_rounds = 2
            else:
                Player.due = 1000
                Player.income = 0
                Player.tax_rate = 0.2
                Player.handling_fee_rate = 0.1
                Player.prison_rounds = 1
        cur_player.payDue()

        cur_player.putToJail()


class Land:
    land_price = 1000
    upgrade_fee = [1000, 2000, 5000]
    toll = [500, 1000, 1500, 3000]
    tax_rate = [0.1, 0.15, 0.2, 0.25]

    def __init__(self):
        self.owner = None
        self.level = 0

    def print(self):
        if self.owner is None:
            print("Land ", end='')
        else:
            print("%s:Lv%d" % (self.owner.name, self.level), end="")
    
    def buyLand(self):

        # ...
        if cur_player.money < 1000 * (1 + 0.1):
            print("You do not have enough money to buy the land!")
            return
        Player.due = 1000
        Player.income = 0
        Player.tax_rate = 0.2
        Player.handling_fee_rate = 0.1

        self.owner = cur_player

        cur_player.payDue()
    
    def upgradeLand(self):
        
        # ...
        price = 0
        if self.level >= 3:
            print("ERROR: You cannot upgrade land of level 3 or above!")
            return
        else:
            price = Land.upgrade_fee[self.level]

        if cur_player.money < price * (1 + 0.1):
            print("You do not have enough money to upgrade the land!")
            return

        self.level += 1

        Player.due = price
        Player.income = 0
        Player.tax_rate = 0.2
        Player.handling_fee_rate = 0.1

        cur_player.payDue()
    
    def chargeToll(self):
        
        # ...
        price = Land.toll[self.level]
        tax = Land.tax_rate[self.level]

        if cur_player.money < price:
            price = cur_player.money

        print("You need to pay player %s $%d" % ( self.owner.name, price ))

        Player.due = price
        Player.income = 0
        Player.tax_rate = 0.2
        Player.handling_fee_rate = 0

        cur_player.payDue()

        # ...

        Player.due = 0
        Player.income = price
        Player.tax_rate = tax
        Player.handling_fee_rate = 0

        self.owner.payDue()

    def stepOn(self):

        # ... 
        if self.owner != None:
            if self.owner.name == cur_player.name:
                price = Land.upgrade_fee[self.level] if self.level < 3 else -10000000000
                
                if self.level == 3:
                    return
                else:
                    print("Pay $%d to upgrade the land? [y/n]" % price)
                    upgrade = 0
                    while True:
                        ans = input()
                        if ans == 'y':
                            upgrade = 1
                            break
                        elif ans == 'n':
                            break
                        else:
                            print("Pay $%d to upgrade the land? [y/n]" % price)
                    if upgrade:
                        self.upgradeLand()
            else:
                self.chargeToll()
        else:
            print("Pay $1000 to buy the land? [y/n]")
            buy = 0

            while True:
                ans = input()
                if ans == 'y':
                    buy = 1
                    break
                elif ans == 'n':
                    break
                else:
                    print("Pay $1000 to buy the land? [y/n]")

            if buy:
                self.buyLand()

        return



players = [Player("A"), Player("B")]
cur_player = players[0]
num_players = len(players)
cur_player_idx = 0
cur_player = players[cur_player_idx]
num_dices = 1
cur_round = 0

game_board = [
    Bank(), Land(), Land(), Land(), Land(), Land(), Land(), Land(), Land(), Jail(),
    Land(), Land(), Land(), Land(), Land(), Land(), Land(), Land(),
    Jail(), Land(), Land(), Land(), Land(), Land(), Land(), Land(), Land(), Jail(),
    Land(), Land(), Land(), Land(), Land(), Land(), Land(), Land()
]
game_board_size = len(game_board)


def printCellPrefix(position):
    occupying = []
    for player in players:
        if player.position == position and player.money > 0:
            occupying.append(player.name)
    print(" " * (num_players - len(occupying)) + "".join(occupying), end='')
    if len(occupying) > 0:
        print("|", end='')
    else:
        print(" ", end='')


def printGameBoard():
    print("-" * (10 * (num_players + 6)))
    for i in range(10):
        printCellPrefix(i)
        game_board[i].print()
    print("\n")
    for i in range(8):
        printCellPrefix(game_board_size - i - 1)
        game_board[-i - 1].print()
        print(" " * (8 * (num_players + 6)), end="")
        printCellPrefix(i + 10)
        game_board[i + 10].print()
        print("\n")
    for i in range(10):
        printCellPrefix(27 - i)
        game_board[27 - i].print()
    print("")
    print("-" * (10 * (num_players + 6)))


def terminationCheck():

    # ...
    if cur_player.money == 0:
        return False
    if players[1 - cur_player_idx].money == 0:
        return False

    return True


def throwDice():
    step = 0
    for i in range(num_dices):
        step += random.randint(1, 6)
    return step


def main():
    global cur_player
    global num_dices
    global cur_round
    global cur_player_idx

    while terminationCheck():
        printGameBoard()
        for player in players:
            player.printAsset()

        # ...
        if cur_player.money < 200:
            Player.due = cur_player.money
            Player.income = 0
            Player.tax_rate = 0.2
            Player.handling_fee_rate = 0

            cur_player.payDue()
        else:
            Player.due = 200
            Player.income = 0
            Player.tax_rate = 0.2
            Player.handling_fee_rate = 0
            cur_player.payDue()

        if cur_player.num_rounds_in_jail > 0:
            cur_player.move(0)
            cur_player_idx = 1 - cur_player_idx
            cur_player = players[cur_player_idx]
            continue

        print("Player %s's turn." % cur_player.name)
        print("Pay $500 to throw two dice? [y/n]")

        throwNum = 1
        while True:
            ans  = input()
            if ans == 'y':
                throwNum = 2
                break
            elif ans == 'n':
                break
            else:
                print("Pay $500 to throw two dice? [y/n]")

        if throwNum == 2:
            if cur_player.money < 500 * (1+0.05):
                print("You do not have enough money to throw two dice!")
                throwNum = 1
            else:
                Player.due = 500
                Player.income = 0
                Player.tax_rate = 0.2
                Player.handling_fee_rate = 0.05

                cur_player.payDue()

        num_dices = throwNum
        step = throwDice()

        print("Points of dice: %d" % step)

        cur_player.move(step)
        printGameBoard()
        game_board[cur_player.position].stepOn()

        cur_player_idx = 1 - cur_player_idx
        cur_player = players[cur_player_idx]

        while cur_player.num_rounds_in_jail > 0:
            if cur_player.money < 200:
                Player.due = cur_player.money
                Player.income = 0
                Player.tax_rate = 0.2
                Player.handling_fee_rate = 0
                cur_player.payDue()
            else:
                Player.due = 200
                Player.income = 0
                Player.tax_rate = 0.2
                Player.handling_fee_rate = 0
                cur_player.payDue()

            cur_player.move(0)
            cur_player_idx = 1 - cur_player_idx
            cur_player = players[cur_player_idx]



    if cur_player.money != 0:
        print("Game over! winner: %s" % cur_player.name)
    else:
        print("Game over! winner: %s" % players[1 - cur_player_idx].name)



if __name__ == '__main__':
    main()
