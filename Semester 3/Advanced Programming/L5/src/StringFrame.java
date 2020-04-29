import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class StringFrame extends Frame implements ActionListener{
    private Button myButton;
    private TextField myTextField,deleteTextField;

    public StringFrame()
    {
        Init();
    }

    public void Init()
    {
        this.setLayout(new GridLayout(3,2));
        this.setBounds(100,100,500,500);


        myTextField=new TextField();
        this.add(myTextField);

        myButton=new Button("Filter");
        this.add(myButton);
        myButton.addActionListener(this);

        deleteTextField=new TextField();
        this.add(deleteTextField);

        this.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e){
                System.exit(0);
            }
        });
    }

    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        if ( myTextField.getSelectedText() != null) { // See if they selected something
            String s = myTextField.getSelectedText();
            String processed=s.replace(deleteTextField.getText(),"");
            myTextField.setText(processed);
        }
    }
}
