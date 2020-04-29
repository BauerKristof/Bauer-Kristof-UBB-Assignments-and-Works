import java.util.Random;

public class Model {

    private int size;
    private int maxSize;

    public Model() {
        size = 100;
        maxSize = new Random().nextInt(300) + size;
    }

    public int getSize() {
        return size;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public int getMaxSize() {
        return maxSize;
    }

}