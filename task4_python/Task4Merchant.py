# -*- coding: utf-8 -*

# /∗
# ∗ CSCI3180 Principles of Programming Languages 
# ∗
# ∗ --- Declaration --- 
# ∗
# ∗ I declare that the assignment here submitted is original except for source
# ∗ material explicitly acknowledged. I also acknowledge that I am aware of
# ∗ University policy and regulations on honesty in academic work, and of the
# ∗ disciplinary guidelines and procedures applicable to breaches of such policy
# ∗ and regulations, as contained in the website
# ∗ http://www.cuhk.edu.hk/policy/academichonesty/ 
# ∗
# ∗ Assignment 2
# ∗ Name : ZHANG Jingze
# ∗ Student ID : 1155107857
# ∗ Email Addr : jzzhang8@cse.cuhk.edu.hk 
# ∗/

from Pos import Pos

class Task4Merchant():
  def __init__(self):
    self.pos = Pos()
    self.elixirPrice = 1
    self.shieldPrice = 2

  def actionOnSoldier(self,soldier):
    self.talk("Do you want to buy something? (1. Elixir, 2. Shield, 3. Leave.) Input: ")

    choice = input()

    if choice == "1":
      if soldier.getCoins() >= self.elixirPrice:
        soldier.addElixir()
        soldier.useCoins(self.elixirPrice)
      else:
        self.talk("You don't have enough coins.\n\n")

    elif choice == "2":
      if soldier.getCoins() >= self.shieldPrice:
        soldier.addShield()
        soldier.useCoins(self.shieldPrice)
      else:
        self.talk("You don't have enough coins.\n\n")

    elif choice == "3":
      pass # leave directly

    else:
      print("=> Illegal choice!\n")

  def talk(self, text):
    print("Merchant$: " + text, end="")

  def getPos(self):
    return self.pos

  def setPos(self, row, column):
    self.pos.setPos(row,column)

  def displaySymbol(self):
    print("$",end="")





