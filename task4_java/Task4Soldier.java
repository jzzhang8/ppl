import java.util.Scanner;

public class Task4Soldier extends Soldier {

	private int coins;
	private int shield;

	public Task4Soldier(){
		super();
		this.coins = 0;
		this.shield = 0;
	}

	public boolean loseHealth(){
		int healthLost = 10 - this.shield * 5 >=0 ? 10 - this.shield * 5 : 0;
		this.health -= healthLost;
		return this.health <= 0;
	}

	public void displayInformation() {
	    System.out.printf("Health: %d.%n", this.health);
	    System.out.printf("Position (row, column): (%d, %d).%n", this.getPos().getRow(), this.getPos().getColumn());
	    System.out.printf("Keys: " + this.getKeys() + ".%n");
	    System.out.printf("Elixirs: %d.%n", this.getNumElixirs());
	    System.out.printf("Defence: %d.%n", this.getShields() * 5);
	    System.out.printf("Coins: %d.%n", this.getCoins());
  	}

  	public int getCoins(){
  		return this.coins;
  	}

  	public void addCoin(){
  		this.coins += 1;
  	}

  	public void addShield(){
  		this.shield += 1;
  	}

  	public void useCoins(int num){
  		this.coins -= num;
  	}
  	public int getShields(){
  		return this.shield;
  	}



}