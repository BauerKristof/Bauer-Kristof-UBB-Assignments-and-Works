import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Olive extends PizzaIngredient {
    private BufferedImage img;

    public Olive(Pizza p)
    {
        super(p);

        if(img==null)
        {
            try
            {
                img= ImageIO.read(new File("olive.png")) ;
            }
            catch (IOException e)
            {
                System.out.println("Hiba a kep betoltesenel");
            }
        }
    }

    private void addOlive(Graphics g)
    {
        g.drawImage(img,0,0,null);
    }
    public void bake(Graphics g)
    {
        super.bake(g);
        addOlive(g);
    }

    @Override
    public int getPrice() {
        return  super.getPrice()+1;
    }


    public String getIngredients(){
        return super.getIngredients()+"Olive ";
    }
}