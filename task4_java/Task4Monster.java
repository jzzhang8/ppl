import java.util.Scanner;


public class Task4Monster extends Monster {

	public Task4Monster(int monsterID, int healthCapacity){
		super(monsterID, healthCapacity);
	}

	public void actionOnSoldier(Task4Soldier soldier) {
		if (this.getHealth() <= 0) {
		  this.talk("You had defeated me.%n%n");
		} else {
		  if (this.requireKey(soldier.getKeys())) {
		    this.fight(soldier);
		  } else {
		    this.displayHints();
		  }
		}
	}


  public void fight(Task4Soldier soldier) {
    boolean fightEnabled = true;

    while (fightEnabled) {
      System.out.printf("       | Monster%d | Soldier |%n", this.getMonsterID());
      System.out.printf("Health | %8d | %7d |%n%n", this.getHealth(), soldier.getHealth());
      System.out.printf("=> What is the next step? (1 = Attack, 2 = Escape, 3 = Use Elixir.) Input: ");

      Scanner sc = new Scanner(System.in);

      String choice = sc.nextLine();

      if (choice.equalsIgnoreCase("1")) {
        if (this.loseHealth()) {
          System.out.printf("=> You defeated Monster%d.%n%n", this.getMonsterID());
          this.dropItems(soldier);
          soldier.addCoin();
          fightEnabled = false;
        } else {
          if (soldier.loseHealth()) {
            this.recover(this.getHealthCapacity());
            fightEnabled = false;
          }
        }
      } else if (choice.equalsIgnoreCase("2")) {
        this.recover(this.getHealthCapacity());
        fightEnabled = false;
      } else if (choice.equalsIgnoreCase("3")) {
        if (soldier.getNumElixirs() == 0) {
          System.out.printf("=> You have run out of elixirs.%n%n");
        } else {
          soldier.useElixir();
        }
      } else {
        System.out.printf("=> Illegal choice!%n%n");
      }
    }
  }


}





