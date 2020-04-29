import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class MushRoom extends PizzaIngredient {
    private BufferedImage img;

    public MushRoom(Pizza p)
    {
        super(p);

        if(img==null)
        {
            try
            {
                img= ImageIO.read(new File("mushroom.png")) ;
            }
            catch (IOException e)
            {
                System.out.println("Hiba a kep betoltesenel");
            }
        }
    }

    private void addMushRoom(Graphics g)
    {
        g.drawImage(img,0,0,null);
    }
    public void bake(Graphics g)
    {
        super.bake(g);
        addMushRoom(g);
    }

    @Override
    public int getPrice() {
        return  super.getPrice()+6;
    }


    public String getIngredients(){
        return super.getIngredients()+"MushRoom";
    }
}