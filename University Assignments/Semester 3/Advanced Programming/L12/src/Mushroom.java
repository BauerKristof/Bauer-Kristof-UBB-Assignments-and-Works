import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public class Mushroom extends PizzaIngredient {

    private BufferedImage img;

    public Mushroom(Pizza pizza) {
        super(pizza);

        try {
            img = ImageIO.read(new File("res/mushroom.png"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void bake(Graphics g) {
        super.bake(g);
        addMushroom(g);
    }

    @Override
    public int getPrice() {
        return super.getPrice() + 3;
    }

    @Override
    public String getIngredients() {
        return pizza.getIngredients() + "," + "Mushroom";
    }

    private void addMushroom(Graphics g) {
        g.drawImage(img, 0, 0, null);
    }

}