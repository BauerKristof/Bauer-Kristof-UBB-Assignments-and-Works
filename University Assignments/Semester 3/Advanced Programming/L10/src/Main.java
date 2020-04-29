import java.awt.Color;
import java.awt.GridLayout;

import javax.swing.JFrame;

public class Main extends JFrame {

    private static final long serialVersionUID = 1L;

    private final int width = 600;
    private final int height = 400;

    private Model[] flowerModel;
    private View[] flowerView;
    private Controller[] flowerController;

    public Main() {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(0, 0, width, height);
        setBackground(Color.BLUE);
        setResizable(false);
        setLocationRelativeTo(null);
        getContentPane().setLayout(new GridLayout(0, 3));

        flowerView = new View[3];
        flowerModel = new Model[3];
        flowerController = new Controller[3];

        for (int i = 0; i < 3; i++) {
            flowerModel[i] = new Model();
            flowerView[i] = new View(flowerModel[i], 70, height);
            flowerController[i] = new Controller(flowerModel[i], flowerView[i]);
        }

        for (int i = 0; i < 3; i++) {
            getContentPane().add(flowerView[i]);
            flowerController[i].start();
        }
    }

    public static void main(String[] args) {
        new Main().setVisible(true);
    }

}