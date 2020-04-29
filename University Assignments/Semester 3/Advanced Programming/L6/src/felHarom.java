import javax.swing.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Random;

public class felHarom extends JFrame {

    private JButton pushButton;

    public felHarom()
    {
        initFrame();
        initComponent();

        add(pushButton);
    }

    private void initFrame()
    {
        setLayout(null);
        this.setSize(600, 600);
        this.setLocation(100, 100);
        this.setResizable(false);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    private void initComponent()
    {
        Random rand = new Random();

        pushButton=new JButton("PUSH ME!!4441!!$4114");
        pushButton.setSize(200,50);
        pushButton.setLocation(rand.nextInt(600),rand.nextInt(600));


        pushButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                pushButton.setLocation(rand.nextInt(400),rand.nextInt(400));
                super.mouseEntered(e);
            }
        });
    }

}
