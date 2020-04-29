import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.IOException;

public class View extends JPanel {

    private int x;
    private int y;

    private Model model;
    private Image flower;

    public View(Model model, int x, int y) {
        this.model = model;
        this.x = x;
        this.y = y;

        try {
            flower = ImageIO.read(new File("virag.png")).getScaledInstance(130, 130, ALLBITS);
        } catch(IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        setBackground(Color.darkGray);

        g.setColor(Color.GREEN);
        g.fillRect(x, y-model.getSize(), 10, model.getSize());
        g.drawImage(flower, x - (flower.getWidth(null) - 30) / 2, y - model.getSize() - flower.getHeight(null) / 2, null);
    }

}