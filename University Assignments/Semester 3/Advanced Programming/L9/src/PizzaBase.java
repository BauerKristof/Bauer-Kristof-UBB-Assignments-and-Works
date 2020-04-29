import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class PizzaBase implements Pizza {
    private BufferedImage img;

    public void bake(Graphics g) {
        try {
            if (img == null) {
                img = ImageIO.read(new File("pizza_base.png"));
            }
            g.drawImage(img, 0, 0, null);
        } catch (IOException e) {
            System.out.println("Error while reading image");
        }

    }
    public int getPrice()
    {
        return 5;
    }
    public String getIngredients()
    {
    return "Pizza alap";
    }

}
