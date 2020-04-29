import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Salami extends PizzaIngredient {
    private BufferedImage img;

    public Salami(Pizza p)
    {
        super(p);

        if(img==null)
        {
            try
            {
                img= ImageIO.read(new File("salami.png")) ;
            }
            catch (IOException e)
            {
                System.out.println("Hiba a kep betoltesenel");
            }
        }
    }

    private void addSalami(Graphics g)
    {
        g.drawImage(img,0,0,null);
    }
    public void bake(Graphics g)
    {
        super.bake(g);
        addSalami(g);
    }

    @Override
    public int getPrice() {
        return  super.getPrice()+5;
    }


    public String getIngredients(){
        return super.getIngredients()+"Salami";
    }
}