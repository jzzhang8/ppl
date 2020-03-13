import java.util.Scanner;

public class Task4Merchant {
  private int elixirPrice;
  private int shieldPrice;
  private Pos pos;

  public Task4Merchant() {
    // TODO: Initialization.
    this.elixirPrice = 1;
    this.shieldPrice = 2;
    this.pos = new Pos();
  }

  public void actionOnSoldier(Task4Soldier soldier) {
    this.talk("Do you want to buy something? (1. Elixir, 2. Shield, 3. Leave.) Input: ");


    // TODO: Main logic.
    Scanner sc = new Scanner(System.in);
    String choice = sc.nextLine();
    if(choice.equalsIgnoreCase("1")){
      if(soldier.getCoins() >= this.elixirPrice){
        soldier.addElixir();
        soldier.useCoins(this.elixirPrice);
      }
      else{
        this.talk("You do not have enough coins.%n");
      }

    }else if(choice.equalsIgnoreCase("2")){
      if (soldier.getCoins() >= this.shieldPrice){
        soldier.addShield();
        soldier.useCoins(this.shieldPrice);
      } else{
        this.talk("You do not have enough coins.%n");
      }

    }else if(choice.equalsIgnoreCase("3")){
      // leave 

    }else{
      System.out.printf("=> Illegal choice!%n%n");
    }

    // If the soldier doesn't have enough coins to buy what (s)he wants, the merchant will say "You don't have enough coins.%n%n".
    // Then, the soldier will automatically leave.

    // After the soldier successfully buys an item from the merchant, (s)he will also automatically leave.


  }

  public void talk(String text) {
    System.out.printf("Merchant$: " + text);
  }

  public Pos getPos() {
    return this.pos;
  }

  public void setPos(int row, int column) {
    this.pos.setPos(row, column);
  }

  public void displaySymbol() {
    System.out.printf("$");
  }



  // TODO: Other functions.
}