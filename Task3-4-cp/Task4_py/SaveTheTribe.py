from Map import Map
from Soldier import Soldier
from Spring import Spring
from Monster import Monster
import random

class SaveTheTribe():

  def __init__(self):
    self.map = Map()
    self.soldier = Soldier()
    self.spring = Spring()
    self.monsters = [None for _i_ in range(7)]
    self.gameEnabled = True

  def initialize(self):
    self.monsters[0] = Monster(1, random.randint(0, 4) * 10 + 30)
    self.monsters[0].setPos(4, 1)
    self.monsters[0].addDropItem(2)
    self.monsters[0].addDropItem(3)

    self.monsters[1] = Monster(2, random.randint(0, 4) * 10 + 30)
    self.monsters[1].setPos(3, 3)
    self.monsters[1].addDropItem(3)
    self.monsters[1].addDropItem(6)
    self.monsters[1].addHint(1)
    self.monsters[1].addHint(5)


    self.monsters[2] = Monster(3, random.randint(0, 4) * 10 + 30)
    self.monsters[2].setPos(5, 3)
    self.monsters[2].addDropItem(4)
    self.monsters[2].addHint(1)
    self.monsters[2].addHint(2)

    self.monsters[3] = Monster(4, random.randint(0, 4) * 10 + 30)
    self.monsters[3].setPos(5, 5)
    self.monsters[3].addHint(3)
    self.monsters[3].addHint(6)


    self.monsters[4] = Monster(5, random.randint(0, 4) * 10 + 30)
    self.monsters[4].setPos(1, 4)
    self.monsters[4].addDropItem(2)
    self.monsters[4].addDropItem(6)

    self.monsters[5] = Monster(6, random.randint(0, 4) * 10 + 30)
    self.monsters[5].setPos(3, 5)
    self.monsters[5].addDropItem(4)
    self.monsters[5].addDropItem(7)
    self.monsters[5].addHint(2)
    self.monsters[5].addHint(5)

    self.monsters[6] = Monster(7, random.randint(0, 4) * 10 + 30)
    self.monsters[6].setPos(4, 7)
    self.monsters[6].addDropItem(-1)
    self.monsters[6].addHint(6)

    self.map.addObject(self.monsters)

    self.soldier.setPos(1,1)
    self.soldier.addKey(1)
    self.soldier.addKey(5)

    self.map.addObject(self.soldier)

    self.spring.setPos(7, 4)

    self.map.addObject(self.spring)



  def start(self):

    print("=> Welcome to the desert!")
    print("=> Now you have to defeat the monsters and find the artifact to save the tribe.\n")

    while self.gameEnabled:
      self.map.displayMap()
      self.soldier.displayInformation()

      print("\n=> What is the next step? (W = Up, S = Down, A = Left, D = Right.) Input: ",end="")

      move = input()

      pos = self.soldier.getPos()

      newRow = pos.getRow()
      oldRow = pos.getRow()
      newColumn = pos.getColumn()
      oldColumn = pos.getColumn()

      if move.upper() == "W":
        newRow = oldRow - 1
      elif move.upper() == "S":
        newRow = oldRow + 1
      elif move.upper() == "A":
        newColumn = oldColumn - 1
      elif move.upper() == "D":
        newColumn = oldColumn + 1
      else:
        print("=> Illegal move!\n")
        continue

      if self.map.checkMove(newRow, newColumn):
        occupiedObject = self.map.getOccupiedObject(newRow, newColumn)
        if occupiedObject is not None:
          occupiedObject.actionOnSoldier(self.soldier)
        else:
          self.soldier.move(newRow, newColumn)
          self.map.update(self.soldier, oldRow, oldColumn, newRow, newColumn)
      else:
        print("=> Illegal move!\n")

      if self.soldier.getHealth() <= 0:
        print("=> You died.")
        print("=> Game over.\n")
        self.gameEnabled = False

      if -1 in self.soldier.getKeys():
        print("=> You found the artifact.")
        print("=> Game over.\n")
        self.gameEnabled = False


if __name__ == "__main__":
  game = SaveTheTribe()
  game.initialize()
  game.start()





















    