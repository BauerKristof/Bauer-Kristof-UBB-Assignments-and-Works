import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.filechooser.FileFilter;
import javax.swing.filechooser.FileNameExtensionFilter;

public class Main extends JFrame {

    private Pizza myPizza;

    private JCheckBox checkBoxSalami;
    private JCheckBox checkBoxTomato;
    private JCheckBox checkBoxMushroom;
    private JCheckBox checkBoxCorn;
    private JCheckBox checkBoxOlive;


    private JPanel checkBoxPanel;
    private JPanel pizzaPanel;
    private JPanel saveLoadPanel;

    private JButton buttonBake;
    private JButton buttonSave;
    private JButton buttonLoad;

    public static void main(String[] args) {
        new Main();
    }

    public Main() {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        initGUI();
        pack();
        setLocationRelativeTo(null);

        myPizza = new PizzaBase();
        myPizza.bake(pizzaPanel.getGraphics());

        pizzaPanel.repaint();
        setVisible(true);
    }

    private void initGUI() {
        checkBoxCorn = new JCheckBox("Corn");
        checkBoxOlive = new JCheckBox("Olive");
        checkBoxTomato = new JCheckBox("Tomato");
        checkBoxSalami = new JCheckBox("Salami");
        checkBoxMushroom = new JCheckBox("Mushroom");

        checkBoxPanel = new JPanel(new FlowLayout());
        checkBoxPanel.add(checkBoxCorn);
        checkBoxPanel.add(checkBoxOlive);
        checkBoxPanel.add(checkBoxTomato);
        checkBoxPanel.add(checkBoxSalami);
        checkBoxPanel.add(checkBoxMushroom);

        pizzaPanel = new JPanel();
        pizzaPanel.setPreferredSize(new Dimension(500, 500));

        buttonBake = new JButton("Bake pizza!");
        buttonSave = new JButton("Save");
        buttonLoad = new JButton("Load");

        buttonBake.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent arg0) {
                bake();
            }
        });

        buttonSave.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent arg0) {
                save();
            }
        });

        buttonLoad.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent arg0) {
                load();
            }
        });

        saveLoadPanel = new JPanel();
        checkBoxPanel.add(buttonBake);
        saveLoadPanel.add(buttonSave);
        saveLoadPanel.add(buttonLoad);

        add(pizzaPanel, BorderLayout.WEST);
        add(checkBoxPanel, BorderLayout.NORTH);
        add(saveLoadPanel, BorderLayout.SOUTH);
    }

    private void bake() {
        myPizza = new PizzaBase();

        if (checkBoxCorn.isSelected()) {
            myPizza = new Corn(myPizza);
        }

        if (checkBoxOlive.isSelected()) {
            myPizza = new Olive(myPizza);
        }

        if (checkBoxTomato.isSelected()) {
            myPizza = new Tomato(myPizza);
        }

        if (checkBoxSalami.isSelected()) {
            myPizza = new Salami(myPizza);
        }

        if (checkBoxMushroom.isSelected()) {
            myPizza = new Mushroom(myPizza);
        }

        myPizza.bake(pizzaPanel.getGraphics());
    }

    private void save() {
        if (myPizza != null) {
            String ingredients = myPizza.getIngredients();
            JFileChooser chooser = new JFileChooser();
            chooser.setCurrentDirectory(new File("."));

            int retrival = chooser.showSaveDialog(null);
            if (retrival == JFileChooser.APPROVE_OPTION) {
                try {
                    FileWriter writer = new FileWriter(chooser.getSelectedFile() + ".txt");
                    writer.write(ingredients);
                    writer.flush();
                    writer.close();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
    }

    private void load() {
        String loadedPizza = "";
        JFileChooser chooser = new JFileChooser();
        chooser.setCurrentDirectory(new File("."));
        FileNameExtensionFilter filter = new FileNameExtensionFilter("TEXT FILES", "txt", "text");

        chooser.setFileFilter(filter);
        chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
        chooser.setAcceptAllFileFilterUsed(false);
        chooser.addChoosableFileFilter(new FileFilter() {
            @Override
            public boolean accept(File f) {
                return f.isDirectory() || f.getName().toLowerCase().endsWith(".txt");
            }

            @Override
            public String getDescription() {
                return "Text Files (*.txt)";
            }
        });

        String text = null;
        int retrival = chooser.showOpenDialog(null);

        if (retrival == JFileChooser.APPROVE_OPTION) {
            try (BufferedReader reader = new BufferedReader(new FileReader(chooser.getSelectedFile()))) {
                while ((text = reader.readLine()) != null) {
                    loadedPizza += text;
                }

                System.out.println("Sikeres betoltes, recept: " + loadedPizza);
                loadFromFile(loadedPizza);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private void loadFromFile(String loadedPizza) {
        myPizza = new PizzaBase();

        checkBoxCorn.setSelected(false);
        checkBoxOlive.setSelected(false);
        checkBoxSalami.setSelected(false);
        checkBoxTomato.setSelected(false);
        checkBoxMushroom.setSelected(false);

        String[] ingredients = loadedPizza.split(",");
        for (String s : ingredients) {
            if (s.equals("Salami")) {
                myPizza = new Salami(myPizza);
                checkBoxSalami.setSelected(true);
            } else if (s.equals("Olive")) {
                myPizza = new Olive(myPizza);
                checkBoxOlive.setSelected(true);
            } else if (s.equals("Corn")) {
                myPizza = new Corn(myPizza);
                checkBoxCorn.setSelected(true);
            } else if (s.equals("Mushroom")) {
                myPizza = new Mushroom(myPizza);
                checkBoxMushroom.setSelected(true);
            } else if (s.equals("Tomato")) {
                myPizza = new Tomato(myPizza);
                checkBoxTomato.setSelected(true);
            } else if (!s.equals("Pizza base")) {
                System.out.println("Hiba: helyetelenek a fájlban levő hozzávalók!");
            }
        }

        myPizza.bake(pizzaPanel.getGraphics());
    }
}