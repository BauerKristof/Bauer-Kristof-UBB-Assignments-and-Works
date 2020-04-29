import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public class PizzaBase implements Pizza {

    private BufferedImage img;

    public PizzaBase() {
        try {
            img = ImageIO.read(new File("res/pizza_base.png"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    @Override
    public void bake(Graphics g) {
        g.drawImage(img, 0, 0, null);
    }

    @Override
    public int getPrice() {
        return 15;
    }

    @Override
    public String getIngredients() {
        return "Pizza base";
    }

    public static class PizzaIngredient implements Pizza {

        protected Pizza pizza;

        public PizzaIngredient(Pizza pizza) {
            this.pizza = pizza;
        }

        @Override
        public void bake(Graphics g) {
            pizza.bake(g);
        }

        @Override
        public int getPrice() {
            return pizza.getPrice();
        }

        @Override
        public String getIngredients() {
            return pizza.getIngredients();
        }

    }
}