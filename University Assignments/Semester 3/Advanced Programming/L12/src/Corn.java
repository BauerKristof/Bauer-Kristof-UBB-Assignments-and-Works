import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public class Corn extends PizzaIngredient {

    private BufferedImage img;

    public Corn(Pizza pizza) {
        super(pizza);

        try {
            img = ImageIO.read(new File("res/corn.png"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void bake(Graphics g) {
        super.bake(g);
        addCorn(g);
    }

    @Override
    public int getPrice() {
        return super.getPrice() + 4;
    }

    @Override
    public String getIngredients() {
        return pizza.getIngredients() + "," + "Corn";
    }

    private void addCorn(Graphics g) {
        g.drawImage(img, 0, 0, null);
    }

}