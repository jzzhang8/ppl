
class Pos():

  def __init__(self, row = None, column = None):
    self.row = row
    self.column = column

  def setPos(self, row, column):
    self.row = row
    self.column = column

  def getRow(self):
    return self.row

  def getColumn(self):
    return self.column
