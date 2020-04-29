import java.awt.*;
import java.awt.event.*;
import java.util.Random;

public class MyFrame extends Frame implements ItemListener {
    //private Button myButton;
    private Choice c;

    public MyFrame(String buttonName)
    {
        this.setLayout(new GridLayout(3,2));
        //myButton=new Button(buttonName);
        c=new Choice();

        c.setBounds(100,100, 20,40);
        c.add("Zold");
        c.add("Piros");
        c.add("Random");
        c.setVisible(false);
        c.addItemListener(this);

        this.add(c);
        //this.add(myButton);
        this.setBounds(100,100,500,500);
        //myButton.addActionListener(this);
        this.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e){
               System.exit(0);
            }
       });
        c.setVisible(true);





    }


    /*@Override
    public void actionPerformed(ActionEvent actionEvent) {
        c.setVisible(true);
    }
    */
    @Override
    public void itemStateChanged(ItemEvent ie) {
        String s = (String)ie.getItem();
        if(s=="Zold")
        {
            setBackground(Color.green);
        }
        else if(s=="Piros")
        {
            setBackground(Color.red);
        }

        else if(s=="Random")
        {
            Random rand=new Random();
            Color c=new Color(rand.nextInt(256),rand.nextInt(256),rand.nextInt(256));
            setBackground(c);
        }
    }

}
