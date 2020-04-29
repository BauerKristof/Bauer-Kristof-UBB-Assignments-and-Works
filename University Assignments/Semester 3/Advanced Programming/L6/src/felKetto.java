import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class felKetto extends JFrame {

    private int xPos;
    private int yPos;
    private int sugar;
    private JButton balGomb;
    private JButton jobbGomb;
    private JButton felGomb;
    private JButton leGomb;
    private MyPanel valami;

    class MyPanel extends JPanel
    {
        @Override
        public void paintComponent(Graphics g)
        {
            super.paintComponent(g);
            g.setColor(Color.GREEN);
            g.fillOval(xPos, yPos, sugar, sugar);
        }
    }

    public felKetto() {
        init();
        //myFrame.setVisible(true);
    }

    private void init() {
        valami=new MyPanel();
        setLayout(new BorderLayout());
        this.setSize(600, 600);
        this.setLocation(700, 300);
        this.setResizable(false);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //komponensek
        setSize(400, 400);

        sugar = 30;
        xPos = getWidth()/2-sugar/2;
        yPos = getHeight()/2-sugar/2;

        balGomb = new JButton("Bal");
        jobbGomb = new JButton("Jobb");
        felGomb = new JButton("Fel");
        leGomb = new JButton("Le");

        balGomb.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                xPos -= 5;
                repaint();
            }
        });

        jobbGomb.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                xPos += 5;
                repaint();
            }
        });

        felGomb.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                yPos -= 5;
                repaint();
            }
        });

        leGomb.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                yPos += 5;
                repaint();
            }
        });

        add(balGomb, BorderLayout.WEST);
        add(jobbGomb, BorderLayout.EAST);
        add(felGomb, BorderLayout.NORTH);
        add(leGomb, BorderLayout.SOUTH);

        this.add(valami);
    }
}
