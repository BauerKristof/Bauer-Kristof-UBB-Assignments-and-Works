import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Corn extends PizzaIngredient {
    private BufferedImage img;

    public Corn(Pizza p)
    {
        super(p);

        if(img==null)
        {
            try
            {
                img= ImageIO.read(new File("corn.png")) ;
            }
            catch (IOException e)
            {
                System.out.println("Hiba a kep betoltesenel");
            }
        }
    }

    private void addCorn(Graphics g)
    {
        g.drawImage(img,0,0,null);
    }
    public void bake(Graphics g)
    {
        super.bake(g);
        addCorn(g);
    }

    @Override
    public int getPrice() {
        return  super.getPrice()+9;
    }


    public String getIngredients(){
        return super.getIngredients()+"Corn ";
    }
}