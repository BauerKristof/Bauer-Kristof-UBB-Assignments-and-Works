import java.util.Random;

public class Controller implements Runnable {

    private int value;

    private Thread thread;
    private Model model;
    private View view;

    public Controller(Model model, View view) {
        this.model = model;
        this.view = view;
        value = new Random().nextInt(10) + 1;
    }

    public synchronized void start() {
        thread = new Thread(this);
        thread.start();
    }


    @Override
    public void run() {
        while (model.getSize() <= model.getMaxSize()) {
            model.setSize(model.getSize() + value);

            try {
                Thread.sleep(200);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            view.repaint();
        }

        stop();
    }

    public synchronized void stop() {
        try {
            thread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}