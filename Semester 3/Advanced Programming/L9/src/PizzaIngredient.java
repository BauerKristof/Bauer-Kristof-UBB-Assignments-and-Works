import java.awt.*;

public class PizzaIngredient implements Pizza {

    protected Pizza p;

    public PizzaIngredient(Pizza pizza)
    {
        p=pizza;
    }

    public void bake(Graphics g)
    {
        p.bake(g);
    }

    public int getPrice()
    {
        return p.getPrice();
    }
    public String getIngredients()
    {
        return p.getIngredients();
    }
}
