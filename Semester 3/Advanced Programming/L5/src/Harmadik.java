import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.Frame;
import java.awt.GridLayout;
import java.awt.List;
import java.awt.Panel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class Harmadik extends Frame {


    private List list1;
    private List list2;
    private Button btn1;
    private Button btn2;
    private Panel buttonPanel;

    public Harmadik() {
        initFrame();
        setComponents();
        setVisible(true);
    }

    private void initFrame() {
        setSize(400, 400);
        setResizable(false);
        setLocation(900, 100);
        setLayout(new BorderLayout());

        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                dispose();
                System.exit(0);
            }
        });
    }

    private void setComponents() {
        list1 = new List();
        list2 = new List();
        list1.setMultipleMode(true);
        list2.setMultipleMode(true);

        btn1 = new Button(">>");
        btn2 = new Button("<<");

        btn1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String[] selected = list1.getSelectedItems();
                for (int i = 0; i < selected.length; i++) {
                    list2.add(selected[i]);
                    list1.remove(selected[i]);
                }
            }
        });

        btn2.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String[] selected = list2.getSelectedItems();
                for (int i = 0; i < selected.length; i++) {
                    list1.add(selected[i]);
                    list2.remove(selected[i]);
                }
            }
        });

        list1.add("alma");
        list1.add("eper");
        list1.add("dinnye");
        list1.add("szolo");

        list2.add("retek");
        list2.add("krumpi");
        list2.add("kaposzta");
        list2.add("lencse");

        buttonPanel = new Panel();
        buttonPanel.setLayout(new GridLayout(2, 1));
        buttonPanel.add(btn1, BorderLayout.CENTER);
        buttonPanel.add(btn2, BorderLayout.CENTER);

        add(list1, BorderLayout.WEST);
        add(list2, BorderLayout.EAST);
        add(buttonPanel, BorderLayout.CENTER);
    }

}