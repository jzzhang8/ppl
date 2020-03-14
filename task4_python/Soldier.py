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
import random

class Soldier():

  def __init__(self):
    self.health = 100
    self.numElixirs = 2
    self.pos = Pos()
    self.keys = set()

  def getHealth(self):
    return self.health

  def loseHealth(self):
    self.health -= 10
    return self.health <= 0

  def recover(self, healingPower):
    totalHealth = healingPower + self.health
    if totalHealth >= 100:
      self.health = 100
    else:
      self.health = totalHealth

  def getPos(self):
    return self.pos

  def setPos(self, row, column):
    self.pos.setPos(row, column)

  def move(self, row, column):
    self.setPos(row, column)

  def getKeys(self):
    return list(self.keys)

  def addKey(self, key):
    return self.keys.add(key)

  def getNumElixirs(self):
    return self.numElixirs

  def addElixir(self):
    self.numElixirs += 1

  def useElixir(self):
    self.recover(random.randint(15, 20))
    self.numElixirs -= 1

  def displayInformation(self):
    print("Health: {}.".format(self.health))
    print("Position (row, column): ({}, {}).".format(self.pos.getRow(), self.pos.getColumn()))
    print("Keys: " + str(list(self.keys)))
    print("Elixirs: {}.".format(self.numElixirs))

  def displaySymbol(self):
    print("S",end="")













