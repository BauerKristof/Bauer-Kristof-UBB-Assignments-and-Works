import java.awt.Dimension;
import java.awt.Graphics;

import javax.swing.JFrame;

public class Main extends JFrame {

    private static final long serialVersionUID = 1L;
    private Pizza pizza;

    public Main() {
        getContentPane().setPreferredSize(new Dimension(500, 500));
        pack();
        setLocationRelativeTo(null);
        setVisible(true);

        bakePizza();
        writeData();
    }

    private void bakePizza() {
        pizza = new Tomato(new Corn(new MushRoom(new Salami(new PizzaBase()))));
        repaint();
    }

    private void writeData() {
        System.out.println("Price: " + pizza.getPrice());
        System.out.println("Ingredients: " + pizza.getIngredients() + "\n");
    }

    @Override
    public void paint(Graphics g) {
        if (pizza != null) {
            pizza.bake(g);
        }
    }

    public static void main(String[] args) {
        new Main();
    }

}