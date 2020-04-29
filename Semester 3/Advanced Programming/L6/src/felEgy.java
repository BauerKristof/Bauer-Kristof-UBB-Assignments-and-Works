import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.time.LocalDateTime;

public class felEgy extends JFrame{
    private JButton myButton;
    private JLabel myLabel;

    public felEgy() {
        Init();
    }

    private void Init() {
        setLayout(new FlowLayout());
        setSize(600,600);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        myLabel = new JLabel();
        add(myLabel);


        myButton = new JButton("Kattints ide");
        add(myButton);
        myButton.addActionListener(new ActionListener() {


            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                LocalDateTime date = LocalDateTime.now();
                String s = date.toString();

                myLabel.setText("A jelenelegi ido: " + s);
            }

        });


    }
}
