import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public class Olive extends PizzaIngredient {

    private BufferedImage img;

    public Olive(Pizza pizza) {
        super(pizza);

        try {
            img = ImageIO.read(new File("res/olive.png"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void bake(Graphics g) {
        super.bake(g);
        addOlive(g);
    }

    @Override
    public int getPrice() {
        return super.getPrice() + 5;
    }

    @Override
    public String getIngredients() {
        return pizza.getIngredients() + "," + "Olive";
    }

    private void addOlive(Graphics g) {
        g.drawImage(img, 0, 0, null);
    }

}