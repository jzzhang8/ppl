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


from Monster import Monster

class Task4Monster(Monster):

	def __init__(self, MonsterID, healthCapacity):
		Monster.__init__(self, MonsterID, healthCapacity)

	def actionOnSoldier(self, soldier):
		if self.getHealth() <= 0:
			self.talk("You had defeated me.\n\n")
		else:
			if self.requireKey(soldier.getKeys()):
				self.fight(soldier)
			else:
				self.displayHints()

	def fight(self, soldier):
	    fightEnabled = True

	    while fightEnabled:
	      print("       | Monster{} | Soldier |".format(self.monsterID))
	      print("Health | {:>8d} | {:>7d} |\n".format(self.health, soldier.getHealth()))
	      print("=> What is the next step? (1 = Attack, 2 = Escape, 3 = Use Elixir.) Input: ",end="")

	      choice = input()

	      if choice == "1":
	        if self.loseHealth():
	          print("=> You defeated Monster{}.\n".format(self.monsterID))
	          self.dropItems(soldier)
	          soldier.addCoin()
	          fightEnabled = False
	        else:
	          if soldier.loseHealth():
	            self.recover(self.healthCapacity)
	            fightEnabled = False
	      elif choice == "2":
	        self.recover(self.healthCapacity)
	        fightEnabled = False
	      elif choice == "3":
	        if soldier.getNumElixirs() == 0:
	          print("=> You have run out of elixirs.\n")
	        else:
	          soldier.useElixir()
	      else:
	        print("=> Illegal choice!\n")


