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


from Soldier import Soldier

class Task4Soldier(Soldier):

	def __init__(self):
		Soldier.__init__(self)
		self.coins = 0
		self.shield = 0

	def loseHealth(self):
		healthLost = 10 - self.getShields() * 5 if 10 - self.getShields() * 5 >= 0 else 0
		self.health -= healthLost
		return self.health <= 0

	def displayInformation(self):
	    print("Health: {}.".format(self.health))
	    print("Position (row, column): ({}, {}).".format(self.pos.getRow(), self.pos.getColumn()))
	    print("Keys: " + str(list(self.keys)))
	    print("Elixirs: {}.".format(self.numElixirs))
	    print("Defence: {}.".format(self.getShields() * 5))
	    print("Coins: {}.".format(self.getCoins()))

	def getCoins(self):
		return self.coins

	def addCoin(self):
		self.coins += 1

	def addShield(self):
		self.shield += 1

	def useCoins(self, num):
		self.coins -= num

	def getShields(self):
		return self.shield

