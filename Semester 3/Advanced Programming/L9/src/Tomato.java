import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Tomato extends PizzaIngredient {
    private BufferedImage img;

    public Tomato(Pizza p)
    {
        super(p);

        if(img==null)
        {
            try
            {
                img= ImageIO.read(new File("tomato.png")) ;
            }
            catch (IOException e)
            {
                System.out.println("Hiba a kep betoltesenel");
            }
        }
    }

    private void addTomato(Graphics g)
    {
        g.drawImage(img,0,0,null);
    }
    public void bake(Graphics g)
    {
        super.bake(g);
        addTomato(g);
    }

    @Override
    public int getPrice() {
      return  super.getPrice()+3;
    }


    public String getIngredients(){
        return super.getIngredients()+"Tomato";
    }
}
