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

class Cell():

  def __init__(self):
    self.occupiedObject = None

  def getOccupiedObject(self):
    return self.occupiedObject

  def setOccupiedObject(self, occupiedObject):
    self.occupiedObject = occupiedObject