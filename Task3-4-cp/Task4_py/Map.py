from Cell import Cell

class Map():

  def __init__(self):
    self.cells = [[Cell() for _j in range(7)] for _i in range(7)]

  def addObject(self, theobject):
    pos = None

    if isinstance(theobject,list):
      for monster in theobject:
        pos = monster.getPos()
        self.cells[pos.getRow() - 1][pos.getColumn() -1 ].setOccupiedObject(monster)
    else:
      pos = theobject.getPos()

      if pos is not None:
        self.cells[pos.getRow() - 1][pos.getColumn() - 1].setOccupiedObject(theobject)


  def displayMap(self):
    print("   | 1 | 2 | 3 | 4 | 5 | 6 | 7 |")
    print("--------------------------------")
    for i in range(7):
      print(" {} |".format(i+1), end="")
      for j in range(7):
        occupiedObject = self.cells[i][j].getOccupiedObject()
        if occupiedObject is not None:
          print(" ", end="")
          occupiedObject.displaySymbol()
          print(" |",end="")
        else:
          print("   |",end="")
      print()
      print("--------------------------------")

    print()

  def getOccupiedObject(self, row, column):
    return self.cells[row - 1][column - 1].getOccupiedObject()


  def checkMove(self, row, column):
    return ((row >= 1 and row <= 7) and (column >= 1 and column <= 7))

  def update(self, soldier, oldRow, oldColumn, newRow, newColumn):
    self.cells[oldRow - 1][oldColumn - 1].setOccupiedObject(None)
    self.cells[newRow - 1][newColumn - 1].setOccupiedObject(soldier)















