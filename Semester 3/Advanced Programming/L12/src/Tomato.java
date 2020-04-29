import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public class Tomato extends PizzaIngredient {

    private BufferedImage img;

    public Tomato(Pizza pizza) {
        super(pizza);

        try {
            img = ImageIO.read(new File("res/tomato.png"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void bake(Graphics g) {
        super.bake(g);
        addTomato(g);
    }

    @Override
    public int getPrice() {
        return super.getPrice() + 2;
    }

    @Override
    public String getIngredients() {
        return pizza.getIngredients() + "," + "Tomato";
    }

    private void addTomato(Graphics g) {
        g.drawImage(img, 0, 0, null);
    }

}
